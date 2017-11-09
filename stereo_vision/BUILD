cc_binary(
    name = "main",
    srcs = [
        "main.cc",
    ],
    deps = [
        "@opencv//:opencv_library",
        "//stereo_vision:stereo_vision",
    ],
    linkopts = [
        "-lstdc++fs",
    ]
)

cc_library(
    name = "stereo_vision",
    srcs = [
        "stereo_vision.cc",
        "stereo_vision.h",
    ]
)

