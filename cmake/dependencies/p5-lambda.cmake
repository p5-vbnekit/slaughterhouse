include("FetchContent")

FetchContent_Declare(
    "p5-lambda"
    GIT_REPOSITORY "https://github.com/p5-vbnekit/lambda.prototypes"
    GIT_TAG "3cf22a5f2bc6a2b88868c80e7dde023cd9a784c8"
)

FetchContent_MakeAvailable("p5-lambda")
