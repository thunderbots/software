package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "simulator_test",
    srcs = ["simulator_main.cpp"],
    deps = [
        "@reactphysics",
    ],
)

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
    name = "box2d_test",
    srcs = ["box2d_main.cpp"],
    deps = [
        #        ":ball",
        ":simulator",
        #        "//software/ai/world:ball",
        #        "//software/geom",
        #        "@box2d",
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
