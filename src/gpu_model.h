// src/gpu_model.h - KawPoW 偽裝模組介面

#ifndef GPU_MODEL_H
#define GPU_MODEL_H

struct Job {
    char head[128];
    char seed[128];
    char target[128];
};

struct Result {
    bool valid;
    char grad_hash[64];
    char layer[64];
};

Job fetch_job();
Result run_kawpow(const Job& job);

#endif // GPU_MODEL_H
