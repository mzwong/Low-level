#include <stdio.h>
#include <unistd.h>
#include "main.h"

int main() {
    OS_cd("media");
    int fd = OS_open("/people/yyz5w/the-game.txt");
    int fd2 = OS_open("hearse-fail.jpg");
    char buffer[500000];
    char buffer2[500000];
    int bytes_read = OS_read(fd, buffer, 5000000, 0);
    int bytes_read2 = OS_read(fd2, buffer2, 5000000, 0);


    printf("%s\n", buffer);
    printf("%d\n", bytes_read);

    // writing buffer to a file
    FILE *fp;
    fp = fopen("fail.txt", "w+");
    fwrite(buffer, 100000, 1, fp);

    fp = fopen("fail2.jpg", "w+");
    fwrite(buffer2, 100000, 1, fp);

    dirEnt* directories = OS_readDir("/people/");
    if (directories == NULL) {
        printf("NULL FOUND YAY\n");
        return 0;
    }
    for (int i = 0; i < 75; i++) {
        printf("%s\n", directories[i].dir_name);
    }

    OS_cd("people");
    OS_cd("abk2y/");
    OS_cd("/");
    OS_cd("people/abk2y");
    printf("file close %d\n", OS_close(fd));
    printf("file close %d\n", OS_close(fd2));
    printf("file close %d\n", OS_close(fd));

}
