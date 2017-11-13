#include <stdio.h>
#include <unistd.h>
#include "main.h"

int main() {
    int fd = OS_open("/PEOPLE/SV9WN/REAGAN~1TXT");
    char buffer[1000];
    read(fd, buffer, 1000);
    printf("%s\n", buffer);
}
