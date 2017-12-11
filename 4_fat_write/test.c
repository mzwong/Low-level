#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "main.h"

int main() {
    system("cat sampledisk16_dup.raw > sampledisk16.raw");
    int i = 0;
    /////////////// MKDIR TEST ////////////////////
    int pass_mkdir_root_dir = OS_mkdir("/NEW_DIR");
    if (pass_mkdir_root_dir == 1) {
        printf("PASS mkdir - create dir in root\n");
    } else {
        printf("FAIL mkdir - create dir in root\n");
    }

    int pass_mkdir_nested_dir = OS_mkdir("/PEOPLE/MZW7AF");
    if (pass_mkdir_nested_dir == 1) {
        printf("PASS mkdir - create nested dir in root\n");
    } else {
        printf("FAIL mkdir - create nested dir in root\n");
    }
    int fail_mkdir_dup_dir = OS_mkdir("/NEW_DIR");
    if (fail_mkdir_dup_dir == -2) {
        printf("PASS mkdir - create duplicate dir in root\n");
    } else {
        printf("fail status: %d\n", fail_mkdir_dup_dir);
        printf("FAIL mkdir - create duplicate dir in root\n");
    }

    ///////////// CREAT TEST ////////////////////////
    int pass_creat_root_new_file = OS_creat("/NEW_FILE");
    if (pass_creat_root_new_file == 1) {
        printf("PASS creat - create new file in root\n");
    } else {
        printf("FAIL creat - create new file in root\n");
    }

    int pass_creat_nested_new_file = OS_creat("/PEOPLE/MZW7AF/SENSEITXT");
    if (pass_creat_nested_new_file == 1) {
        printf("PASS creat - create new nested file\n");
    } else {
        printf("FAIL creat - create new nested file\n");
    }

    int fail_creat_nested_dup_file = OS_creat("/PEOPLE/MZW7AF/SENSEITXT");
    if (fail_creat_nested_dup_file == -2) {
        printf("PASS creat - dup file created\n");
    } else {
        printf("FAIL creat - dup file created\n");
    }

    int fail_creat_invalid_file = OS_creat("/PEOPLE/MZASDF/SENSEITXT");
    if (fail_creat_invalid_file == -1) {
        printf("PASS creat - invalid file created\n");
    } else {
        printf("FAIL creat - invalid file created\n");
    }

    dirEnt* directories = OS_readDir("/");
    if (directories == NULL) {
        printf("NULL FOUND YAY\n");
        return 0;
    }
    for (i = 0; i < 10; i++) {
        printf("%s\n", directories[i].dir_name);
    }
    directories = OS_readDir("/PEOPLE/MZW7AF");
    if (directories == NULL) {
        printf("NULL FOUND YAY\n");
        return 0;
    }
    for (i = 0; i < 5; i++) {
        printf("%s\n", directories[i].dir_name);
    }

    int fd = OS_open("/PEOPLE/MZW7AF/SENSEITXT");

    char* buff = "sensei is the best why are you so good at programming\n fill all the cups with knowledge";
    int bytes_write = OS_write(fd, buff, 500, 0);
    char buffer[500000];
    OS_read(fd, buffer, 500000, 0);
    if (strcmp(buff, buffer) == 0) {
        printf("PASS write - writing just text\n");
    } else {
        printf("FAIL write - writing just text\n");
    }
    OS_write(fd, buff, 500, 10);
    OS_read(fd, buffer, 500000, 0);
    char* newSensei = "sensei is sensei is the best why are you so good at programming\n fill all the cups with knowledge";
    if (strcmp(newSensei, buffer) == 0) {
        printf("PASS write - writing just text at offset\n");
    } else {
        printf("FAIL write - writing just text at offset\n");
    }

    int fd2 = OS_open("/MEDIA/HEARSE~1JPG");
    char buffer2[500000];
    OS_read(fd2, buffer2, 500000, 0);

    FILE *fp;
    fp = fopen("mzw7af_fail.jpg", "w+");
    fwrite(buffer2, 500000, 1, fp);

    OS_creat("/PEOPLE/MZW7AF/IMAGEJPG");
    int fd3 = OS_open("/PEOPLE/MZW7AF/IMAGEJPG");
    bytes_write = OS_write(fd3, buffer2, 300000, 0);
    printf("bytes written %d\n",  bytes_write);

    OS_close(fd3);
    fd3 = OS_open("/PEOPLE/MZW7AF/IMAGEJPG");

    char buffer3[300000];

    OS_read(fd3, buffer3, 300000, 0);
    // FILE *fp;
    fp = fopen("mzw7af_fail.jpg", "w+");

    fwrite(buffer3, 100000, 1, fp);
    fclose(fp);

    ////////////////// TEST RMDIR ////////////////////////
    int fail_rmdir_not_empty = OS_rmdir("/MEDIA");
    if (fail_rmdir_not_empty == -3) {
        printf("PASS rmdir - deleting nonempty dir\n");
    } else {
        printf("FAIL rmdir - deleting nonempty dir\n");
    }

    int fail_rmdir_not_dir = OS_rmdir("/PEOPLE/AG8T/GATE-C~1TXT");
    if (fail_rmdir_not_dir == -2) {
        printf("PASS rmdir - deleting file not dir\n");
    } else {
        printf("FAIL rmdir - deleting file not dir\n");
    }

    int fail_rmdir_not_dir2 = OS_rmdir("/PEOPLE/MZW7AF/SENSEITXT");
    if (fail_rmdir_not_dir2 == -2) {
        printf("PASS rmdir - deleting file not dir custom\n");
    } else {
        printf("FAIL rmdir - deleting file not dir custom\n");
    }

    int fail_rmdir_invalid_path = OS_rmdir("/PEOPLE/ASDF");
    if (fail_rmdir_invalid_path == -1) {
        printf("PASS rmdir - invalid path\n");
    } else {
        printf("FAIL rmdir - invalid path\n");
    }

    int pass_rmdir_new_dir = OS_rmdir("/NEW_DIR");
    printf("%d\n", pass_rmdir_new_dir);
    directories = OS_readDir("/");
    if (pass_rmdir_new_dir == 1) {
        printf("PASS rmdir - remove new_dir from root\n");
    } else {
        printf("FAIL rmdir - remove new_dir from root\n");
    }
    // should be missing new_dir:
    for (i = 0; i < 10; i++) {
        printf("%s\n", directories[i].dir_name);
    }

    ////////////////////////// RM TEST ////////////////////////
    int fail_rm_invalid_path = OS_rm("/PEOPLE/ASD/SENSEITXT");
    if (fail_rm_invalid_path == -1) {
        printf("PASS rm - invalid path\n");
    } else {
        printf("FAIL rm - invalid path\n");
    }

    int fail_rm_not_file = OS_rm("/PEOPLE");
    if (fail_rm_not_file == -2) {
        printf("PASS rm - not a file\n");
    } else {
        printf("FAIL rm - not a file\n");
    }
    directories = OS_readDir("/PEOPLE/MZW7AF");

    // should contain image.txt before removal:
    for (i = 0; i < 5; i++) {
        printf("%s\n", directories[i].dir_name);
    }
    int pass_rm_image = OS_rm("/PEOPLE/MZW7AF/SENSEITXT");
    if (pass_rm_image == 1) {
        printf("PASS rm - image\n");
    } else {
        printf("FAIL rm - image\n");
    }
    directories = OS_readDir("/PEOPLE/MZW7AF");
    // should be missing image.txt:
    for (i = 0; i < 5; i++) {
        printf("%s\n", directories[i].dir_name);
    }
    OS_creat("/PEOPLE/AG8T/GRIMTXT");
    int fd4 = OS_open("/PEOPLE/AG8T/GRIMTXT");
    OS_write(fd4, buffer2, 300000, 0);


    //////////// INtegration test /////////////
    int fail_mkdir_blank_space_dup_name = OS_mkdir("/NEW_FILE");
    if (fail_mkdir_blank_space_dup_name == -2) {
        printf("PASS mkdir - skipped blank space and found dup name\n");
    } else {
        printf("STATUS: %d\n", fail_mkdir_blank_space_dup_name);
        printf("FAIL mkdir - skipped blank space and found dup name\n");

    }

    int fail_creat_blank_space_file = OS_creat("/PEOPLE/MZW7AF/IMAGEJPG");
    if (fail_creat_blank_space_file == -2) {
        printf("PASS creat - skipped blank space and found dup name\n");
    } else {
        printf("STATUS asd: %d\n", fail_creat_blank_space_file);
        printf("FAIL creat - skipped blank space and found dup name\n");

    }
    return 0;
}
