/********************************************************************
 * File:        serlcd.c
 * Author:      Jin Yuan Chen
 * Created:     4/24/2026
 * Modified:    4/28/2026
 *
 * @file serlcd.c
 * @brief SPI0-based SERLCD driver for multi-page display output.
 *
 * @details
 * This module provides interrupt-driven SPI0 communication with
 * a SERLCD display. It supports formatted multi-page output for:
 * - Sensor measurements
 * - Control register debugging
 * - System identification page
 ********************************************************************/

#include "global.h"
#include "serlcd.h"

void SPI0_SerLCD_byte_write(char);
void SPI0_SerLCD_line(int);

//=================================================================//
//                     SPI0 INITIALIZATION                         //
//=================================================================//

/**
 * @brief Initialize SPI0 for SERLCD communication.
 *
 * @details
 * Pseudo-logic:
 * @code
 * 1. Configure SPI pins (MOSI, SCK, SS)
 * 2. Set SPI mode (Mode 0, MSB first)
 * 3. Set clock rate (fosc/4 or appropriate)
 * 4. Enable SPI as master
 * 5. Enable SPI interrupt
 * 6. Configure SS pin as output and pull low for transmission
 * @endcode
 */

void init_avr_SPI0(void)
{
	// Configure SPI0 Control Register B
	
	// Configure SPI0 Control Register A
	SPI0.CTRLA = (SPI_MASTER_bm | SPI_PRESC_DIV4_gc | SPI_CLK2X_bm | SPI_ENABLE_bm);         // Enable SPI
	SPI0.CTRLB = 0x04;                  // Standard mode, no SS control

    
	// PIN4 = MOSI, PIN6 = SCK, PIN7 = SS,
	PORTA.DIR |= (PIN4_bm | PIN6_bm | PIN7_bm);
	PORTA.OUTSET |= PIN7_bm;  // Set SS and SCK high initially

	// Enable SPI interrupt on receive complete
}

//=================================================================//
//                        SERLCD PAGE 0                             //
//=================================================================//

/**
 * @brief System identification / splash page.
 *
 * @details
 * Pseudo-logic:
 * @code
 * 1. Send LCD control header
 * 2. Load static text into buffer
 * 3. Transmit buffer byte-by-byte
 * 4. Delay for display stability
 * @endcode
 */
void SPI0_SerLCD_page0(void)
{
	snprintf((char*)dsp.buf.ln1, 21, "  AK9723AJ Temp/C02 ");

	snprintf((char*)dsp.buf.ln2, 21, "  ---- Sensor ----  ");

	snprintf((char*)dsp.buf.ln3, 21, "   S2026, ESE 381   ");

	snprintf((char*)dsp.buf.ln4, 21, "JIN Y. CHEN, ERIC WU");

    for (int row = 0; row < DISPLAY_ROWS; row++) {
	    SPI0_SerLCD_line(row + 1);
	    for (int col = 0; col < DISPLAY_COLS; col++) {
		    uint8_t c = dsp.buffer[row * (DISPLAY_COLS + 1) + col];
		    SPI0_SerLCD_byte_write(c != '\0' ? c : ' ');
	    }
    }
}

//=================================================================//
//                        SERLCD PAGE 1                             //
//=================================================================//

/**
 * @brief Real-time sensor measurement display.
 *
 * @details
 * Pseudo-logic:
 * @code
 * 1. Load IR1, IR2, VF values
 * 2. Format values into fixed-width strings
 * 3. Transfer buffer to SERLCD
 * 4. Delay for display refresh
 * @endcode
 */
void SPI0_SerLCD_page1(void)
{
    snprintf((char*)dsp.buf.ln1, 21, "IR1 = 0xFF%02X%02X%02X       ", 
             meas.at.IR1H, meas.at.IR1M, meas.at.IR1L);
    snprintf((char*)dsp.buf.ln2, 21, "IR1 = %7.2f mV     ", ir1_mV);
    snprintf((char*)dsp.buf.ln3, 21, "IR2 = %7.2f mV     ", ir2_mV);
    snprintf((char*)dsp.buf.ln4, 21, "VF  = %7.2f mV     ", vf_mV);

    for (int row = 0; row < DISPLAY_ROWS; row++) {
	    SPI0_SerLCD_line(row + 1);
	    for (int col = 0; col < DISPLAY_COLS; col++) {
		    uint8_t c = dsp.buffer[row * (DISPLAY_COLS + 1) + col];
		    SPI0_SerLCD_byte_write(c != '\0' ? c : ' ');
	    }
    }
}

