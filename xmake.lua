
add_rules("mode.debug", "mode.release")

set_targetdir("bin")
set_objectdir("bin-int")
set_rundir(".")

set_warnings("allextra", "error")
set_languages("clatest")
add_defines("_CRT_SECURE_NO_WARNINGS")
set_toolchains("gcc")

target("nox")
    set_kind("binary")
    add_files("nox/**.c")
    add_includedirs("nox")

    add_links("kernel32")
    add_ldflags("-nodefaultlibs", "-nostartfiles", "-e__init", {force = true})
