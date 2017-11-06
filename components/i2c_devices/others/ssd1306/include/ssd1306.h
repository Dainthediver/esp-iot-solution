/*
 * ESPRESSIF MIT License
 *
 * Copyright (c) 2017 <ESPRESSIF SYSTEMS (SHANGHAI) PTE LTD>
 *
 * Permission is hereby granted for use on ESPRESSIF SYSTEMS products only, in which case,
 * it is free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */
#ifndef __IOT_SSD_1306_H__
#define __IOT_SSD_1306_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "driver/gpio.h"
#include "driver/i2c.h"
#include "i2c_bus.h"
#include "stdint.h"

/**
 * @brief  I2C address.
 */
#define SSD1306_I2C_ADDRESS    ((uint8_t)0x3C)

//#define INTERFACE_3WIRE_SPI   	//3-wire SPI
//#define INTERFACE_4WIRE_SPI   	//4-wire SPI
#define INTERFACE_IIC         	    //I2C

#define SSD1306_SET_LOWER_ADDRESS   0x02
#define SSD1306_SET_HIGHER_ADDRESS  0x10

#define SSD1306_CMD			        0
#define SSD1306_DAT			        1
#define SSD1306_WRITE_CMD           0x00
#define SSD1306_WRITE_DAT           0x40
#define SSD1306_WIDTH    	        128
#define SSD1306_HEIGHT   	        64
#define SSD1306_SET_PAGE_ADDR       0xB0

#define SSD1306_CS_MUX		        PERIPHS_IO_MUX_GPIO23_U
#define SSD1306_CS_NUM		        23
#define SSD1306_CS_FUNC		        FUNC_GPIO23_GPIO23

#define SSD1306_CLK_MUX		        PERIPHS_IO_MUX_GPIO4_U
#define SSD1306_CLK_NUM		        4
#define SSD1306_CLK_FUNC	        FUNC_GPIO4_GPIO4

#define SSD1306_DIN_MUX		        PERIPHS_IO_MUX_GPIO17_U
#define SSD1306_DIN_NUM		        17
#define SSD1306_DIN_FUNC	        FUNC_GPIO17_GPIO17

#define SSD1306_RES_MUX		        PERIPHS_IO_MUX_GPIO18_U
#define SSD1306_RES_NUM		        18
#define SSD1306_RES_FUNC	        FUNC_GPIO18_GPIO18

#define SSD1306_DC_MUX		        PERIPHS_IO_MUX_GPIO5_U
#define SSD1306_DC_NUM		        5
#define SSD1306_DC_FUNC		        FUNC_GPIO5_GPIO5

#define __SSD1306_CS_SET()		    GPIO_OUTPUT_SET(SSD1306_CS_NUM, 1)
#define __SSD1306_CS_CLR()		    GPIO_OUTPUT_SET(SSD1306_CS_NUM, 0)

#define __SSD1306_RES_SET()		    GPIO_OUTPUT_SET(SSD1306_RES_NUM, 1)
#define __SSD1306_RES_CLR()		    GPIO_OUTPUT_SET(SSD1306_RES_NUM, 0)

#define __SSD1306_DC_SET()		    GPIO_OUTPUT_SET(SSD1306_DC_NUM, 1)
#define __SSD1306_DC_CLR()		    GPIO_OUTPUT_SET(SSD1306_DC_NUM, 0)

#define __SSD1306_CLK_SET()		    GPIO_OUTPUT_SET(SSD1306_CLK_NUM, 1)
#define __SSD1306_CLK_CLR()		    GPIO_OUTPUT_SET(SSD1306_CLK_NUM, 0)

#define __SSD1306_DIN_SET()		    GPIO_OUTPUT_SET(SSD1306_DIN_NUM, 1)
#define __SSD1306_DIN_CLR()		    GPIO_OUTPUT_SET(SSD1306_DIN_NUM, 0)

