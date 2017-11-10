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
unsigned int getFirstRootDirSecNum(fat_BS_t* boot_sector);
unsigned int getFirstDataSector(fat_BS_t* boot_sector);
unsigned int getFirstSectorOfCluster(unsigned int n, fat_BS_t* boot_sector);
unsigned int getFatValue(unsigned int n, fat_BS_t* boot_sector);
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
    unsigned int rootDirStart = getFirstRootDirSecNum(bs);
    void *rootDirSpace[sizeof(dirEnt)];

    int fd = openFileSystem();
    lseek(fd, rootDirStart * (bs->bytes_per_sector), SEEK_SET);

    // loop through directory entries
    while (1) {
        read(fd, rootDirSpace, sizeof(dirEnt));
        dirEnt* rootDir = (dirEnt*) rootDirSpace;
        printf("%sa\n", rootDir->dir_name);
        printf("%x\n", rootDir->dir_attr);
        if (strcmp("PEOPLE     ", (char *) rootDir->dir_name) == 0) {
            printf("begin\n");
            unsigned int clusterNum = (unsigned int) rootDir->dir_fstClusHI << 16;
            printf("%u\n", rootDir->dir_fstClusLO);
            int firstSector = getFirstSectorOfCluster(clusterNum, bs);
            char buffer[bs->bytes_per_sector];
            lseek(fd, firstSector * bs->bytes_per_sector, SEEK_SET);
            read(fd, buffer, bs->bytes_per_sector);
            printf("%s\n", buffer);
            printf("end\n");

            break;
        }
        if (rootDir->dir_name[0] == 0x00) {
            break;
        }
    }
    close(fd);

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
unsigned int getFirstRootDirSecNum(fat_BS_t* boot_sector) {
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
    read(fd, boot_sector, sizeof(fat_BS_t));
    close(fd);
}

/**
 * returns the first data sector (start of the data region)
 */
unsigned int getFirstDataSector(fat_BS_t* boot_sector) {
    unsigned int rootEntCnt = (unsigned int) boot_sector->root_entry_count;
    unsigned int bytsPerSec = (unsigned int) boot_sector->bytes_per_sector;
    unsigned int resvdSecCnt = (unsigned int) boot_sector->reserved_sector_count;
    unsigned int numFats = (unsigned int) boot_sector->table_count;
    unsigned int fatSz16 = (unsigned int) boot_sector->table_size_16;

    unsigned int rootDirSectors = ((rootEntCnt * 32) + (bytsPerSec - 1)) / bytsPerSec;
    return resvdSecCnt + (numFats * fatSz16) + rootDirSectors;
}

/**
 * Takes in a cluster number N and returns the first sector of that cluster
 */
unsigned int getFirstSectorOfCluster(unsigned int n, fat_BS_t* boot_sector) {
    unsigned int secPerCluster = (unsigned int) boot_sector->sectors_per_cluster;
    unsigned int firstDataSector = getFirstDataSector(boot_sector);
    return ((n-2) * secPerCluster) + firstDataSector;
}

/**
 * Takes in a cluster N and returns the FAT value for that cluster.
 */
unsigned int getFatValue(unsigned int n, fat_BS_t* boot_sector) {
    unsigned int resvdSecCnt = (unsigned int) boot_sector->reserved_sector_count;
    unsigned int bytsPerSec = (unsigned int) boot_sector->bytes_per_sector;
    unsigned int fatOffset = n * 2;
    unsigned int fatSecNum = resvdSecCnt + (fatOffset / bytsPerSec);
    unsigned int fatEntOffset = fatOffset % bytsPerSec;

    int fd = openFileSystem();
    lseek(fd, fatSecNum * bytsPerSec, SEEK_SET);
    unsigned char secBuff[bytsPerSec];
    read(fd, secBuff, bytsPerSec);
    return (unsigned int) *((short *) &secBuff[fatEntOffset]);
}
