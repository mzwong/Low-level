#include <stdio.h>
#include <unistd.h>
#include "main.h"

int main() {
    int fd = OS_open("/PEOPLE/ABK2Y/COFFEE~1TXT");
    char buffer[500000];
    int bytes_read = OS_read(fd, buffer, 5000000, 0);
    //int bytes_read = read(fd, buffer, 5000000);
    printf("%s\n", buffer);
    printf("%d\n", bytes_read);

    // // writing buffer to a file
    // FILE *fp;
    // fp = fopen("fail.jpg", "w+");
    // fwrite(buffer, 100000, 1, fp);

    dirEnt* directories = OS_readDir("/PEOPLE/ABK2Y");
    if (directories == NULL) {
        printf("NULL FOUND YAY\n");
        return 0;
    }
    for (int i = 0; i < 100; i++) {
        printf("%s\n", directories[i].dir_name);
    }

}
