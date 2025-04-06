//
// > Notice: Amélie Heinrich @ 2024
// > Create Time: 2024-12-03 10:03:19
//

#include "Fence.hpp"
#include "Utils.hpp"
#include "Queue.hpp"
#include "RHI.hpp"

#include <Core/Assert.hpp>

Fence::Fence()
    : mValue(0)
{
    HRESULT result = RHI::GetDevice()->GetDevice()->CreateFence(mValue, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&mFence));
    ASSERT(SUCCEEDED(result), "Failed to create fence!");
}

Fence::~Fence()
{
    D3DUtils::Release(mFence);
}

uint64_t Fence::Signal(std::shared_ptr<Queue> queue)
{
    mValue++;
    queue->GetQueue()->Signal(mFence, mValue);
    return mValue;
}

void Fence::Wait(uint64_t value)
{
    if (GetCompletedValue() < value) {
        HANDLE event = ::CreateEventA(nullptr, false, false, "Fence Wait Event");
        mFence->SetEventOnCompletion(value, event);
        if (::WaitForSingleObject(event, 10'000'000) == WAIT_TIMEOUT) {
            ASSERT(false, "!! GPU TIME-OUT !!");
        }
    }
}
