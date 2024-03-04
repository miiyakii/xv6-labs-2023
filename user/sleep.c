#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int i;
    
  for(i = 1; i < argc; i++){
    int time = atoi(argv[i]);
    sleep(time);
  }
  exit(0);
}
