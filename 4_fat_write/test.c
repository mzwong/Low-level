#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    for (int i = 0; i < 10; i++) {
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
    OS_read(fd, buffer, 500000, 0);
    if (strcmp(buff, buffer) == 0) {
        printf("PASS write - writing just text\n");
    } else {
        printf("FAIL write - writing just text\n");
    }

    int fd2 = OS_open("/media/hearse-fail.jpg");
    char buffer2[500000];
    OS_read(fd2, buffer2, 500000, 0);

    FILE *fp;
    fp = fopen("mzw7af_fail.jpg", "w+");
    fwrite(buffer2, 500000, 1, fp);

    OS_creat("/people/mzw7af/image.jpg");
    int fd3 = OS_open("/people/mzw7af/image.jpg");
    bytes_write = OS_write(fd3, buffer2, 300000, 0);
    printf("bytes written %d\n",  bytes_write);

    OS_close(fd3);
    fd3 = OS_open("/people/mzw7af/image.jpg");

    char buffer3[300000];

    OS_read(fd3, buffer3, 300000, 0);
    // FILE *fp;
    fp = fopen("mzw7af_fail.jpg", "w+");

    fwrite(buffer3, 100000, 1, fp);
    fclose(fp);

    ////////////////// TEST RMDIR ////////////////////////
    int fail_rmdir_not_empty = OS_rmdir("/media");
    if (fail_rmdir_not_empty == -3) {
        printf("PASS rmdir - deleting nonempty dir\n");
    } else {
        printf("FAIL rmdir - deleting nonempty dir\n");
    }

    int fail_rmdir_not_dir = OS_rmdir("/people/ag8t/gate-captain.txt");
    if (fail_rmdir_not_dir == -2) {
        printf("PASS rmdir - deleting file not dir\n");
    } else {
        printf("FAIL rmdir - deleting file not dir\n");
    }

    int fail_rmdir_not_dir2 = OS_rmdir("/people/mzw7af/sensei.txt");
    if (fail_rmdir_not_dir2 == -2) {
        printf("PASS rmdir - deleting file not dir custom\n");
    } else {
        printf("FAIL rmdir - deleting file not dir custom\n");
    }

    int fail_rmdir_invalid_path = OS_rmdir("/people/asdf");
    if (fail_rmdir_invalid_path == -1) {
        printf("PASS rmdir - invalid path\n");
    } else {
        printf("FAIL rmdir - invalid path\n");
    }

    int pass_rmdir_new_dir = OS_rmdir("/new_dir");
    printf("%d\n", pass_rmdir_new_dir);
    directories = OS_readDir("/");
    if (pass_rmdir_new_dir == 1) {
        printf("PASS rmdir - remove new_dir from root\n");
    } else {
        printf("FAIL rmdir - remove new_dir from root\n");
    }
    // should be missing new_dir:
    for (int i = 0; i < 10; i++) {
        printf("%s\n", directories[i].dir_name);
    }

    ////////////////////////// RM TEST ////////////////////////
    int fail_rm_invalid_path = OS_rm("/people/asd/sensei.txt");
    if (fail_rm_invalid_path == -1) {
        printf("PASS rm - invalid path\n");
    } else {
        printf("FAIL rm - invalid path\n");
    }

    int fail_rm_not_file = OS_rm("/people");
    if (fail_rm_not_file == -2) {
        printf("PASS rm - not a file\n");
    } else {
        printf("FAIL rm - not a file\n");
    }
    directories = OS_readDir("/people/mzw7af");

    // should contain image.txt before removal:
    for (int i = 0; i < 5; i++) {
        printf("%s\n", directories[i].dir_name);
    }
    int pass_rm_image = OS_rm("/people/mzw7af/sensei.txt");
    if (pass_rm_image == 1) {
        printf("PASS rm - image\n");
    } else {
        printf("FAIL rm - image\n");
    }
    directories = OS_readDir("/people/mzw7af");
    // should be missing image.txt:
    for (int i = 0; i < 5; i++) {
        printf("%s\n", directories[i].dir_name);
    }
    OS_creat("/people/ag8t/grim.txt");
    int fd4 = OS_open("/people/ag8t/grim.txt");
    OS_write(fd4, buffer2, 300000, 0);

}
