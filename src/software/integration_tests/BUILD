package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "integration_tests",
    srcs = ["integration_tests_main.cpp"],
    deps = [
        "//software:typedefs",
        "//software/ai:ai_wrapper",
        "//software/backend:simulator_backend",
        "//software/gui:visualizer_wrapper",
        "//software/util/logger",
        "//software/util/parameter:dynamic_parameters",
        "@boost//:program_options",
        "@g3log",
    ],
)
