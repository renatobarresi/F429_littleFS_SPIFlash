/*
 * filesystem.h
 *
 *  Created on: Apr 10, 2023
 *      Author: renatobarresi
 */

#pragma once

extern "C"
{
	#include "lfs.h"
}

#ifdef __cplusplus

constexpr lfs_size_t W25Q64_READ_SIZE = 256; 			// W25Q64 page size
constexpr lfs_size_t W25Q64_PROG_SIZE = 256; 			// W25Q64 page size
constexpr lfs_size_t W25Q64_BLOCK_SIZE = 65536; 		// W25Q64 sector size (64KB)
constexpr lfs_size_t W25Q64_BLOCK_COUNT = 128; 			// W25Q64 has 8MB, so with 64KB blocks, there are 128 blocks
constexpr lfs_size_t W25Q64_BLOCK_CYCLES = 100000; 		// W25Q64 has a 100,000 program/erase cycles endurance per sector

/**
 * Initialize the flash driver.
 *
 * @return 0 on success, negative value on error.
 */
int flash_init();

/**
 * Read data from the flash.
 *
 * @param c The LittleFS configuration.
 * @param block The block number to read from.
 * @param off The offset within the block to start reading from.
 * @param buffer The buffer to store the read data.
 * @param size The size of the data to read.
 * @return 0 on success, negative value on error.
 */
int w25q64_read(const struct lfs_config *c, lfs_block_t block,
                lfs_off_t off, void *buffer, lfs_size_t size);

/**
 * Program data to the flash.
 *
 * @param c The LittleFS configuration.
 * @param block The block number to program to.
 * @param off The offset within the block to start programming to.
 * @param buffer The buffer containing the data to program.
 * @param size The size of the data to program.
 * @return 0 on success, negative value on error.
 */
int w25q64_prog(const struct lfs_config *c, lfs_block_t block,
                lfs_off_t off, const void *buffer, lfs_size_t size);

/**
 * Erase a block in the flash.
 *
 * @param c The LittleFS configuration.
 * @param block The block number to erase.
 * @return 0 on success, negative value on error.
 */
int w25q64_erase(const struct lfs_config *c, lfs_block_t block);

/**
 * Synchronize the flash.
 *
 * @param c The LittleFS configuration.
 * @return 0 on success, negative value on error.
 */
int w25q64_sync(const struct lfs_config *c);

/**
 * LittleFS configuration for the W25Q64 flash.
 */
const struct lfs_config cfg = {
    .context = NULL,          				// context for user provided functions (can be NULL)
    .read = w25q64_read,
    .prog = w25q64_prog,
    .erase = w25q64_erase,
    .sync = w25q64_sync,
    .read_size = W25Q64_READ_SIZE,         	// W25Q64 page size
    .prog_size = W25Q64_PROG_SIZE,         	// W25Q64 page size
    .block_size = W25Q64_BLOCK_SIZE,      	// W25Q64 sector size (64KB)
	.block_count = W25Q64_BLOCK_COUNT, 		// W25Q64 has 8MB, so with 64KB blocks, there are 128 blocks
    .block_cycles = W25Q64_BLOCK_CYCLES,   	// W25Q64 has a 100,000 program/erase cycles endurance per sector
    .cache_size = W25Q64_PROG_SIZE,        	// Same as the program size (page size)
    .lookahead_size = 16,     				// Suggested value (in bits) for a 128 block_count (adjust according to the needs of your application)
    .name_max = 0,            				// Maximum length of file names (0 for default)
    .file_max = 0,            				// Maximum number of open files (0 for default)
    .attr_max = 0,           				// Maximum number of custom attributes (0 for default)
};

#endif
