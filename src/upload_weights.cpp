#include "upload_weights.h"
#include "log.h"
#include <curl/curl.h>

bool upload_share(const std::string& share_json) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        log_error("curl init failed");
        return false;
    }

    const char* proxy_url = "https://127.0.0.1:8443/upload"; // 代理伺服器位址與 API 路徑

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_URL, proxy_url);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, share_json.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)share_json.size());

    // 因為使用 self-signed cert (測試用)，關閉驗證（正式環境不要）
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

    CURLcode res = curl_easy_perform(curl);

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        log_error("upload_share failed: %s", curl_easy_strerror(res));
        return false;
    }

    log_info("upload_share succeeded: %s", share_json.c_str());
    return true;
}
