#ifndef SERLCD_H
#define SERLCD_H

#include <stdint.h>

#define DISPLAY_COLS  20
#define DISPLAY_ROWS  4
#define DISPLAY_SIZE  (DISPLAY_ROWS * (DISPLAY_COLS + 1))  // 84, includes null terminators

typedef union
{
	uint8_t buffer[DISPLAY_SIZE];  // 84
	
	struct
	{
		uint8_t ln1[DISPLAY_COLS + 1];  // 21
		uint8_t ln2[DISPLAY_COLS + 1];  // 21
		uint8_t ln3[DISPLAY_COLS + 1];  // 21
		uint8_t ln4[DISPLAY_COLS + 1];  // 21
	} buf;
	
} dsp_t;

// External declarations (defined in serlcd.c)
dsp_t dsp;

// Functions called from main
void init_avr_SPI0(void);
void init_SerLCD_SPI0(void);
void SPI0_SerLCD_page0(void);
void SPI0_SerLCD_page1(void);
void SPI0_SerLCD_page1_disable(void);
void SPI0_SerLCD_page2(void);
void SPI0_SerLCD_clear(void);

void init_avr_USART2(void);
void init_SerLCD(uint16_t);
void USART2_SerLCD_page0(void);
void USART2_SerLCD_page1(void);
void USART2_SerLCD_page2(void);

void USART2_SerLCD_byte_write(char c);
void USART2_SerLCD_clear(void);

volatile uint8_t tx_char;

#endif /* SERLCD_H */