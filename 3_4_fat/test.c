#include <stdio.h>
#include <unistd.h>
#include "main.h"

int main() {
    int fd = OS_open("/MEDIA/EP9962~1JPG");
    char buffer[500000];
    int bytes_read = OS_read(fd, buffer, 5000000, 0);
    //int bytes_read = read(fd, buffer, 5000000);
    printf("%s\n", buffer);
    printf("%d\n", bytes_read);

    // writing buffer to a file
    FILE *fp;
    fp = fopen("fail.jpg", "w+");
    fwrite(buffer, 100000, 1, fp);
}
