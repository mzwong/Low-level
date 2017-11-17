#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"

int main() {
    system("cat sampledisk16_dup.raw > sampledisk16.raw");
    OS_mkdir("/new_dir");
    dirEnt* directories = OS_readDir("/new_dir/.");
    if (directories == NULL) {
        printf("NULL FOUND YAY\n");
        return 0;
    }
    for (int i = 0; i < 20; i++) {
        printf("%s\n", directories[i].dir_name);
    }
}
