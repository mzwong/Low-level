#include <stdio.h>
#include <unistd.h>
#include "main.h"

int main() {
    OS_cd("MEDIA");
    int fd = OS_open("/PEOPLE/ABK2Y/COFFEE~1TXT");
    int fd2 = OS_open("HEARSE~1JPG");
    char buffer[500000];
    char buffer2[500000];
    int bytes_read = OS_read(fd, buffer, 5000000, 10);
    int bytes_read2 = OS_read(fd2, buffer2, 5000000, 0);


    printf("%s\n", buffer);
    printf("%d\n", bytes_read);

    // writing buffer to a file
    FILE *fp;
    fp = fopen("fail.txt", "w+");
    fwrite(buffer, 100000, 1, fp);

    fp = fopen("fail2.jpg", "w+");
    fwrite(buffer2, 100000, 1, fp);

    dirEnt* directories = OS_readDir("../PEOPLE/ABK2Y");
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
    printf("file close %d\n", OS_close(fd));
    printf("file close %d\n", OS_close(fd2));
    printf("file close %d\n", OS_close(fd));

}