void SPI0_SerLCD_page1_disable(void)
{
    snprintf((char*)dsp.buf.ln1, DISPLAY_COLS + 1, "                    ");
    snprintf((char*)dsp.buf.ln2, DISPLAY_COLS + 1, "   Display  OFF     ");
    snprintf((char*)dsp.buf.ln3, DISPLAY_COLS + 1, "                    ");
    snprintf((char*)dsp.buf.ln4, DISPLAY_COLS + 1, "                    ");

	for (int row = 0; row < DISPLAY_ROWS; row++) {
		SPI0_SerLCD_line(row + 1);
		for (int col = 0; col < DISPLAY_COLS; col++) {
			uint8_t c = dsp.buffer[row * (DISPLAY_COLS + 1) + col];
			SPI0_SerLCD_byte_write(c != '\0' ? c : ' ');
		}
	}
}

//=================================================================//
//                        SERLCD PAGE 2                             //
//=================================================================//

/**
 * @brief Control register debug page.
 *
 * @details
 * Pseudo-logic:
 * @code
 * 1. Read control register values (C0�C9)
 * 2. Format into display buffer
 * 3. Transmit buffer to LCD
 * 4. Delay for readability
 * @endcode
 */
void SPI0_SerLCD_page2(void)
{
    snprintf((char*)dsp.buf.ln1, 21, "AK9723 cntl,  C0=%02X ", cntl.at.c0);

    snprintf((char*)dsp.buf.ln2, 21,
             "C1=%02X, C2=%02X, C3=%02X ",
             cntl.at.c1, cntl.at.c2, cntl.at.c3);

    snprintf((char*)dsp.buf.ln3, 21,
             "C4=%02X, C5=%02X, C6=%02X ",
             cntl.at.c4, cntl.at.c5, cntl.at.c6);

    snprintf((char*)dsp.buf.ln4, 21,
             "C7=%02X, C8=%02X, C9=%02X ",
             cntl.at.c7, cntl.at.c8, cntl.at.c9);

    for (int row = 0; row < DISPLAY_ROWS; row++) {
	    SPI0_SerLCD_line(row + 1);
	    for (int col = 0; col < DISPLAY_COLS; col++) {
		    uint8_t c = dsp.buffer[row * (DISPLAY_COLS + 1) + col];
		    SPI0_SerLCD_byte_write(c != '\0' ? c : ' ');
	    }
    }
}

//=================================================================//
//                     SPI0 BYTE TRANSMISSION                      //
//=================================================================//

/**
 * @brief Send single character to SERLCD via SPI0.
 *
 * @param c Character to transmit
 *
 * @details
 * Pseudo-logic:
 * @code
 * 1. Pull SS (CS) low to select device
 * 2. Wait until SPI is ready
 * 3. Load character into SPI data register
 * 4. Wait for transmission to complete
 * 5. Pull SS (CS) high to deselect
 * @endcode
 */
void SPI0_SerLCD_byte_write(char c)
{
	PORTA.OUTCLR = PIN7_bm;
	SPI0.DATA = c;
	while (!(SPI0.INTFLAGS & SPI_IF_bm)); 
	PORTA.OUTSET = PIN7_bm;
	_delay_us(400);  //around 0.40 ms for stable operation
}

/**
 * @brief Clear the SerLCD display.
 *
 * @details
 * Sends clear command sequence for SPI mode.
 */
void SPI0_SerLCD_clear(void)
{
    SPI0_SerLCD_byte_write('-');  // Command prefix
    SPI0_SerLCD_byte_write('|');  // Clear command (for OpenLCD firmware)
    SPI0_SerLCD_line(1);
}

/**
 * @brief Move cursor to specified line.
 *
 * @param i Line number (1-4)
 *
 * @details
 * Uses OpenLCD firmware commands (prefix '-') for SPI mode.
 */
void SPI0_SerLCD_line(int i)
{
	if (i >= 1 && i <= 4) {
		SPI0_SerLCD_byte_write(0xFE);
		
		switch(i) {
			case 1:
			SPI0_SerLCD_byte_write(0x80);
			break;
			case 2:
			SPI0_SerLCD_byte_write(0xC0);
			break;
			case 3:
			SPI0_SerLCD_byte_write(0x94);
			break;
			case 4:
			SPI0_SerLCD_byte_write(0xD4);
			break;
		}
	}
}