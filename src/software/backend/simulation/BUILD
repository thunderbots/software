package(default_visibility = ["//visibility:public"])

cc_library(
    name = "ball",
    srcs = ["physics_ball.cpp"],
    hdrs = ["physics_ball.h"],
    deps = [
        "//shared:constants",
        "//software/ai/world:ball",
        "//software/geom",
        "@box2d",
    ],
)

cc_binary(
    name = "simulator_test",
    srcs = ["simulator_test.cpp"],
    #    copts = [
    #        "-lpthread",
    #    ],
    deps = [
        ":simulator",
        "//software/ai/world:ball",
    ],
)

cc_library(
    name = "simulator",
    srcs = ["simulator.cpp"],
    hdrs = ["simulator.h"],
    deps = [
        ":ball",
        "//software/ai/world:ball",
        "//software/util/time:duration",
        "@box2d",
    ],
)
