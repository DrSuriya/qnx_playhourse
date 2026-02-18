#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/neutrino.h>
#include <sys/dispatch.h>
#include <sys/iofunc.h>


#define ATTACH_POINT "my_qnx_server"

int main() {
	int coid;

    if ((coid = name_open(ATTACH_POINT, 0)) == -1) {
    	return EXIT_FAILURE;
	}
    printf("Pulse Client connected. Sending heartbeats every 2 seconds...\n");

    while (1) {
        MsgSendPulse(coid, 10, 15, 2002); // server id, priority, 8-bit pulse code, 32-bit pulse value
        sleep(2);
    }

    name_close(coid);

    return 0;
}
