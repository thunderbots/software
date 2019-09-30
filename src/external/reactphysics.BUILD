# Description:
#   This library provides us with a 3d physics engine
#   https://github.com/DanielChappuis/reactphysics3d

cc_library(
    name = "reactphysics",
    srcs = glob(["src/**/*.cpp"]),
    hdrs = glob(["src/**/*.h"]),
    includes = [
        "./src",
        "./src/body",
        "./src/collision",
        "./src/collision/broadphase",
        "./src/collision/narrowphase",
        "./src/collision/narrowphase",
        "./src/collision/narrowphase/GJK",
        "./src/collision/narrowphase/SAT",
        "./src/collision/shapes",
        "./src/constraint",
        "./src/containers",
        "./src/engine",
        "./src/mathematics",
        "./src/memory",
        "./src/util",
    ],
    visibility = ["//visibility:public"],
)
