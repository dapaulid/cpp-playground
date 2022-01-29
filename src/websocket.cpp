#include <emscripten/emscripten.h>
#include <emscripten/websocket.h>
#include <emscripten/threading.h>
#include <stdio.h>

#include <chrono>
#include <thread>

#include "threadinfo.h"

void print_thread() {
	printf("runtime: %d, browser: %d, name: %s\n",
		emscripten_is_main_runtime_thread(), emscripten_is_main_browser_thread(), ThreadInfo::current().get_name().c_str());
}

EM_BOOL onopen(int eventType, const EmscriptenWebSocketOpenEvent *websocketEvent, void *userData) {
    puts("onopen");
	print_thread();

    EMSCRIPTEN_RESULT result;
    result = emscripten_websocket_send_utf8_text(websocketEvent->socket, "hoge");
    if (result) {
        printf("Failed to emscripten_websocket_send_utf8_text(): %d\n", result);
    }
    return EM_TRUE;
}
EM_BOOL onerror(int eventType, const EmscriptenWebSocketErrorEvent *websocketEvent, void *userData) {
    puts("onerror");
	

    return EM_TRUE;
}
EM_BOOL onclose(int eventType, const EmscriptenWebSocketCloseEvent *websocketEvent, void *userData) {
    printf("onclose: %d (%s)\n", websocketEvent->code, websocketEvent->reason);

    return EM_TRUE;
}
EM_BOOL onmessage(int eventType, const EmscriptenWebSocketMessageEvent *websocketEvent, void *userData) {
    puts("onmessage");
    if (websocketEvent->isText) {
        // For only ascii chars.
        printf("message: %s\n", websocketEvent->data);
    }
/*
    EMSCRIPTEN_RESULT result;
    result = emscripten_websocket_close(websocketEvent->socket, 1000, "no reason");
    if (result) {
        printf("Failed to emscripten_websocket_close(): %d\n", result);
    }
*/
    return EM_TRUE;
}

int main() {
    if (!emscripten_websocket_is_supported()) {
        return 0;
    }
	print_thread();
    EmscriptenWebSocketCreateAttributes ws_attrs = {
        "ws://localhost:8080",
        NULL,
        EM_TRUE
    };

    EMSCRIPTEN_WEBSOCKET_T ws = emscripten_websocket_new(&ws_attrs);
    emscripten_websocket_set_onopen_callback(ws, NULL, onopen);
    emscripten_websocket_set_onerror_callback(ws, NULL, onerror);
    emscripten_websocket_set_onclose_callback(ws, NULL, onclose);
    emscripten_websocket_set_onmessage_callback(ws, NULL, onmessage);

	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	printf("bye\n");
}