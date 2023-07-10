/*
 * W25Qx_module.cpp
 *
 *  Created on: Apr 5, 2023
 *      Author: renatobarresi
 */

#include "W25Qx_module.h"
#include "gpio_module.h"

/* Constant expressions */
constexpr uint8_t CMD_WRITE_ENABLE       = 0x06;
constexpr uint8_t CMD_WRITE_DISABLE      = 0x04;
constexpr uint8_t CMD_READ_STATUS_REG    = 0x05;
constexpr uint8_t CMD_WRITE_STATUS_REG   = 0x01;
constexpr uint8_t CMD_CHIP_ERASE         = 0xC7;
constexpr uint8_t CMD_SECTOR_ERASE       = 0x20;
constexpr uint8_t CMD_BLOCK_ERASE        = 0xD8; // or 0x52 for 32KB block erase
constexpr uint8_t CMD_PAGE_PROGRAM       = 0x02;
constexpr uint8_t CMD_READ_DATA          = 0x03;
constexpr uint8_t CMD_READ_JDEC          = 0x9F;
constexpr uint8_t STATUS_BUSY_MASK       = 0x01;

/* Constructor */
W25Q64::W25Q64(GPIO_TypeDef *cs_gpio_port, uint16_t cs_pin)
    : csGPIOPort(cs_gpio_port), csPin(cs_pin), mySPIPort(SPI::getInstance())
{

}

/* Public methods */
HAL_StatusTypeDef W25Q64::init()
{
    HAL_StatusTypeDef status;

    // Init GPIO
    initGPIOOutput(this->csPin, this->csGPIOPort);
    cs_deselect();

    // Check if the SPI peripheral has already been initialized
    if (SPIStates::NotInitialized == mySPIPort.state)
    {
        status = mySPIPort.init();
        return status;
    }

    return HAL_OK;
}

/**
 * @brief Enable write operations to the W25Q64 flash memory.
 */
void W25Q64::write_enable()
{
    cs_select();
    mySPIPort.transmit((uint8_t *) &CMD_WRITE_ENABLE, 1);
    cs_deselect();
}

/**
 * @brief Disable write operations to the W25Q64 flash memory.
 */
void W25Q64::write_disable()
{
    cs_select();
    mySPIPort.transmit((uint8_t *) &CMD_WRITE_DISABLE, 1);
    cs_deselect();
}

/**
 * @brief Read the status register of the W25Q64 flash memory.
 *
 * @return The value of the status register.
 */
uint8_t W25Q64::read_status_register()
{
    uint8_t status;
    cs_select();
    mySPIPort.transmit((uint8_t *) &CMD_READ_STATUS_REG, 1);
    mySPIPort.receive(&status, 1);
    cs_deselect();
    return status;
}

/**
 * @brief Read the JDEC ID of the W25Q64 flash memory.
 */
void W25Q64::read_JDEC()
{
    uint8_t dummy = 0x00;
    cs_select();
    mySPIPort.transmit((uint8_t *) &CMD_READ_JDEC, 1);
    mySPIPort.transmit(&dummy, 1);
    mySPIPort.transmit(&dummy, 1);
    mySPIPort.transmit(&dummy, 1);
    cs_deselect();
}

/**
 * @brief Write a value to the status register of the W25Q64 flash memory.
 *
 * @param status The value to write to the status register.
 */
void W25Q64::write_status_register(uint8_t status)
{
    cs_select();
    write_enable(); // Set the Write Enable Latch (WEL) bit before writing to the status register
    uint8_t cmd[] = {CMD_WRITE_STATUS_REG, status};
    mySPIPort.transmit(cmd, 2);
    cs_deselect();

    // If needed, you can add a write_disable() call here, although it's not strictly necessary
    // since the WEL bit will be automatically cleared after the Write Status Register operation.
}

/**
 * @brief Erase the entire chip (W25Q64) of the flash memory.
 */
void W25Q64::chip_erase()
{
    write_enable();
    cs_select();
    mySPIPort.transmit((uint8_t *) &CMD_CHIP_ERASE, 1);
    cs_deselect();
    wait_until_ready();
}

/**
 * @brief Erase a sector (4KB) of the W25Q64 flash memory.
 *
 * @param addr The starting address of the sector to erase.
 */
void W25Q64::sector_erase(uint32_t addr)
{
    write_enable();
    cs_select();
    uint8_t cmd[] = {CMD_SECTOR_ERASE,
                    static_cast<uint8_t>((addr >> 16) & 0xFF),
                    static_cast<uint8_t>((addr >> 8) & 0xFF),
                    static_cast<uint8_t>(addr & 0xFF)}; // Sector Erase command
    mySPIPort.transmit(cmd, 4);
    cs_deselect();
    wait_until_ready();
}

/**
 * @brief Erase a block (64KB) of the W25Q64 flash memory.
 *
 * @param addr The starting address of the block to erase.
 */
void W25Q64::block_erase(uint32_t addr)
{
    write_enable();
    cs_select();
    uint8_t cmd[] = {CMD_BLOCK_ERASE,
                     static_cast<uint8_t>((addr >> 16) & 0xFF),
                     static_cast<uint8_t>((addr >> 8) & 0xFF),
                     static_cast<uint8_t>(addr & 0xFF)};
    mySPIPort.transmit(cmd, 4);
    cs_deselect();
    wait_until_ready();
}

/**
 * @brief Write a page (256 bytes) of data to the W25Q64 flash memory.
 *
 * @param addr The starting address of the page to write.
 * @param data A pointer to the buffer containing the data to be written.
 * @param size The size of the data buffer (must be 256 bytes or less).
 */
void W25Q64::page_program(uint32_t addr, uint8_t *data, uint16_t size)
{
    if (size > 256) return; // Ensure that the data size is within the page limit

    write_enable();
    cs_select();
    uint8_t cmd[] = {CMD_PAGE_PROGRAM,
                     static_cast<uint8_t>((addr >> 16) & 0xFF),
                     static_cast<uint8_t>((addr >> 8) & 0xFF),
                     static_cast<uint8_t>(addr & 0xFF)};
    mySPIPort.transmit(cmd, 4);
    mySPIPort.transmit(data, size);
    cs_deselect();
    wait_until_ready();
}

/**
 * @brief Read data from the W25Q64 flash memory.
 *
 * @param addr The starting address to read from.
 * @param data A pointer to the buffer where the read data will be stored.
 * @param size The number of bytes to read.
 */
void W25Q64::read_data(uint32_t addr, uint8_t *data, uint16_t size)
{
    cs_select();
    uint8_t cmd[] = {CMD_READ_DATA,
                     static_cast<uint8_t>((addr >> 16) & 0xFF),
                     static_cast<uint8_t>((addr >> 8) & 0xFF),
                     static_cast<uint8_t>(addr & 0xFF)};
    mySPIPort.transmit(cmd, 4);
    mySPIPort.receive(data, size);
    cs_deselect();
}

/**
 * @brief Wait for the W25Q64 flash memory to become ready for the next operation.
 *
 * This method polls the status register and waits until the busy bit is cleared.
 */
void W25Q64::wait_until_ready()
{
    uint8_t status;
    do
    {
        status = read_status_register();
    } while (status & STATUS_BUSY_MASK); // Wait until the busy bit (bit 0) is cleared
}

/* Private methods */
void W25Q64::cs_select()
{
    mySPIPort.csLow(this->csPin, this->csGPIOPort);
}

void W25Q64::cs_deselect()
{
    mySPIPort.csHigh(this->csPin, this->csGPIOPort);
}
