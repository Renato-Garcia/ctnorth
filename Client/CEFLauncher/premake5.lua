project "CEFLauncher"
    language "C++"
    kind "WindowedApp"
    targetname "CEFLauncher"
    targetdir(buildpath("SAO/cef"))
    
    links { "CEFLauncherDLL" }
    flags { "WinMain" }
    
    vpaths { 
        ["Headers/*"] = "**.hpp",
        ["Sources/*"] = "**.cpp",
        ["Resources/*"] = {"**.rc", "res/sao.ico"},
        ["*"] = "premake5.lua"
    }
    
    files {
        "premake5.lua",
        "*.hpp",
        "*.cpp",
        "**.rc",
        "**.ico"
    }
    
    filter "architecture:x64"
        flags { "ExcludeFromBuild" }

    filter "system:not windows"
        flags { "ExcludeFromBuild" }