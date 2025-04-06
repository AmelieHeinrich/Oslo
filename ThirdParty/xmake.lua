--
-- > Notice: Amélie Heinrich @ 2024
-- > Create Time: 2024-12-03 05:46:04
--

target("CGLTF")
    set_kind("static")
    add_files("$(projectdir)/ThirdParty/cgltf.c")

target("D3D12")
    set_kind("headeronly")
    add_headerfiles("$(projectdir)/ThirdParty/DirectX/include/Agility/**.h")
    add_includedirs("$(projectdir)/ThirdParty/DirectX/include", { public = true })

target("DXC")
    set_kind("headeronly")
    add_headerfiles("$(projectdir)/ThirdParty/DXC/include/DXC/*.h")
    add_includedirs("$(projectdir)/ThirdParty/DXC/include", { public = true })

target("GLM")
    set_kind("headeronly")
    add_headerfiles("$(projectdir)/ThirdParty/glm/glm/*.hpp")
    add_includedirs("$(projectdir)/ThirdParty/glm/", { public = true })

target("ImGui")
    set_kind("static")
    add_files("$(projectdir)/ThirdParty/ImGui/*.cpp", "$(projectdir)/ThirdParty/ImGui/backends/imgui_impl_sdl3.cpp", "$(projectdir)/ThirdParty/ImGui/backends/imgui_impl_dx12.cpp")
    add_includedirs("ImGui/", { public = true })
    add_deps("SDL3")

target("nvtt")
    set_kind("headeronly")
    add_headerfiles("$(projectdir)/ThirdParty/nvtt/nvtt/*.h")
    add_includedirs("$(projectdir)/ThirdParty/nvtt/", { public = true })
    add_syslinks("$(projectdir)/ThirdParty/nvtt/lib64/nvtt30205.lib", { public = true })

target("PIX")
    set_kind("headeronly")
    add_headerfiles("$(projectdir)/ThirdParty/PIX/include/**.h")
    add_includedirs("$(projectdir)/ThirdParty/PIX/include", { public = true })
    add_syslinks("$(projectdir)/ThirdParty/PIX/lib/WinPixEventRuntime.lib", { public = true })

target("SDL3")
    set_kind("headeronly")
    add_headerfiles("$(projectdir)/ThirdParty/SDL3/include/**.h")
    add_includedirs("$(projectdir)/ThirdParty/SDL3/include", { public = true })
    add_syslinks("$(projectdir)/ThirdParty/SDL3/lib/SDL3.lib", { public = true })

target("STB")
    set_kind("static")
    add_files("$(projectdir)/ThirdParty/stb.c")
    add_headerfiles("$(projectdir)/ThirdParty/stb/*.h")
    add_includedirs("$(projectdir)/ThirdParty/stb", { public = true })
