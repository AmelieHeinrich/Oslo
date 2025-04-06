//
// > Notice: Amélie Heinrich @ 2024
// > Create Time: 2024-12-03 10:11:31
//

#include "Queue.hpp"
#include "Utils.hpp"
#include "Fence.hpp"
#include "RHI.hpp"
#include "CommandBuffer.hpp"

#include <Core/Assert.hpp>

Queue::Queue(QueueType type)
    : mType(type)
{
    D3D12_COMMAND_QUEUE_DESC desc = {};
    desc.Type = D3D12_COMMAND_LIST_TYPE(type);

    HRESULT result = RHI::GetDevice()->GetDevice()->CreateCommandQueue(&desc, IID_PPV_ARGS(&mQueue));
    ASSERT(SUCCEEDED(result), "Failed to create queue!");
}

Queue::~Queue()
{
    D3DUtils::Release(mQueue);
}

void Queue::Wait(std::shared_ptr<Fence> fence, uint64_t value)
{
    mQueue->Wait(fence->GetFence(), value);
}

void Queue::Signal(std::shared_ptr<Fence> fence, uint64_t value)
{
    mQueue->Signal(fence->GetFence(), value);
}

void Queue::Submit(const std::vector<std::shared_ptr<CommandBuffer>>& buffers)
{
    std::vector<ID3D12CommandList*> lists;
    for (auto& buffer : buffers) {
        lists.push_back(buffer->GetList());
    }

    mQueue->ExecuteCommandLists(lists.size(), lists.data());
}
