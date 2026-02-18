#include <stdio.h>
#include <stdlib.h>
#include <sys/neutrino.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>

#define ATTACH_POINT "my_qnx_server"

int main() {
    struct _pulse pulse;

    name_attach_t *attach;

    if ((attach = name_attach(NULL, ATTACH_POINT, 0)) == NULL) { // dispatch, path, flags
    	return EXIT_FAILURE;
    }

    printf("Server active. My Server path %s \n", ATTACH_POINT);
    printf("Waiting for client heartbeats...\n");

    while (1) {
        int rcvid = MsgReceive(attach->chid, &pulse, sizeof(pulse), NULL); // chid, msg, msg size, msg info

        if (rcvid == 0) {
            printf("Heartbeat received (Code: %d, Value: %d)\n", pulse.code, pulse.value.sival_int);
        }
    }
    name_detach(attach, 0);
    return 0;
}
