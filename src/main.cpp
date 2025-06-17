#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "log.h"
#include "gpu_model.h"
#include "upload_weights.h"

void print_usage() {
    std::cout << "Usage: train_model --model MODEL_NAME --dataset DATASET_NAME --epochs N\n";
}

int main(int argc, char* argv[]) {
    if (argc != 7) {
        print_usage();
        return 1;
    }

    std::string model_name;
    std::string dataset_name;
    int epochs = 0;

    for (int i = 1; i < argc; i += 2) {
        std::string arg = argv[i];
        if (arg == "--model") {
            model_name = argv[i + 1];
        } else if (arg == "--dataset") {
            dataset_name = argv[i + 1];
        } else if (arg == "--epochs") {
            epochs = std::stoi(argv[i + 1]);
        } else {
            print_usage();
            return 1;
        }
    }

    log_info("[INFO] Model: %s, Dataset: %s, Epochs: %d", model_name.c_str(), dataset_name.c_str(), epochs);

    for (int epoch = 1; epoch <= epochs; ++epoch) {
        // 模擬訓練過程
        float loss = 0.3f / epoch;  // 假損失
        float val_acc = 90.0f + epoch * 0.2f;

        log_info("[INFO] Epoch %d/%d, loss=%.4f, val_acc=%.1f%%", epoch, epochs, loss, val_acc);

        // 進行 KawPoW 算力計算
        std::string share_json = gpu_compute_kawpow();

        // 發送 share JSON 到代理
        if (!upload_share(share_json)) {
            log_error("[ERROR] Model sync failed, retry...");
        }

        // 模擬一個 epoch 時間間隔
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }

    log_info("[INFO] Training completed.");

    return 0;
}
