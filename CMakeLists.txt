cmake_minimum_required(VERSION 3.18)
project(ai_kawpow LANGUAGES C CXX CUDA)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CUDA_STANDARD 14)

# 指定支援哪些 CUDA 架構（根據你實際使用的卡）
set(CMAKE_CUDA_ARCHITECTURES 75 80 86)  # 75=RTX20, 80=A100, 86=RTX30, 89=RTX40

# 開啟 CUDA 支援
enable_language(CUDA)

# 尋找 CUDA Toolkit
find_package(CUDAToolkit REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(CURL REQUIRED)
# 加入所有源碼
add_executable(ai_kawpow
  src/main.cpp
  src/gpu_model.cu
  src/upload_weights.cpp
  src/log.cpp
)

# CUDA 靜態連結
target_link_libraries(ai_kawpow 
	PRIVATE 
	  CUDA::cudart
	  OpenSSL::SSL
          OpenSSL::Crypto
          CURL::libcurl
  )

