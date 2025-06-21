// src/log.cpp - 模擬 Transformer-style 模型訓練輸出

#include <iostream>
#include <iomanip>
#include "gpu_model.h"
#include "log.h"

void log_device_info() {
    std::cout << "[Env] Using device: NVIDIA A100, batch_size=64" << std::endl;
}

void log_training_step(int step) {
    float loss = 0.35f - (step % 10) * 0.0123f;
    float acc = 88.1f + (step % 7) * 0.5f;
    std::cout << "[Train] Step " << step
              << " | loss=" << std::fixed << std::setprecision(4) << loss
              << " | val_acc=" << std::fixed << std::setprecision(2) << acc << "%"
              << std::endl;
}

void log_shard_sync(const Result& r, int step) {
    std::cout << "[Sync] layer: " << r.layer
              << ", hash: " << r.grad_hash
              << ", step: " << step << std::endl;
}
