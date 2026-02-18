#pragma once

#define ATTACH_POINT "my_qnx_server"

typedef struct {
    uint16_t type; // 1 for command processor and 2 for sensor processor, rest for anything else
    struct _pulse pulse; // pulse
    char text[64]; // string data
    int value; // int data
} my_client_msg_t;

typedef struct {
    union {
        struct _pulse pulse; // rcvid == 0
        my_client_msg_t  msg;   // rcvid > 0
    };
} my_msg_t;

typedef struct {
    bool status; // True all good, false something came up
    char reply_text[64];
} my_reply_t;
