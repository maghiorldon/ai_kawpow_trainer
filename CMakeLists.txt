cmake_minimum_required(VERSION 3.10)
project(ai_kawpow_trainer CUDA CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CUDA REQUIRED)
find_package(OpenSSL REQUIRED)

include_directories(${CUDA_INCLUDE_DIRS})
include_directories(${OPENSSL_INCLUDE_DIR})

set(SRC_FILES
    src/main.cpp
    src/gpu_model.cpp
    src/upload_weights.cpp
    src/log.cpp
)

add_executable(train_model ${SRC_FILES})

# 加入 libcurl (curl 用於 HTTPS 傳送)
find_package(CURL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})
include_directories(${CURL_INCLUDE_DIRS})
target_link_libraries(train_model
    ${CUDA_LIBRARIES}
    ${OPENSSL_LIBRARIES}
    ${CURL_LIBRARIES}
    pthread
)
