/*
 * W25Qx_module.h
 *
 *  Created on: Apr 5, 2023
 *      Author: renatobarresi
 */
#pragma once
#ifdef __cplusplus

#include "stm32f4xx_hal.h"
#include "spi_module.h"

/**
 * @brief W25Q64 SPI Flash Memory Class.
 */
class W25Q64 {
public:
    /**
     * @brief Constructor for W25Q64 class.
     * @param cs_gpio_port The GPIO port for the chip select pin.
     * @param cs_pin The pin number for the chip select.
     */
    W25Q64(GPIO_TypeDef *cs_gpio_port, uint16_t cs_pin);

    /**
     * @brief Initializes the W25Q64 Flash Memory.
     * @return The initialization status.
     */
    HAL_StatusTypeDef init();

    /**
     * @brief Enables write operations.
     */
    void write_enable();

    /**
     * @brief Disables write operations.
     */
    void write_disable();

    /**
     * @brief Reads the status register.
     * @return The value of the status register.
     */
    uint8_t read_status_register();

    /**
     * @brief Writes the status register.
     * @param status The value to be written to the status register.
     */
    void write_status_register(uint8_t status);

    /**
     * @brief Performs a chip erase operation.
     */
    void chip_erase();

    /**
     * @brief Performs a sector erase operation at the specified address.
     * @param addr The address of the sector to be erased.
     */
    void sector_erase(uint32_t addr);

    /**
     * @brief Performs a block erase operation at the specified address.
     * @param addr The address of the block to be erased.
     */
    void block_erase(uint32_t addr);

    /**
     * @brief Performs a page program operation at the specified address.
     * @param addr The starting address for page programming.
     * @param data Pointer to the data buffer to be programmed.
     * @param size The size of the data buffer.
     */
    void page_program(uint32_t addr, uint8_t *data, uint16_t size);

    /**
     * @brief Reads data from the specified address.
     * @param addr The starting address for data read.
     * @param data Pointer to the buffer to store the read data.
     * @param size The size of the buffer.
     */
    void read_data(uint32_t addr, uint8_t *data, uint16_t size);

    /**
     * @brief Waits until the flash memory is ready for the next operation.
     */
    void wait_until_ready();

    /**
     * @brief Reads the JEDEC ID of the flash memory.
     */
    void read_JDEC();

private:
    GPIO_TypeDef *csGPIOPort; ///< GPIO port for the chip select pin.
    uint16_t csPin; ///< Pin number for the chip select.

    SPI& mySPIPort; ///< SPI port for communication with the flash memory.

    /**
     * @brief Selects the chip by pulling the chip select pin low.
     */
    void cs_select();

    /**
     * @brief Deselects the chip by pulling the chip select pin high.
     */
    void cs_deselect();
};

#endif
