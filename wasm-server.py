# Python 3

import sys
import socketserver
from http.server import SimpleHTTPRequestHandler

class WasmHandler(SimpleHTTPRequestHandler):
    def end_headers(self):        
        # Include additional response headers here. CORS for example:
        # self.send_header('Access-Control-Allow-Origin', '*')
        self.send_header('Cross-Origin-Embedder-Policy', 'require-corp')
        self.send_header('Cross-Origin-Opener-Policy', 'same-origin')
        SimpleHTTPRequestHandler.end_headers(self)


# Python 3.7.5 adds in the WebAssembly Media Type. If this is an older
# version, add in the Media Type.
if sys.version_info < (3, 7, 5):
    WasmHandler.extensions_map['.wasm'] = 'application/wasm'


if __name__ == '__main__':
    PORT = 8000
    with socketserver.TCPServer(("", PORT), WasmHandler) as httpd:
        print("Listening on port {}.\nGo to http://localhost:{}\nPress Ctrl+C to stop.".format(PORT, PORT))
        httpd.serve_forever()