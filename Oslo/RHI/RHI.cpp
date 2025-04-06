//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-04-06 12:20:53
//

#include "RHI.hpp"

RHI::Data RHI::sData;

void RHI::Init()
{
    sData.Device = std::make_shared<Device>();
}

void RHI::Exit()
{

}
