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


typedef struct fat_dirEnt {
    unsigned char       name[11];
    unsigned char       attr;
    unsigned char       NT_reserved;
    unsigned char       create_time_tenth;
    unsigned short      create_time;
    unsigned short      create_date;
    unsigned short      last_access_date;
    unsigned short      first_cluster_number_high;
    unsigned short      write_time;
    unsigned short      write_date;
    unsigned short      first_cluster_low;
    unsigned int        file_size;
} __attribute__((packed)) fat_dir_ent_t;
