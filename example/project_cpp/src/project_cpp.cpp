/*
 * project_cpp.cpp
 *
 *  Created on: Mar 19, 2023
 *      Author: renatobarresi
 */

#include "project_cpp.h"
#include "littleFSInterface.h"
#include <cstring>

void main_cpp(void)
{
	flash_init();

    lfs_t lfs;
    int res = lfs_mount(&lfs, &cfg);
    if (res < 0) {
        // If the mount fails, try formatting the filesystem
        res = lfs_format(&lfs, &cfg);
        if (res < 0) {
        	while(1);
        }
        // Try mounting again
        res = lfs_mount(&lfs, &cfg);
        if (res < 0) {
        	while(1);
        }
    }

    // Open the file for writing
    lfs_file_t file;
    res = lfs_file_open(&lfs, &file, "example.txt", LFS_O_WRONLY | LFS_O_CREAT);
    if (res < 0) {
    	while(1);
    }

    // Write some data to the file
    const char *data = "Hello, LittleFS!";
    res = lfs_file_write(&lfs, &file, data, strlen(data));
    if (res < 0) {
    	while(1);
    }

    // Close the file after writing
    lfs_file_close(&lfs, &file);

    // Open the file for reading
    res = lfs_file_open(&lfs, &file, "example.txt", LFS_O_RDONLY);
    if (res < 0) {
    	while(1);
    }

    // Read the data from the file
    char buffer[32];
    res = lfs_file_read(&lfs, &file, buffer, sizeof(buffer));
    if (res < 0) {
        while(1);
    }

    // Null-terminate the read data
    buffer[res] = '\0';

    // Print the read data
    printf("Read data: %s\n", buffer);

    // Close the file after reading
    lfs_file_close(&lfs, &file);

    // Unmount the filesystem
    lfs_unmount(&lfs);

    while(1);
}
