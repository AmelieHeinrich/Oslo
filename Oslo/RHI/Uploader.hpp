//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-04-06 16:39:02
//

#pragma once

#include "RHI.hpp"
#include "CommandBuffer.hpp"
#include "Resource.hpp"
#include "Queue.hpp"
#include "Buffer.hpp"
#include "AccelerationStructure.hpp"
#include "RHI.hpp"

#define KILOBYTES(s) s * 1024
#define MEGABYTES(s) KILOBYTES(s) * 1024
#define GIGABYTES(s) MEGABYTES(s) * 1024

class Uploader
{
public:
    static void Init();
    static void EnqueueTextureUpload(std::vector<uint8_t> buffer, std::shared_ptr<Resource> texture);
    static void EnqueueBufferUpload(void* data, uint64_t size, std::shared_ptr<Resource> buffer);
    static void EnqueueAccelerationStructureBuild(std::shared_ptr<AccelerationStructure> as);
    static void Flush();
    static void ClearRequests();

private:
    static constexpr uint64_t MAX_UPLOAD_BATCH_SIZE = MEGABYTES(512);

    enum class UploadRequestType
    {
        BufferCPUToGPU,
        TextureToGPU,
        BuildAS
    };

    struct UploadRequest
    {
        UploadRequestType Type;

        std::shared_ptr<Resource> Resource = nullptr;
        std::shared_ptr<Buffer> StagingBuffer = nullptr;
        std::shared_ptr<AccelerationStructure> Acceleration = nullptr;
    };

    static struct Data
    {
        std::shared_ptr<CommandBuffer> CmdBuffer = nullptr;
        std::vector<UploadRequest> Requests;

        int TextureRequests = 0;
        int BufferRequests = 0;
        int ASRequests = 0;
        int UploadBatchSize = 0;
    } sData;
};
