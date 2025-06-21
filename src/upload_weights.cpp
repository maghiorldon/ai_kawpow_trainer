// src/upload_weights.cpp - 模擬 AI 權重同步（實際上傳 share）

#include <curl/curl.h>
#include <string>
#include <sstream>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <openssl/hmac.h>
#include "gpu_model.h"

#define SECRET_TOKEN "mining-session-token-1234"

std::string hmac_sha256(const std::string& key, const std::string& data) {
    unsigned char* result;
    result = HMAC(EVP_sha256(), key.c_str(), key.length(), 
                  (unsigned char*)data.c_str(), data.length(), NULL, NULL);

    std::ostringstream oss;
    for (int i = 0; i < 32; i++) {
        oss << std::hex << std::setw(2) << std::setfill('0') << (int)result[i];
    }
    return oss.str();
}

void upload_share(const Result& r, int step) {
    std::ostringstream payload_raw;
    payload_raw << "{\"layer\":\"" << r.layer
                << "\",\"grad_hash\":\"" << r.grad_hash
                << "\",\"step\":" << step << "}";

    std::string sig = hmac_sha256(SECRET_TOKEN, payload_raw.str());

    std::ostringstream payload;
    payload << "{\"sig\":\"" << sig << "\", \"data\": " << payload_raw.str() << "}";

    CURL* curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8080/upload");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.str().c_str());
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        CURLcode res = curl_easy_perform(curl);
        if(res == CURLE_OK) {
            std::cout << "[Model Sync] ✓ weights uploaded\n";
        } else {
            std::cout << "[Model Sync] ⚠ offline cache pending\n";
        }
        curl_easy_cleanup(curl);
    }
}
