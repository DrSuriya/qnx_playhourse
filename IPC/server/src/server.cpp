#include <stdio.h>
#include <stdlib.h>
#include <sys/neutrino.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include "shared_header.hpp"

#define ATTACH_POINT "my_qnx_server"

int main() {
    my_msg_t msg_con;
	my_reply_t reply;
    name_attach_t *attach;

    if ((attach = name_attach(NULL, ATTACH_POINT, 0)) == NULL) { // dispatch, path, flags
    	return EXIT_FAILURE;
    }

    printf("Server active. My Server path %s \n", ATTACH_POINT);
    printf("Waiting for client heartbeats...\n");

    while (1) {
        int rcvid = MsgReceive(attach->chid, &msg_con, sizeof(msg_con), NULL);

        if (rcvid == -1) break;

        if (rcvid == 0) {
            printf("Pulse received (Code: %d, Value: %d)\n", msg_con.pulse.code, msg_con.pulse.value.sival_int);
        } else {
            printf("Message received (Text: '%s', Value: %d)\n", msg_con.msg.text, msg_con.msg.value);

            reply.status = true;
            snprintf(reply.reply_text, 64, "Acknowledged: %d", msg_con.msg.value);

            MsgReply(rcvid, 0, &reply, sizeof(reply));
        }
    }
    name_detach(attach, 0);
    return 0;
}
