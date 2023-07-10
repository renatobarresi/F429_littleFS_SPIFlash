/*
 * filesystem.cpp
 *
 *  Created on: Apr 10, 2023
 *      Author: renatobarresi
 *
 *  This file contains the implementation of the LittleFS interface using the W25Q64 flash memory.
 */

#include <littleFSInterface.h>
#include "W25Qx_module.h"

W25Q64 myFlash(GPIOF, GPIO_PIN_13); // F13 is Pin D7 on the nucleo board

/**
 * @brief Initialize the W25Q64 flash memory for filesystem operations.
 *
 * @return 1 if initialization is successful, otherwise it will loop indefinitely.
 */
int flash_init()
{
    if (HAL_OK != myFlash.init())
    {
        while(1);
    }

    return 1;
}

/**
 * @brief Read data from the W25Q64 flash memory for the LittleFS interface.
 *
 * @param c Pointer to the LittleFS configuration.
 * @param block The block number to read from.
 * @param off The offset within the block to start reading from.
 * @param buffer Pointer to the buffer where the read data will be stored.
 * @param size The number of bytes to read.
 * @return Always returns 0.
 */
int w25q64_read(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, void *buffer, lfs_size_t size)
{
    uint32_t addr = block * c->block_size + off;
    myFlash.read_data(addr, static_cast<uint8_t *>(buffer), size);
    return 0;
}

/**
 * @brief Program data to the W25Q64 flash memory for the LittleFS interface.
 *
 * @param c Pointer to the LittleFS configuration.
 * @param block The block number to write to.
 * @param off The offset within the block to start writing to.
 * @param buffer Pointer to the buffer containing the data to be written.
 * @param size The number of bytes to write.
 * @return Always returns 0.
 */
int w25q64_prog(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, const void *buffer, lfs_size_t size)
{
    uint32_t addr = block * c->block_size + off;
    myFlash.page_program(addr, const_cast<uint8_t *>(static_cast<const uint8_t *>(buffer)), size);
    return 0;
}

/**
 * @brief Erase a block of the W25Q64 flash memory for the LittleFS interface.
 *
 * @param c Pointer to the LittleFS configuration.
 * @param block The block number to erase.
 * @return Always returns 0.
 */
int w25q64_erase(const struct lfs_config *c, lfs_block_t block)
{
    uint32_t addr = block * c->block_size;
    myFlash.block_erase(addr);
    return 0;
}

/**
 * @brief Synchronize the W25Q64 flash memory for the LittleFS interface.
 *
 * This function does nothing since we're not using any caching or buffering.
 *
 * @param c Pointer to the LittleFS configuration.
 * @return Always returns 0.
 */
int w25q64_sync(const struct lfs_config *c)
{
    // Nothing to do since we're not using any caching or buffering
    return 0;
}
