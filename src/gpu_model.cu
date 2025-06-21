// src/gpu_model.cu - CUDA KawPoW 偽裝 AI forward kernel

#include <cuda.h>
#include <curand_kernel.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include "gpu_model.h"

using json = nlohmann::json;

__global__ void kawpow_kernel(int* results, uint64_t seed, uint64_t target) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x;
    uint64_t hash = seed ^ (idx * 0xABCDEF1234567890ULL);
    if ((hash & 0xFFFFFFFFFFFFULL) < target) {
        results[0] = idx;
    }
}

Job fetch_job() {
    Job job;
    std::ifstream f("current_job.json");
    if (!f.is_open()) throw std::runtime_error("No job file.");
    json j;
    f >> j;
    strcpy(job.head, j["head"].get<std::string>().c_str());
    strcpy(job.seed, j["seed"].get<std::string>().c_str());
    strcpy(job.target, j["target"].get<std::string>().c_str());
    return job;
}

Result run_kawpow(const Job& job) {
    Result r;
    int* d_result;
    cudaMalloc(&d_result, sizeof(int));
    cudaMemset(d_result, -1, sizeof(int));

    // 模擬解碼
    uint64_t seed = 0xabcdef;
    uint64_t target = 0x00000fffffffffff;

    kawpow_kernel<<<64, 128>>>(d_result, seed, target);
    int h_result = -1;
    cudaMemcpy(&h_result, d_result, sizeof(int), cudaMemcpyDeviceToHost);
    cudaFree(d_result);

    r.valid = (h_result != -1);
    snprintf(r.grad_hash, sizeof(r.grad_hash), "0x%08x", h_result);
    snprintf(r.layer, sizeof(r.layer), "block_%d.ffn", h_result % 24);
    return r;
}
