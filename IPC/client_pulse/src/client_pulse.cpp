#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/neutrino.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Pulse Client <client_pulse.cpp>\n");
        return 1;
    }

    int pid = atoi(argv[1]);
    int chid = atoi(argv[2]);
    int coid;

    coid = ConnectAttach(0, pid, chid, _NTO_SIDE_CHANNEL, 0); // 0, pid, chid, kernel index value, flags

    if (coid == -1) {
        perror("ConnectAttach");
        return EXIT_FAILURE;
    }

    printf("Pulse Client connected. Sending heartbeats every 2 seconds...\n");

    while (1) {
        MsgSendPulse(coid, 10, 15, 2002); // server id, priority, 8-bit pulse code, 32-bit pulse value
        sleep(2);
    }

    return 0;
}