//I2C
#define OLED_IIC_SCL_NUM			(gpio_num_t)4		/*!< gpio number for I2C master clock IO4*/
#define OLED_IIC_SDA_NUM			(gpio_num_t)17		/*!< gpio number for I2C master data IO17*/
#define OLED_IIC_NUM				I2C_NUM_0           /*!< I2C number >*/
#define OLED_IIC_FREQ_HZ			100000              /*!< I2C colock frequency >*/
#define OLED_IIC_TX_BUF_DISABLE		0                   /*!< I2C Tx buffer disable >*/
#define OLED_IIC_RX_BUF_DISABLE		0                   /*!< I2C Rx buffer disable >*/

#define WRITE_BIT      				I2C_MASTER_WRITE    /*!< I2C master write */
#define READ_BIT       				I2C_MASTER_READ     /*!< I2C master read */
#define ACK_CHECK_EN				1		            /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS				0		            /*!< I2C master will not check ack from slave */
#define ACK_VAL        				0x0                 /*!< I2C ack value */
#define NACK_VAL       				0x1                 /*!< I2C nack value */

typedef void* ssd1306_handle_t;                         /*handle of ssd1306*/

/**
 * @brief   device initialization
 *
 * @param   device object handle of ssd1306
 *
 * @return
 *     - ESP_OK Success
 *     - ESP_FAIL Fail
 */
esp_err_t dev_ssd1306_init(ssd1306_handle_t dev);

/**
 * @brief   Create and initialization device object and return a device handle
 *
 * @param   bus I2C bus object handle
 * @param   dev_addr I2C device address of device
 *
 * @return
 *     - device object handle of ssd1306
 */
ssd1306_handle_t dev_ssd1306_create(i2c_bus_handle_t bus, uint16_t dev_addr);

/**
 * @brief   Delete and release a device object
 *
 * @param   device object handle of ssd1306
 * @param   del_bus Whether to delete the I2C bus
 *
 * @return
 *     - ESP_OK Success
 *     - ESP_FAIL Fail
 */
esp_err_t dev_ssd1306_delete(ssd1306_handle_t dev, bool del_bus);

/**
 * @brief   Write command or data to ssd1306
 *
 * @param   device object handle of ssd1306
 * @param   will write data
 * @param   command
 *
 * @return
 *     - ESP_OK Success
 *     - ESP_FAIL Fail
 */
esp_err_t ssd1306_write_byte(ssd1306_handle_t dev, uint8_t chData,
        uint8_t chCmd);

/**
 * @brief   draw point on (x, y)
 *
 * @param   device object handle of ssd1306
 * @param   chXpos: Specifies the X position
 * @param   chYpos: Specifies the Y position
 * @param   point
 *
 * @return
 *     - NULL
 */
void ssd1306_draw_point(ssd1306_handle_t dev, uint8_t chXpos, uint8_t chYpos,
        uint8_t chPoint);

/**
 * @brief   Draw rectangle on (x1,y1)-(x2,y2)
 *
 * @param   device object handle of ssd1306
 * @param   x1, y1, x2, y2, dot
 *
 * @return
 *     - ESP_OK Success
 *     - ESP_FAIL Fail
 */
esp_err_t ssd1306_fill_rectangle_screen(ssd1306_handle_t dev,
        uint8_t chXpos1, uint8_t chYpos1, uint8_t chXpos2, uint8_t chYpos2,
        uint8_t chDot);

/**
 * @brief   display char on (x, y),and set size, mode
 *
 * @param   device object handle of ssd1306
 * @param   chXpos: Specifies the X position
 * @param   chYpos: Specifies the Y position
 * @param   display char, size, mode
 *
 * @return
 *     - NULL
 */
void ssd1306_display_char(ssd1306_handle_t dev, uint8_t chXpos,
        uint8_t chYpos, uint8_t chChr, uint8_t chSize, uint8_t chMode);

