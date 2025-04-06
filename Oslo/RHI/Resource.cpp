//
// > Notice: Amélie Heinrich @ 2024
// > Create Time: 2024-12-03 10:44:01
//

#include "Resource.hpp"
#include "Utils.hpp"
#include "RHI.hpp"

#include <Core/UTF.hpp>
#include <Core/Assert.hpp>

Resource::Resource()
    : mResource(nullptr), mLayout(ResourceLayout::Common)
{
}

Resource::~Resource()
{
    if (mShouldFree) {
        D3DUtils::Release(mResource);
    }   
}

void Resource::SetName(const std::string& string)
{
    mName = string;
    mResource->SetName(UTF::AsciiToWide(string).data());
}

void Resource::CreateResource(D3D12_HEAP_PROPERTIES* heapProps, D3D12_RESOURCE_DESC* resourceDesc, D3D12_RESOURCE_STATES state)
{
    mLayout = ResourceLayout(state);
    HRESULT result = RHI::GetDevice()->GetDevice()->CreateCommittedResource(heapProps, D3D12_HEAP_FLAG_NONE, resourceDesc, state, nullptr, IID_PPV_ARGS(&mResource));
    ASSERT(SUCCEEDED(result), "Failed to allocate resource!");

    RHI::GetDevice()->GetDevice()->GetCopyableFootprints(resourceDesc, 0, resourceDesc->MipLevels, 0, nullptr, nullptr, nullptr, &mAllocSize);
}
