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
int openFileSystem();
void getBootSector(void * boot_sector);
int getRootDirStart(fat_BS_t* boot_sector);
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

dirEnt* OS_readDir(const char *dirname) {

    void * boot_sector[sizeof(fat_BS_t)];
    getBootSector(boot_sector);
    fat_BS_t* bs = (fat_BS_t *) boot_sector;
    int rootDirStart = getRootDirStart(bs);
    void *rootDirSpace[sizeof(dirEnt)];

    int fd = openFileSystem();
    lseek(fd, rootDirStart, SEEK_SET);
    close(fd);
    int i = 0;
    printf("here\n");
    printf("%d\n", bs->bytes_per_sector);
    // for (i = 0; i < bs->root_entry_count; i++) {
    //     read(fd, rootDirSpace, sizeof(dirEnt));
    //     dirEnt* rootDir = (dirEnt*) rootDirSpace;
    //     printf("%s\n", rootDir->dir_name);
    // }
    return '\0';
}

/**
 * Opens a file descriptor to the file system file
 */
int openFileSystem() {
    char* filepath = getenv("FAT_FS_PATH");
    return open(filepath, O_RDONLY);
}

/**
 * Gets the starting offset of the root directory
 * Takes in a pointer to the boot sector
 */
int getRootDirStart(fat_BS_t* boot_sector) {
     unsigned int resvdSecCnt = (unsigned int) boot_sector->reserved_sector_count;
     unsigned int numFats = (unsigned int) boot_sector->table_count;
     unsigned int fatSz16 = (unsigned int) boot_sector->table_size_16;
     return resvdSecCnt + (numFats * fatSz16);
}

/**
 * Takes in a buffer and reads the boot sector into the buffer
 */
void getBootSector(void* boot_sector) {
    int fd = openFileSystem();
    read(fd, boot_sector, sizeof(boot_sector));
    close(fd);
}
