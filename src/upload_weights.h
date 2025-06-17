#ifndef UPLOAD_WEIGHTS_H
#define UPLOAD_WEIGHTS_H

#include <string>

// 將 share JSON 傳送給代理伺服器
// 傳回是否成功
bool upload_share(const std::string& share_json);

#endif
