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
    for (int i = 0; i < 20; i++) {
        printf("%s\n", directories[i].dir_name);
    }


}
