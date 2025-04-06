--
-- > Notice: Amélie Heinrich @ 2025
-- > Create Time: 2025-04-06 10:38:15
--

add_rules("mode.debug", "mode.release", "mode.releasedbg")

includes("ThirdParty", "Examples")

target("Oslo")
    set_kind("static")
    set_languages("c++17")

    add_files("Oslo/**.cpp")
    add_headerfiles("Oslo/**.hpp")
    add_includedirs("Oslo/", { public = true })
    add_defines("USE_PIX", "GLM_ENABLE_EXPERIMENTAL", { public = true })
    add_deps(
        "CGLTF",
        "D3D12",
        "DXC",
        "GLM",
        "ImGui",
        "nvtt",
        "PIX",
        "SDL3",
        "STB",
        { public = true }
    )
    add_syslinks("d3d12", "dxgi", "user32")

    if is_mode("debug") then
        set_symbols("debug")
        set_optimize("none")
        add_defines("OSLO_DEBUG")
    end
    if is_mode("release") then
        set_symbols("hidden")
        set_optimize("fastest")
        set_strip("all")
    end
    if is_mode("releasedbg") then
        set_symbols("debug")
        set_optimize("fastest")
        set_strip("all")
        add_defines("OSLO_DEBUG")
    end

    before_link(function (target)
        os.cp("Binaries/*", "$(buildir)/$(plat)/$(arch)/$(mode)/")
    end)
