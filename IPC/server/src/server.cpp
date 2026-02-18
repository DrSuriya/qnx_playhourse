#include <stdio.h>
#include <stdlib.h>
#include <sys/neutrino.h>
#include <process.h>

int main() {
    int chid;
    struct _pulse pulse;

    chid = ChannelCreate(0);
    if (chid == -1) {
        perror("ChannelCreate");
        return EXIT_FAILURE;
    }

    printf("Server active. My Process ID (PID) is: %d, My Channel ID (chid) is: %d\n", getpid(), chid);
    printf("Waiting for client heartbeats...\n");

    while (1) {
        int rcvid = MsgReceive(chid, &pulse, sizeof(pulse), NULL); // chid, msg, msg size, msg info

        if (rcvid == 0) {
            printf("Heartbeat received (Code: %d, Value: %d)\n", pulse.code, pulse.value.sival_int);
        }
    }
    return 0;
}
