add_rules("mode.debug", "mode.release", "mode.coverage")
add_requires("doctest", "fmt")

set_languages("c++17")
add_includedirs("include", "../fractions-cpp/include")

if is_mode("coverage") then
    add_cxflags("-ftest-coverage", "-fprofile-arcs", {force = true})
end

if is_plat("linux") then
    add_cxflags("-Wconversion", {force = true})
    -- Termux/Android ships its libc++ headers under $PREFIX
    local prefix = os.getenv("PREFIX")
    if prefix then
        add_cxflags("-Wno-unused-command-line-argument", {force = true})
        add_sysincludedirs(prefix .. "/include/c++/v1", prefix .. "/include", {public = true})
    end
elseif is_plat("windows") then
    add_cxflags("/EHsc /utf-8 /W4 /WX /wd4702", {force = true})
end

target("test_rattrig")
    add_files("test/source/*.cpp")
    add_packages("doctest", "fmt")
    add_tests("default")

    -- rapidcheck is optionally provided by a CMake build
    local rapidcheck_dir = path.join(os.projectdir(), "build", "_deps", "rapidcheck-src")
    local rapidcheck_lib_dir = path.join(os.projectdir(), "build", "_deps", "rapidcheck-build")
    local rapidcheck_lib = nil

    if is_plat("windows") then
        rapidcheck_lib_dir = path.join(rapidcheck_lib_dir, "Release")
        rapidcheck_lib = path.join(rapidcheck_lib_dir, "rapidcheck.lib")
    else
        rapidcheck_lib = path.join(rapidcheck_lib_dir, "librapidcheck.a")
    end

    if os.isdir(rapidcheck_dir) and os.isfile(rapidcheck_lib) then
        add_includedirs(path.join(rapidcheck_dir, "include"))
        add_linkdirs(rapidcheck_lib_dir)
        add_links("rapidcheck")
        add_defines("RAPIDCHECK_H")
    end
