#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"

int main() {
    system("cat sampledisk16_dup.raw > sampledisk16.raw");
    OS_mkdir("/new_dir");
    OS_creat("/new_file");
    OS_mkdir("/people/mzw7af");
    dirEnt* directories = OS_readDir("/");
    if (directories == NULL) {
        printf("NULL FOUND YAY\n");
        return 0;
    }
    for (int i = 0; i < 20; i++) {
        printf("%s\n", directories[i].dir_name);
    }
    OS_creat("/people/mzw7af/sensei.txt");
    directories = OS_readDir("/people/mzw7af");
    if (directories == NULL) {
        printf("NULL FOUND YAY\n");
        return 0;
    }
    for (int i = 0; i < 5; i++) {
        printf("%s\n", directories[i].dir_name);
    }

    int fd = OS_open("/people/mzw7af/sensei.txt");

    char* buff = "sensei is the best why are you so good at programming\n fill all the cups with knowledge";
    int bytes_write = OS_write(fd, buff, 500, 0);
    char buffer[500000];
    OS_read(fd, buffer, 5000000, 0);
    printf("%s\n", buffer);
    printf("%d\n", bytes_write);

    int fd2 = OS_open("/media/hearse-fail.jpg");
    char buffer2[500000];
    int bytes_read2 = OS_read(fd2, buffer2, 5000000, 0);

    OS_creat("/people/mzw7af/image.jpg");
    int fd3 = OS_open("/people/mzw7af/image.jpg");
    bytes_write = OS_write(fd3, buffer2, 500000, 0);


    char buffer3[500000];
    int bytes_read3 = OS_read(fd3, buffer3, 5000000, 0);
    FILE *fp;
    fp = fopen("mzw7af_fail.jpg", "w+");
    fwrite(buffer3, 100000, 1, fp);


}
