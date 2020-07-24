#ifndef __led_H
#define __led_H
#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>
#include "ws2812b.h"

#define MAX_BRIGHTNESS 2000.0

extern uint8_t frame_buffer[WS2812_BUFFER_COUNT][3*WS2812B_NUMBER_OF_LEDS];

void led_init();
void led_test(uint8_t r, uint8_t g, uint8_t b);
void led_transfer();
void led_bars(uint8_t* level_ticker, uint8_t speed);
void led_bar(uint8_t bar, uint8_t level, uint8_t r, uint8_t g, uint8_t b);

#ifdef __cplusplus
 }
#endif
#endif