# examples/proxy/proxy_client.py - Job 指令下發模擬器

import json
import time

job = {
    "head": "0xabc123...",
    "seed": "0x0011223344556677",
    "target": "0x00000fffffffffff"
}

with open("../../current_job.json", "w") as f:
    json.dump(job, f, indent=2)

print("[JobCtl] ✅ Job 下發成功 -> current_job.json")
time.sleep(1)
