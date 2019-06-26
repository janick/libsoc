#ifndef _LIBSOC_I2C_H_
#define _LIBSOC_I2C_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \struct i2c
 * \brief representation of spi device and chipselect
 * \param int fd - file descriptor to open i2c device
 * \param uint8_t bus - i2c bus number
 * \param uint8_t address - address of i2c device on the bus
 */

typedef struct {
  uint8_t bus;
  uint8_t address;
} i2c;

/**
 * \fn i2c * libsoc_i2c_init (uint8_t i2c_bus, uint8_t i2c_address)
 * \brief initialises new i2c instance at specified address
 * \param uint8_t i2c_bus - the linux enumerated bus number
 * \param uint8_t i2c_address - 
 * \return i2c* struct pointer or NULL on failure
 */
i2c * libsoc_i2c_init (uint8_t i2c_bus, uint8_t i2c_address)
{
    i2c *p = new i2c;

    *p = {i2c_bus, i2c_address};

    return p;
}

/**
 * \fn libsoc_i2c_free (i2c * i2c)
 * \brief frees the malloced i2c struct
 * \param i2c* i2c - valid i2c struct pointer
 * \return EXIT_SUCCESS or EXIT_FAILURE
 */
int libsoc_i2c_free (i2c * i2c)
{
    delete i2c;
    return 0;
}

/**
 * \fn libsoc_i2c_write(i2c *i2c, uint8_t *buffer, uint16_t len)
 * \brief write a specified amount of data to i2c slave
 * \param i2c *i2c - valid i2c device struct
 * \param uint8_t *buffer - pointer to output data buffer
 * \param uint16_t len - length of buffer in bytes
 * \return EXIT_SUCCESS or EXIT_FAILURE 
 */
int libsoc_i2c_write (i2c * i2c, uint8_t * buffer, uint16_t len)
{
    return 0;
}

/**
 * \fn libsoc_i2c_read(i2c *i2c, uint8_t *buffer, uint16_t len)
 * \brief read a specified amount of data from an i2c slave
 * \param i2c *i2c - valid i2c device struct
 * \param uint8_t *buffer - pointer to input data buffer
 * \param uint16_t len - length of buffer in bytes
 * \return EXIT_SUCCESS or EXIT_FAILURE 
 */
int libsoc_i2c_read (i2c * i2c, uint8_t * buffer, uint16_t len)
{
    return 0;
}

/**
 * \fn libsoc_i2c_set_timeout(i2c *i2c, int timeout)
 * \brief set the timeout in is 10's of milliseconds, i.e. a timeout of
 * 2 is 2 x 10ms = 20ms
 * \param i2c *i2c - valid i2c device struct
 * \return EXIT_SUCCESS or EXIT_FAILURE 
 */
int libsoc_i2c_set_timeout(i2c * i2c, int timeout)
{
    return 0;
}

#ifdef __cplusplus
}
#endif
#endif
