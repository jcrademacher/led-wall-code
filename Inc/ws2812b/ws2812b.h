/*

  WS2812B CPU and memory efficient library

  Date: 28.9.2016

  Author: Martin Hubacek
  	  	  http://www.martinhubacek.cz
  	  	  @hubmartin

  Licence: MIT License

*/

#ifndef WS2812B_H_
#define WS2812B_H_
#include "main.h"
#include <stdint.h>

// GPIO enable command
#define WS2812B_GPIO_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()
// LED output port
#define WS2812B_PORT GPIOB
// LED output pins
#define WS2812B_PINS ( \
	UC_LED1_Pin \
	| UC_LED3_Pin \
	| UC_LED5_Pin \
	| UC_LED7_Pin \
	| UC_LED9_Pin \
	| UC_LED11_Pin \
	| UC_LED13_Pin \
	| UC_LED15_Pin \
	| UC_LED17_Pin \
	| UC_LED19_Pin \
	| UC_LED21_Pin \
	| UC_LED23_Pin \
	| UC_LED25_Pin \
	| UC_LED27_Pin)

// How many LEDs are in the series - only valid multiples by two
#define WS2812B_NUMBER_OF_LEDS 22
// Number of paralel output LED strips. Each has its own buffer.
// Supports up to 16 outputs on a single GPIO port
#define WS2812_BUFFER_COUNT 14

// Choose one of the bit-juggling setpixel implementation
// *******************************************************
//#define SETPIX_1	// For loop, works everywhere, slow
//#define SETPIX_2	// Bit band in a loop
//#define SETPIX_3	// Like SETPIX_1 but with unrolled loop
#define SETPIX_4	// Fastest copying using bit-banding


// DEBUG OUTPUT
// ********************

// Set during DMA Half and Full transfer IRQ to debug how long IRQ is processing
#define LED_BLUE_PORT GPIOA
#define LED_BLUE_PIN GPIO_PIN_1

// Public functions
// ****************
void ws2812b_init();
void ws2812b_handle();

// Library structures
// ******************
// This value sets number of periods to generate 50uS Treset signal
#define WS2812_RESET_PERIOD 50

typedef struct WS2812_BufferItem {
	uint8_t* frameBufferPointer;
	uint32_t frameBufferSize;
	uint32_t frameBufferCounter;
	uint8_t channel;	// digital output pin/channel
} WS2812_BufferItem;



typedef struct WS2812_Struct
{
	WS2812_BufferItem item[WS2812_BUFFER_COUNT];
	uint8_t transferComplete;
	uint8_t startTransfer;
	uint32_t timerPeriodCounter;
	uint32_t repeatCounter;
} WS2812_Struct;

WS2812_Struct ws2812b;

// Bit band stuff
#define RAM_BASE 0x20000000
#define RAM_BB_BASE 0x22000000
#define Var_ResetBit_BB(VarAddr, BitNumber) (*(volatile uint32_t *) (RAM_BB_BASE | ((VarAddr - RAM_BASE) << 5) | ((BitNumber) << 2)) = 0)
#define Var_SetBit_BB(VarAddr, BitNumber) (*(volatile uint32_t *) (RAM_BB_BASE | ((VarAddr - RAM_BASE) << 5) | ((BitNumber) << 2)) = 1)
#define Var_GetBit_BB(VarAddr, BitNumber) (*(volatile uint32_t *) (RAM_BB_BASE | ((VarAddr - RAM_BASE) << 5) | ((BitNumber) << 2)))
#define BITBAND_SRAM(address, bit) ( (__IO uint32_t *) (RAM_BB_BASE + (((uint32_t)address) - RAM_BASE) * 32 + (bit) * 4))

#define varSetBit(var,bit) (Var_SetBit_BB((uint32_t)&var,bit))
#define varResetBit(var,bit) (Var_ResetBit_BB((uint32_t)&var,bit))
#define varGetBit(var,bit) (Var_GetBit_BB((uint32_t)&var,bit))

static void ws2812b_set_pixel(uint8_t row, uint16_t column, uint8_t red, uint8_t green, uint8_t blue);
void DMA_TransferCompleteHandler(DMA_HandleTypeDef *DmaHandle);
void DMA_TransferHalfHandler(DMA_HandleTypeDef *DmaHandle);
void DMA_TransferError(DMA_HandleTypeDef *DmaHandle);

#endif /* WS2812B_H_ */
