#include <stdio.h>
#include <unistd.h>
#include "main.h"

int main() {
    OS_cd("MEDIA");
    int fd = OS_open("404-FAILJPG");
    char buffer[500000];
    int bytes_read = OS_read(fd, buffer, 5000000, 0);
    printf("%s\n", buffer);
    printf("%d\n", bytes_read);

    // writing buffer to a file
    FILE *fp;
    fp = fopen("fail.jpg", "w+");
    fwrite(buffer, 100000, 1, fp);

    dirEnt* directories = OS_readDir("../MEDIA");
    if (directories == NULL) {
        printf("NULL FOUND YAY\n");
        return 0;
    }
    for (int i = 0; i < 100; i++) {
        printf("%s\n", directories[i].dir_name);
    }

    OS_cd("PEOPLE");
    OS_cd("ABK2Y/");
    OS_cd("/");
    OS_cd("PEOPLE/ABK2Y");

}
