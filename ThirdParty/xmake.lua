--
-- > Notice: Amélie Heinrich @ 2024
-- > Create Time: 2024-12-03 05:46:04
--

target("CGLTF")
    set_kind("static")
    add_files("$(scriptdir)/ThirdParty/cgltf.c")

target("D3D12")
    set_kind("headeronly")
    add_headerfiles("$(scriptdir)/ThirdParty/DirectX/include/Agility/**.h")
    add_includedirs("$(scriptdir)/ThirdParty/DirectX/include", { public = true })

target("DXC")
    set_kind("headeronly")
    add_headerfiles("$(scriptdir)/ThirdParty/DXC/include/DXC/*.h")
    add_includedirs("$(scriptdir)/ThirdParty/DXC/include", { public = true })
    add_syslinks("$(scriptdir)/ThirdParty/DXC/lib/dxcompiler.lib", { public = true })

target("GLM")
    set_kind("headeronly")
    add_headerfiles("$(scriptdir)/ThirdParty/glm/glm/*.hpp")
    add_includedirs("$(scriptdir)/ThirdParty/glm/", { public = true })

target("ImGui")
    set_kind("static")
    add_files("$(scriptdir)/ThirdParty/ImGui/*.cpp", "$(scriptdir)/ThirdParty/ImGui/backends/imgui_impl_sdl3.cpp", "$(scriptdir)/ThirdParty/ImGui/backends/imgui_impl_dx12.cpp")
    add_includedirs("ImGui/", { public = true })
    add_deps("SDL3")

target("nvtt")
    set_kind("headeronly")
    add_headerfiles("$(scriptdir)/ThirdParty/nvtt/nvtt/*.h")
    add_includedirs("$(scriptdir)/ThirdParty/nvtt/", { public = true })
    add_syslinks("$(scriptdir)/ThirdParty/nvtt/lib64/nvtt30205.lib", { public = true })

target("PIX")
    set_kind("headeronly")
    add_headerfiles("$(scriptdir)/ThirdParty/PIX/include/**.h")
    add_includedirs("$(scriptdir)/ThirdParty/PIX/include", { public = true })
    add_syslinks("$(scriptdir)/ThirdParty/PIX/lib/WinPixEventRuntime.lib", { public = true })

target("SDL3")
    set_kind("headeronly")
    add_headerfiles("$(scriptdir)/ThirdParty/SDL3/include/**.h")
    add_includedirs("$(scriptdir)/ThirdParty/SDL3/include", { public = true })
    add_syslinks("$(scriptdir)/ThirdParty/SDL3/lib/SDL3.lib", { public = true })

target("STB")
    set_kind("static")
    add_files("$(scriptdir)/ThirdParty/stb.c")
    add_headerfiles("$(scriptdir)/ThirdParty/stb/*.h")
    add_includedirs("$(scriptdir)/ThirdParty/stb", { public = true })
