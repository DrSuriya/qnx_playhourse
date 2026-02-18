#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/neutrino.h>
#include <sys/dispatch.h>
#include <sys/iofunc.h>
#include "shared_header.hpp"

int main() {
	int coid;
	my_msg_t msg_con;
	my_reply_t reply;

    if ((coid = name_open(ATTACH_POINT, 0)) == -1) {
    	return EXIT_FAILURE;
	}
    printf("Message Client connected. Sending heartbeats every 2 seconds...\n");

    msg_con.msg.type = 1; // example for now
    msg_con.msg.value = 2002;
    strncpy(msg_con.msg.text, "Hello from the message client!", 64);

    while (1) {
        int status = MsgSend(coid, &msg_con.msg, sizeof(msg_con.msg), &reply, sizeof(reply));

        if (status == -1) {
			perror("MsgSend");
		} else {
			printf("Server replied: %s (Status: %d)\n", reply.reply_text, reply.status);
		}
        sleep(2);
    }

    name_close(coid);
    return 0;
}
