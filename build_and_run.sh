#!/bin/bash

# 安裝必要套件
sudo apt update
sudo apt install -y build-essential cmake libssl-dev python3 python3-pip

# 建立 build 目錄
mkdir -p build
cd build

# 產生 Makefile
cmake ..

# 編譯
make -j$(nproc)

cd ..

echo "[INFO] 編譯完成，執行檔位於 ./build/train_model"
