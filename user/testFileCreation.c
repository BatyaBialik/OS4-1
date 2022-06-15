#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define TOTAL_FILE_SIZE (1<<20)

#define BSIZE 1024  // block size
#define NDIRECT 12
#define NINDIRECT (BSIZE / sizeof(uint))
#define NDINDIRECT (NINDIRECT * NINDIRECT)

int main(int argc, char** argv){
    char buffer[BSIZE];
    int fd = open("testFile",O_CREATE | O_RDWR);
    printf("Writing to direct blocks\n");
    for(int i=0;i<NDIRECT; i++){
        if(write(fd,buffer,BSIZE)<0){
            exit(-1);
        }
    }
    printf("Finished writing 12KB (direct)\n");
    printf("Writing to indirect blocks\n");
    for(int i=0;i<NINDIRECT; i++){
        if(write(fd,buffer,BSIZE)<0){
            exit(-1);
        }
    }
    printf("Finished writing 258KB (single indirect)\n");
    printf("Writing to double indirect blocks\n");
    int goalSize = 10240 - (NINDIRECT+NDIRECT);
    for(int i=0;i<NDINDIRECT;i++){
        if (i%1000 == 0)
        {
            printf("writing double block number %d\n",i);
        }
        if (goalSize == 0){
            break;
        }
        if(write(fd,buffer,BSIZE)<0){
            exit(-1);
        }
        goalSize -=1;
    }
    printf("Finished writing 10MB (double indirect)\n");
    close(fd);
    exit(0);
}