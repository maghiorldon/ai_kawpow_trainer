// src/log.h - 訓練過程輸出模擬介面

#ifndef LOG_H
#define LOG_H

#include "gpu_model.h"

void log_device_info();
void log_training_step(int step);
void log_shard_sync(const Result& r, int step);

#endif // LOG_H
