#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void work(int* p)
{
  int n;
  //int p1[2];
  int rd, wd;
  rd = p[0];
  wd = p[1];
  int isPrime = 1;
  int prime;
  while(read(rd, &n, sizeof(n)) != 0)
  {
    if(isPrime == 1) {
      printf("prime %d\n", n);
      prime = n;
      int p1[2];
      pipe(p1);
      if(fork() != 0) {
        isPrime = 0;
        close(p1[0]);
        wd = p1[1];
      }
      else {
        close(p1[1]);
        rd = p1[0];
      }
    }
    else {
      if(n % prime != 0) {
        write(wd, &n, sizeof(n));
      }
    }
  }
  close(rd);
  close(wd);
  wait(0);
}

int main(int argc, char* argv[])
{
  int p[2];
  pipe(p);
  int i;
  if(fork() == 0) {
    close(p[1]);
    int n;
    //int p1[2];
    int rd, wd;
    rd = p[0];
    wd = p[1];
    int isPrime = 1;
    int prime;
    while(read(rd, &n, sizeof(n)) != 0)
    {
      if(isPrime == 1) {
        printf("prime %d\n", n);
        prime = n;
        int p1[2];
        pipe(p1);
        if(fork() != 0) {
          isPrime = 0;
          close(p1[0]);
          wd = p1[1];
        }
        else {
          close(p1[1]);
          rd = p1[0];
        }
      }
      else {
        if(n % prime != 0) {
          write(wd, &n, sizeof(n));
        }
      }
    }
    close(rd);
    close(wd);
  }
  else {
    close(p[0]);
    for(i = 2; i <= 35; i++)
    {
      write(p[1], &i, sizeof(i));
    }
    close(p[1]);
  }
  wait(0);
  return 0;
}
