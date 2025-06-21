# examples/proxy/proxy_server.py - 偽裝版 Proxy Server

from flask import Flask, request, jsonify
import hmac, hashlib, json

app = Flask(__name__)
SECRET_TOKEN = b'mining-session-token-1234'

def verify_signature(data, sig):
    computed = hmac.new(SECRET_TOKEN, data.encode(), hashlib.sha256).hexdigest()
    return hmac.compare_digest(sig, computed)

@app.route('/upload', methods=['POST'])
def upload():
    try:
        payload = request.get_json()
        sig = payload.get('sig')
        data_raw = json.dumps(payload.get('data'), separators=(',', ':'))

        if not verify_signature(data_raw, sig):
            return jsonify({'error': 'invalid signature'}), 403

        print(f"[Proxy] ✅ Accepted: {payload['data']}")
        return jsonify({'status': 'synced', 'latency_ms': 21, 'checksum': 'ok'})

    except Exception as e:
        print(f"[Proxy] ❌ Error: {e}")
        return jsonify({'error': 'bad request'}), 400

if __name__ == '__main__':
    print("[Proxy] 🛡️ Secure AI job endpoint listening at http://0.0.0.0:8080")
    app.run(host='0.0.0.0', port=8080)
