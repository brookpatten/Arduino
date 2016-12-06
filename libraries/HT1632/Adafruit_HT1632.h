#include "Adafruit_GFX.h"

#ifndef ADA_HT1632_H_
#define ADA_HT1632_H_

#if(ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

#define ADA_HT1632_READ  0x6
#define ADA_HT1632_WRITE 0x5
#define ADA_HT1632_COMMAND 0x4

#define ADA_HT1632_SYS_DIS 0x00
#define ADA_HT1632_SYS_EN 0x01
#define ADA_HT1632_LED_OFF 0x02
#define ADA_HT1632_LED_ON 0x03
#define ADA_HT1632_BLINK_OFF 0x08
#define ADA_HT1632_BLINK_ON 0x09
#define ADA_HT1632_SLAVE_MODE 0x10
#define ADA_HT1632_MASTER_MODE 0x14
#define ADA_HT1632_INT_RC 0x18
#define ADA_HT1632_EXT_CLK 0x1C
#define ADA_HT1632_PWM_CONTROL 0xA0

#define ADA_HT1632_COMMON_8NMOS  0x20
#define ADA_HT1632_COMMON_16NMOS  0x24
#define ADA_HT1632_COMMON_8PMOS  0x28
#define ADA_HT1632_COMMON_16PMOS  0x2C

class Adafruit_HT1632 {

 public:
  Adafruit_HT1632(int8_t data, int8_t wr, int8_t cs, int8_t rd = -1);

  void begin(uint8_t type);
  
  void clrPixel(uint16_t i);
  void setPixel(uint16_t i);

  void blink(boolean state);
  void setBrightness(uint8_t pwm);

  void clearScreen();
  void fillScreen();
  void writeScreen();
  void dumpScreen();
  
 private:
  int8_t WIDTH, HEIGHT;
  int8_t _data, _cs, _wr, _rd;
  uint8_t ledmatrix[48];     // 16 * 24 / 8
  void sendcommand(uint8_t c);
  void writedata(uint16_t d, uint8_t bits);
  void writeRAM(uint8_t addr, uint8_t data);
};

class Adafruit_HT1632LEDMatrix : public Adafruit_GFX {
 public:
  Adafruit_HT1632LEDMatrix(uint8_t data, uint8_t wr, uint8_t cs1);
  Adafruit_HT1632LEDMatrix(uint8_t data, uint8_t wr, uint8_t cs1, uint8_t cs2);
  Adafruit_HT1632LEDMatrix(uint8_t data, uint8_t wr, uint8_t cs1, 
		  uint8_t cs, uint8_t cs3);
  Adafruit_HT1632LEDMatrix(uint8_t data, uint8_t wr, uint8_t cs1, 
		  uint8_t cs2, uint8_t cs3, uint8_t cs4);

 void begin(uint8_t type);
 void clearScreen(void);
 void fillScreen(void);
 void blink(boolean b);
 void setBrightness(uint8_t brightness);
 void writeScreen();

  void clrPixel(uint8_t x, uint8_t y);
  void setPixel(uint8_t x, uint8_t y);
  void drawPixel(int16_t x, int16_t y, uint16_t color);

 private:
  Adafruit_HT1632 *matrices;
  uint8_t matrixNum;
};


#endif /* Adafruit HT1632_H_ */
