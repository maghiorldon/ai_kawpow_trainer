// src/upload_weights.h - 權重上傳模組介面

#ifndef UPLOAD_WEIGHTS_H
#define UPLOAD_WEIGHTS_H

#include "gpu_model.h"

void upload_share(const Result& r, int step);

#endif // UPLOAD_WEIGHTS_H