/**
 * @brief   display number on (x, y),and set length, size, mode
 *
 * @param   device object handle of ssd1306
 * @param   chXpos: Specifies the X position
 * @param   chYpos: Specifies the Y position
 * @param   number, length, size
 *
 * @return
 *     - NULL
 */
void ssd1306_display_num(ssd1306_handle_t dev, uint8_t chXpos,
        uint8_t chYpos, uint32_t chNum, uint8_t chLen, uint8_t chSize);

/**
 * @brief   display 1616char on (x, y)
 *
 * @param   device object handle of ssd1306
 * @param   chXpos: Specifies the X position
 * @param   chYpos: Specifies the Y position
 * @param   1616char
 *
 * @return
 *     - NULL
 */
void ssd1306_draw_1616char(ssd1306_handle_t dev, uint8_t chXpos,
        uint8_t chYpos, uint8_t chChar);

/**
 * @brief   display 3216char on (x, y)
 *
 * @param   device object handle of ssd1306
 * @param   chXpos: Specifies the X position
 * @param   chYpos: Specifies the Y position
 * @param   3216char
 *
 * @return
 *     - NULL
 */
void ssd1306_draw_3216char(ssd1306_handle_t dev, uint8_t chXpos,
        uint8_t chYpos, uint8_t chChar);

/**
 * @brief   draw bitmap on (x, y),and set width, height
 *
 * @param   device object handle of ssd1306
 * @param   chXpos: Specifies the X position
 * @param   chYpos: Specifies the Y position
 * @param   bitmap
 * @param   width and height
 *
 * @return
 *     - NULL
 */
void ssd1306_draw_bitmap(ssd1306_handle_t dev, uint8_t chXpos,
        uint8_t chYpos, const uint8_t *pchBmp, uint8_t chWidth,
        uint8_t chHeight);

/**
 * @brief   refresh dot matrix panel
 *
 * @param   device object handle of ssd1306

 * @return
 *     - ESP_OK Success
 *     - ESP_FAIL Fail
 **/
esp_err_t ssd1306_refresh_gram(ssd1306_handle_t dev);

/**
 * @brief   Clear screen
 *
 * @param   device object handle of ssd1306
 *
 * @return
 *     - ESP_OK Success
 *     - ESP_FAIL Fail
 **/
esp_err_t ssd1306_clear_screen(ssd1306_handle_t dev, uint8_t chFill);

/**
 * @brief   Displays a string on the screen
 *
 * @param   device object handle of ssd1306
 * @param   chXpos: Specifies the X position
 * @param   chYpos: Specifies the Y position
 * @param   pchString: Pointer to a string to display on the screen
 *
 * @return
 *     - ESP_OK Success
 *     - ESP_FAIL Fail
 **/
esp_err_t ssd1306_display_string(ssd1306_handle_t dev, uint8_t chXpos,
        uint8_t chYpos, const uint8_t *pchString, uint8_t chSize,
        uint8_t chMode);

/**
 * @brief   Set column start address
 *
 * @param   device object handle of ssd1306
 *
 * @retval  None
 **/
void set_column_start_address(ssd1306_handle_t device);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
/**
 * class of ssd1306
 */
class CSsd1306
{
private:
    ssd1306_handle_t m_dev_handle;
    CI2CBus *bus;

    /**
     * prevent copy constructing
     */
    CSsd1306(const CSsd1306&);

    CSsd1306& operator =(const CSsd1306&);
public:
    /**
     * @brief   Constructor of CSsd1306 class
     * @param   p_i2c_bus pointer to CI2CBus object
     * @param   addr sensor device address
     */
    CSsd1306(CI2CBus *p_i2c_bus, uint8_t addr = SSD1306_I2C_ADDRESS);

    /**
     * @brief   Destructor function of CSsd1306 class
     */
    ~CSsd1306();

