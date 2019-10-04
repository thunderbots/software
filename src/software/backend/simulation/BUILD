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

cc_test(
    name = "ball_test",
    srcs = ["physics_ball_test.cpp"],
    deps = [
        ":ball",
        "//software/ai/world:ball",
        "@box2d",
        "@gtest//:gtest_main",
    ],
)

# TODO: remove
cc_binary(
    name = "simulator_test",
    srcs = ["simulator_test.cpp"],
    linkopts = [
        "-pthread",
    ],
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
