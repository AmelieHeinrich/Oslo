//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-04-06 16:41:14
//

#include "Uploader.hpp"
#include "RHI.hpp"

#include <cstdlib>

Uploader::Data Uploader::sData;

void Uploader::Init()
{
    sData.CmdBuffer = nullptr;
    sData.BufferRequests = 0;
    sData.TextureRequests = 0;
    sData.UploadBatchSize = 0;
}

void Uploader::EnqueueTextureUpload(std::vector<uint8_t> buffer, std::shared_ptr<Resource> texture)
{
    sData.TextureRequests++;

    UploadRequest request = {};
    request.Type = UploadRequestType::TextureToGPU;
    request.Resource = texture;
    
    D3D12_RESOURCE_DESC desc = texture->GetResource()->GetDesc();
    std::vector<D3D12_PLACED_SUBRESOURCE_FOOTPRINT> footprints(desc.MipLevels);
    std::vector<uint32_t> numRows(desc.MipLevels);
    std::vector<uint64_t> rowSizes(desc.MipLevels);
    uint64_t totalSize = 0;

    RHI::GetDevice()->GetDevice()->GetCopyableFootprints(&desc, 0, desc.MipLevels, 0, footprints.data(), numRows.data(), rowSizes.data(), &totalSize);
    request.StagingBuffer = std::make_shared<Buffer>(totalSize, 0, BufferType::Copy, "Staging Buffer " + texture->GetName());

    uint8_t* pixels = reinterpret_cast<uint8_t*>(buffer.data());    
    uint8_t* mapped;
    request.StagingBuffer->Map(0, 0, (void**)&mapped);
    for (int i = 0; i < desc.MipLevels; i++) {
        for (int j = 0; j < numRows[i]; j++) {
            memcpy(mapped, pixels, rowSizes[i]);
            mapped += footprints[i].Footprint.RowPitch;
            pixels += rowSizes[i];
        }
    }
    request.StagingBuffer->Unmap(0, 0);

    sData.Requests.push_back(request);

    sData.UploadBatchSize += totalSize;
    if (sData.UploadBatchSize >= MAX_UPLOAD_BATCH_SIZE)
        Flush();
}

void Uploader::EnqueueBufferUpload(void* data, uint64_t size, std::shared_ptr<Resource> buffer)
{
    sData.BufferRequests++;

    UploadRequest request = {};
    request.Type = UploadRequestType::BufferCPUToGPU;
    request.Resource = buffer;
    request.StagingBuffer = std::make_shared<Buffer>(size, 0, BufferType::Copy, "Staging Buffer " + buffer->GetName());

    void* mapped;
    request.StagingBuffer->Map(0, 0, &mapped);
    memcpy(mapped, data, size);
    request.StagingBuffer->Unmap(0, 0);

    sData.Requests.push_back(request);

    sData.UploadBatchSize += size;
    if (sData.UploadBatchSize >= MAX_UPLOAD_BATCH_SIZE)
        Flush();
}

void Uploader::EnqueueAccelerationStructureBuild(std::shared_ptr<AccelerationStructure> as)
{
    sData.ASRequests++;

    UploadRequest request = {};
    request.Type = UploadRequestType::BuildAS;
    request.Acceleration = as;

    sData.Requests.push_back(request);
}

void Uploader::Flush()
{
    if (sData.Requests.empty())
        return;

    sData.CmdBuffer = std::make_shared<CommandBuffer>(RHI::GetGraphicsQueue(), true);
    sData.CmdBuffer->Begin();

    LOG_INFO("Flushing {0} upload requests ({1} buffer uploads, {2} texture uploads, {3} acceleration structure builds)", sData.Requests.size(), sData.BufferRequests, sData.TextureRequests, sData.ASRequests);
    for (auto request : sData.Requests) {        
        switch (request.Type) {
            case UploadRequestType::BufferCPUToGPU: {
                sData.CmdBuffer->Barrier(request.Resource, ResourceLayout::CopyDest);
                sData.CmdBuffer->Barrier(request.StagingBuffer, ResourceLayout::CopySource);
                sData.CmdBuffer->CopyBufferToBuffer(request.Resource, request.StagingBuffer);
                sData.CmdBuffer->Barrier(request.StagingBuffer, ResourceLayout::Common);
                sData.CmdBuffer->Barrier(request.Resource, ResourceLayout::NonPixelShader);
                break;
            }
            case UploadRequestType::TextureToGPU: {
                sData.CmdBuffer->Barrier(request.Resource, ResourceLayout::CopyDest);
                sData.CmdBuffer->Barrier(request.StagingBuffer, ResourceLayout::CopySource);
                sData.CmdBuffer->CopyBufferToTexture(request.Resource, request.StagingBuffer);
                sData.CmdBuffer->Barrier(request.StagingBuffer, ResourceLayout::Common);
                sData.CmdBuffer->Barrier(request.Resource, ResourceLayout::Shader);
                break;
            }
            case UploadRequestType::BuildAS: {
                sData.CmdBuffer->UAVBarrier(request.Acceleration);
                sData.CmdBuffer->UAVBarrier(request.Acceleration->GetScratch());
                sData.CmdBuffer->BuildAccelerationStructure(request.Acceleration);
                sData.CmdBuffer->UAVBarrier(request.Acceleration);
                sData.CmdBuffer->UAVBarrier(request.Acceleration->GetScratch());
                break;
            }
        }
    }

    sData.CmdBuffer->End();
    RHI::Submit({ sData.CmdBuffer });
    RHI::Wait();
    ClearRequests();
}

void Uploader::ClearRequests()
{
    sData.UploadBatchSize = 0;
    sData.BufferRequests = 0;
    sData.TextureRequests = 0;
    sData.ASRequests = 0;
    sData.CmdBuffer.reset();
    sData.Requests.clear();
}
