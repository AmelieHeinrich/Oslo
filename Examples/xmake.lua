--
-- > Notice: Amélie Heinrich @ 2025
-- > Create Time: 2025-04-06 10:38:15
--

target("Triangle")
    set_rundir("$(projectdir)/Examples")
    set_kind("binary")

    add_files("$(projectdir)/Examples/Triangle/**.cpp")
    add_includedirs("$(projectdir)")
    add_deps("Oslo")

target("Triangle")
    set_rundir("$(projectdir)/Examples")
    set_kind("binary")

    add_files("$(projectdir)/Examples/Raytracing/**.cpp")
    add_includedirs("$(projectdir)")
    add_deps("Oslo")
