project "jpeg"
    language "C++"
    kind "StaticLib"
    targetname "jpeg"
    
    vpaths {
        ["Headers/*"] = "**.h",
        ["Sources/*"] = "**.c",
        ["*"] = "premake5.lua"
    }
    
    files {
        "premake5.lua",
        "jaricom.c",
        "jcapimin.c",
        "jcapistd.c",
        "jcarith.c",
        "jccoefct.c",
        "jccolor.c",
        "jcdctmgr.c",
        "jchuff.c",
        "jcinit.c",
        "jcmainct.c",
        "jcmarker.c",
        "jcmaster.c",
        "jcomapi.c",
        "jcparam.c",
        "jcprepct.c",
        "jcsample.c",
        "jctrans.c",
        "jdapimin.c",
        "jdapistd.c",
        "jdarith.c",
        "jdatadst.c",
        "jdatasrc.c",
        "jdcoefct.c",
        "jdcolor.c",
        "jddctmgr.c",
        "jdhuff.c",
        "jdinput.c",
        "jdmainct.c",
        "jdmarker.c",
        "jdmaster.c",
        "jdmerge.c",
        "jdpostct.c",
        "jdsample.c",
        "jdtrans.c",
        "jerror.c",
        "jfdctflt.c",
        "jfdctfst.c",
        "jfdctint.c",
        "jidctflt.c",
        "jidctfst.c",
        "jidctint.c",
        "jmemmgr.c",
        "jmemnobs.c",
        "jquant1.c",
        "jquant2.c",
        "jutils.c",
        "jconfig.h",
        "jdct.h",
        "jerror.h",
        "jmemsys.h",
        "jmorecfg.h",
        "jpegint.h",
        "jpeglib.h",
        "jversion.h"
    }
    
    filter "architecture:x64"
        flags { "ExcludeFromBuild" }
    filter "system:not windows"
        flags { "ExcludeFromBuild" }
