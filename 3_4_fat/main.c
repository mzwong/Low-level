/**
 * Homework 3: Read API for FAT 16 file system
 *
 * CS4414 Operating Systems
 * Fall 2017
 *
 * Maurice Wong - mzw7af
 *
 * main.c - Read API library for FAT16 file system
 *
 * COMPILE:     make
 * OBJECTS:     libFAT.so
 */

#include "main.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


//PRIVATE FUNCTION DECLARATIONS
DIRENTRY* getRoot();

// BEGIN IMPLEMENTATION

int OS_cd(const char *path) {
    return -1;
}

int OS_open(const char *path) {
    return -1;
}

int OS_close(int fd) {
    return -1;
}

int OS_read(int fildes, void *buf, int nbyte, int offset) {
    return -1;
}

DIRENTRY* OS_readDir(const char *dirname) {
    return '\0';
}

DIRENTRY* getRoot() {
    char* filepath = getenv("FAT_FS_PATH");
    int fd = open(filepath, O_RDONLY);
    void * boot_sector[sizeof(fat_BS_t)];
    read(fd, boot_sector, sizeof(boot_sector));
    printf("hel");
    return '\0';
}
