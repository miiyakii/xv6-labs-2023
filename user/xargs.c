#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include <kernel/param.h>
char buf[1024];
int
main(int argc, char* argv[])
{
  if(argc <= 1) {
    fprintf(2, "usage: xargs command\n");
    //exit(1);
  }

  char* xargv[MAXARG];
  int i;
  int fd = 0;
  for(i = 0; i + 1 < argc; i++)
  {
    xargv[i] = argv[i + 1];
  }
  int n, m = 0;
  char* p, * q;
  while((n = read(fd, buf + m, sizeof(buf) - m - 1)) > 0) {
    m += n;
    buf[m] = '\0';
    //fprintf(2, "%d\n", m);
    p = buf;
    while((q = strchr(p, '\n')) != 0) {
      *q = 0;
      if(fork() == 0) {
        xargv[i] = p;
        exec(xargv[0], xargv);
        exit(0);
      }
      //printf("p: %s\n", p);
      p = q + 1;
    }
    if(m > 0) {
      m -= p - buf;
      memmove(buf, p, m);
    }
  }
  wait(0);
  return 0;
}
