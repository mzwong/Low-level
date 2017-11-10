typedef struct fat_extBS_16 {
	//extended fat12 and fat16 stuff
	unsigned char		bios_drive_num;
	unsigned char		reserved1;
	unsigned char		boot_signature;
	unsigned int		volume_id;
	unsigned char		volume_label[11];
	unsigned char		fat_type_label[8];

} __attribute__((packed)) fat_extBS_16_t;

typedef struct fat_BS {
	unsigned char 		bootjmp[3];
	unsigned char 		oem_name[8];
	unsigned short 	    bytes_per_sector;
	unsigned char		sectors_per_cluster;
	unsigned short		reserved_sector_count;
	unsigned char		table_count;
	unsigned short		root_entry_count;
	unsigned short		total_sectors_16;
	unsigned char		media_type;
	unsigned short		table_size_16;
	unsigned short		sectors_per_track;
	unsigned short		head_side_count;
	unsigned int 		hidden_sector_count;
	unsigned int 		total_sectors_32;

	//this will be cast to it's specific type once the driver actually knows what type of FAT this is.
	unsigned char		extended_section[54];

} __attribute__((packed)) fat_BS_t;


typedef struct  dir_ent {
    unsigned char dir_name[11];           // short name
    unsigned char dir_attr;               // File sttribute
    unsigned char dir_NTRes;              // Set value to 0, never chnage this
    unsigned char dir_crtTimeTenth;       // millisecond timestamp for file creation time
    unsigned short dir_crtTime;           // time file was created
    unsigned short dir_crtDate;           // date file was created
    unsigned short dir_lstAccDate;        // last access date
    unsigned short dir_fstClusHI;         // high word fo this entry's first cluster number
    unsigned short dir_wrtTime;           // time of last write
    unsigned short dir_wrtDate;           // dat eof last write
    unsigned short dir_fstClusLO;         // low word of this entry's first cluster number
    unsigned int dir_fileSize;          // 32-bit DWORD hoding this file's size in bytes
} __attribute__((packed)) dirEnt;

int OS_cd(const char *path);
int OS_open(const char *path);
int OS_close(int fd);
int OS_read(int fildes, void *buf, int nbyte, int offset);
dirEnt *OS_readDir(const char *dirname);
