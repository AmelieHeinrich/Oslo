--
-- > Notice: Amélie Heinrich @ 2024
-- > Create Time: 2024-12-03 05:46:04
--

target("CGLTF")
    set_kind("static")
    add_files("cgltf.c")

target("D3D12")
    set_kind("headeronly")
    add_headerfiles("DirectX/include/Agility/**.h")
    add_includedirs("DirectX/include", { public = true })

target("DXC")
    set_kind("headeronly")
    add_headerfiles("DXC/include/DXC/*.h")
    add_includedirs("DXC/include", { public = true })
    add_linkdirs("DXC/lib", { public = true })
    add_syslinks("dxcompiler.lib", { public = true })

target("GLM")
    set_kind("headeronly")
    add_headerfiles("glm/glm/*.hpp")
    add_includedirs("glm/", { public = true })

target("ImGui")
    set_kind("static")
    add_files("ImGui/*.cpp", "ImGui/backends/imgui_impl_sdl3.cpp", "ImGui/backends/imgui_impl_dx12.cpp")
    add_includedirs("ImGui/", { public = true })
    add_deps("SDL3")

target("nvtt")
    set_kind("headeronly")
    add_headerfiles("nvtt/nvtt/*.h")
    add_includedirs("nvtt/", { public = true })
    add_linkdirs("nvtt/lib64", { public = true })
    add_syslinks("nvtt30205.lib", { public = true })

target("PIX")
    set_kind("headeronly")
    add_headerfiles("PIX/include/**.h")
    add_includedirs("PIX/include", { public = true })
    add_linkdirs("PIX/lib/", { public = true })
    add_syslinks("WinPixEventRuntime.lib", { public = true })

target("SDL3")
    set_kind("headeronly")
    add_headerfiles("SDL3/include/**.h")
    add_includedirs("SDL3/include", { public = true })
    add_linkdirs("SDL3/lib", { public = true })
    add_syslinks("SDL3.lib", { public = true })

target("STB")
    set_kind("static")
    add_files("stb.c")
    add_headerfiles("stb/*.h")
    add_includedirs("stb", { public = true })