    /**
     * @brief draw point on (x, y)
     *
     * @param   device object handle of ssd1306
     * @param   chXpos: Specifies the X position
     * @param   chYpos: Specifies the Y position
     * @param   point
     *
     * @return
     *     - NULL
     */
    void draw_point(uint8_t chXpos, uint8_t chYpos, uint8_t chPoint);

    /**
     * @brief   Draw rectangle on (x1,y1) (x2,y2)
     *
     * @param   device object handle of ssd1306
     * @param   x1, y1, x2, y2, dot
     *
     * @return
     *     - ESP_OK Success
     *     - ESP_FAIL Fail
     */
    esp_err_t fill_rectangle_screen(uint8_t chXpos1, uint8_t chYpos1,
            uint8_t chXpos2, uint8_t chYpos2, uint8_t chDot);

    /**
     * @brief   display char on (x, y),and set size, mode
     *
     * @param   device object handle of ssd1306
     * @param   chXpos: Specifies the X position
     * @param   chYpos: Specifies the Y position
     * @param   display char, size, mode
     *
     * @return
     *     - NULL
     */
    void display_char(uint8_t chXpos, uint8_t chYpos, uint8_t chChr,
            uint8_t chSize, uint8_t chMode);

    /**
     * @brief   display num on (x, y),and set length, size, mode
     *
     * @param   device object handle of ssd1306
     * @param   chXpos: Specifies the X position
     * @param   chYpos: Specifies the Y position
     * @param   number, length, size
     *
     * @return
     *     - NULL
     */
    void display_num(uint8_t chXpos, uint8_t chYpos, uint32_t chNum,
            uint8_t chLen, uint8_t chSize);

    /**
     * @brief   display 1616char on (x, y)
     *
     * @param   device object handle of ssd1306
     * @param   chXpos: Specifies the X position
     * @param   chYpos: Specifies the Y position
     * @param   1616char
     *
     * @return
     *     - NULL
     */
    void draw_1616char(uint8_t chXpos, uint8_t chYpos, uint8_t chChar);

    /**
     * @brief   display 3216char on (x, y)
     *
     * @param   device object handle of ssd1306
     * @param   chXpos: Specifies the X position
     * @param   chYpos: Specifies the Y position
     * @param   3216char
     *
     * @return
     *     - NULL
     */
    void draw_3216char(uint8_t chXpos, uint8_t chYpos, uint8_t chChar);

    /**
     * @brief   draw bitmap on (x, y),and set width, height
     *
     * @param   device object handle of ssd1306
     * @param   chXpos: Specifies the X position
     * @param   chYpos: Specifies the Y position
     * @param   bitmap
     * @param   width and height
     *
     * @return
     *     - NULL
     */
    void draw_bitmap(uint8_t chXpos, uint8_t chYpos,
            const uint8_t *pchBmp, uint8_t chWidth, uint8_t chHeight);

    /**
     * @brief   refresh dot matrix panel
     *
     * @param   device object handle of ssd1306

     * @return
     *     - ESP_OK Success
     *     - ESP_FAIL Fail
     **/
    esp_err_t refresh_gram(void);

    /**
     * @brief   Clear screen
     *
     * @param   device object handle of ssd1306
     *
     * @return
     *     - ESP_OK Success
     *     - ESP_FAIL Fail
     **/
    esp_err_t clear_screen(uint8_t chFill);

    /**
     * @brief   Displays a string on the screen
     *
     * @param   device object handle of ssd1306
     * @param   chXpos: Specifies the X position
     * @param   chYpos: Specifies the Y position
     * @param   pchString: Pointer to a string to display on the screen
     *
     * @return
     *     - ESP_OK Success
     *     - ESP_FAIL Fail
     **/
    esp_err_t display_string(uint8_t chXpos, uint8_t chYpos,
            const uint8_t *pchString, uint8_t chSize, uint8_t chMode);

    /**
     * @brief   Displays a string on the screen
     *
     * @return  device object handle of ssd1306
     * **/
    ssd1306_handle_t get_dev_handle();
};
#endif

#endif

