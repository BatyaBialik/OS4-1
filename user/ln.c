#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc != 3 && argc != 4){
    printf("Usage: ln old new OR ls -s old new\n");
    exit(0);
  }
  char* oldp;
  char* newp;
  if(argc == 3)
  {
    oldp = argv[1];
    newp = argv[2];
    if (link(oldp,newp) < 0) {
      printf("link %s %s: failed\n", oldp, newp);
    }
    exit(0);
  }
  if(!strcmp(argv[1], "-s"))
  {
    oldp = argv[2];
    newp = argv[3];
    if (symlink(oldp, newp) != 0) {
      printf("symlink %s %s: failed\n", oldp, newp);
    }
    exit(0);
  }
  printf("wrong arguments for ln");
  exit(0);
  }

