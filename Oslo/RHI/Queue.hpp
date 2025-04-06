//
// > Notice: Amélie Heinrich @ 2024
// > Create Time: 2024-12-03 10:08:14
//

#pragma once

#include <RHI/Device.hpp>
#include <vector>
#include <memory>

class Fence;
class CommandBuffer;

enum class QueueType
{
    AllGraphics = D3D12_COMMAND_LIST_TYPE_DIRECT,
    Compute = D3D12_COMMAND_LIST_TYPE_COMPUTE,
    Copy = D3D12_COMMAND_LIST_TYPE_COPY,
    VideoDecode = D3D12_COMMAND_LIST_TYPE_VIDEO_DECODE,
    VideoEncode = D3D12_COMMAND_LIST_TYPE_VIDEO_ENCODE
};

class Queue
{
public:
    Queue(QueueType type);
    ~Queue();

    void Wait(std::shared_ptr<Fence> fence, uint64_t value);
    void Signal(std::shared_ptr<Fence> fence, uint64_t value);
    void Submit(const std::vector<std::shared_ptr<CommandBuffer>>& buffers);

    ID3D12CommandQueue* GetQueue() { return mQueue; }
    QueueType GetType() { return mType; }
private:
    ID3D12CommandQueue* mQueue = nullptr;
    QueueType mType;
};
