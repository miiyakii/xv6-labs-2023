#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
    int p[2];
    pipe(p);
    char buf[4];
    if(fork() == 0) {
        read(p[0],buf , 4);
        printf("%d: received %s\n",getpid(), buf);
        write(p[1], "pong", 4);
    } else {
        write(p[1], "ping", 4);
        read(p[0], buf, 4);
        printf("%d: received %s\n",getpid(), buf);

        wait(0);
    }
    exit(0);
}