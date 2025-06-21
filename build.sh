#!/bin/bash

build_and_run.sh - 一鍵編譯並執行偽裝 KawPoW AI Miner

set -e

檢查 CMake 目錄

if [ ! -d build ]; then mkdir build fi cd build

生成 Makefile 並編譯

cmake .. make -j$(nproc)

echo "\n[INFO] ✓ 編譯完成，開始執行 AI 偽裝礦機..." ./ai_kawpow

