add_rules("mode.debug", "mode.release")
add_requires("fmt")
add_requires("doctest")

rule("test")
    on_run(function (target)
        os.exec("%s", target:targetfile())
    end)

target("test_rattrig")
    set_kind("binary")
    add_rules("test")
    add_files("test/source/*.cpp")
    add_packages("fmt", "doctest")
    add_includedirs("include", {public = true})
    add_includedirs("../fractions-cpp/include", {public = true})

add_tests("test_rattrig")
