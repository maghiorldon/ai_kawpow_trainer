# CMakeLists.txt - AI偽裝版 KawPoW Miner 編譯設定

cmake_minimum_required(VERSION 3.10)
project(ai_kawpow LANGUAGES C CXX CUDA)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CUDA_STANDARD 11)

# CUDA 編譯設定
enable_language(CUDA)
find_package(CUDA REQUIRED)

# OpenSSL 與 libcurl
find_package(OpenSSL REQUIRED)
find_package(CURL REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(ai_kawpow
  src/main.cpp
  src/gpu_model.cu
  src/log.cpp
  src/upload_weights.cpp
)

# 連結必要的函式庫
target_link_libraries(ai_kawpow
  CUDA::cudart
  OpenSSL::SSL
  OpenSSL::Crypto
  CURL::libcurl
)
