#include "led.h"
#include "main.h"

#include <stdint.h>
#include "ws2812b.h"
#include "visEffect.h"
#include <math.h>
#include "arm_math.h"
#include <stdio.h>

#define BRIGHTNESS_RATIO  ((MAX_BRIGHTNESS - (float32_t)(ADC_values[2])) / MAX_BRIGHTNESS)
#define BRIGHTNESS        (255 * BRIGHTNESS_RATIO)


uint8_t frame_buffer[WS2812_BUFFER_COUNT][3*WS2812B_NUMBER_OF_LEDS] = {0};
uint16_t ADC_values[3 * NUM_SAMPLES];

extern void print(char* str);

void led_init() {
  // UC_LED1_Pin == GPIO_PIN_0
  ws2812b.item[0].channel = 0;            
  ws2812b.item[0].frameBufferPointer = &frame_buffer[0];
  ws2812b.item[0].frameBufferSize = sizeof(&frame_buffer[0]);

  // UC_LED3_Pin == GPIO_PIN_1
  ws2812b.item[1].channel = 1;            
  ws2812b.item[1].frameBufferPointer = &frame_buffer[1];
  ws2812b.item[1].frameBufferSize = sizeof(&frame_buffer[1]);

  // UC_LED5_Pin == GPIO_PIN_2
  ws2812b.item[2].channel = 2;            
  ws2812b.item[2].frameBufferPointer = &frame_buffer[2];
  ws2812b.item[2].frameBufferSize = sizeof(&frame_buffer[2]);

  // UC_LED7_Pin == GPIO_PIN_10
  ws2812b.item[3].channel = 10;            
  ws2812b.item[3].frameBufferPointer = &frame_buffer[3];
  ws2812b.item[3].frameBufferSize = sizeof(&frame_buffer[3]);

  // UC_LED9_Pin == GPIO_PIN_12
  ws2812b.item[4].channel = 12;            
  ws2812b.item[4].frameBufferPointer = &frame_buffer[4];
  ws2812b.item[4].frameBufferSize = sizeof(&frame_buffer[4]);

  // UC_LED11_Pin == GPIO_PIN_13
  ws2812b.item[5].channel = 13;            
  ws2812b.item[5].frameBufferPointer = &frame_buffer[5];
  ws2812b.item[5].frameBufferSize = sizeof(&frame_buffer[5]);

  // UC_LED13_Pin == GPIO_PIN_14
  ws2812b.item[6].channel = 14;            
  ws2812b.item[6].frameBufferPointer = &frame_buffer[6];
  ws2812b.item[6].frameBufferSize = sizeof(&frame_buffer[6]);

  // UC_LED15_Pin == GPIO_PIN_15
  ws2812b.item[7].channel = 15;            
  ws2812b.item[7].frameBufferPointer = &frame_buffer[7];
  ws2812b.item[7].frameBufferSize = sizeof(&frame_buffer[7]);

  // UC_LED17_Pin == GPIO_PIN_3
  ws2812b.item[8].channel = 3;            
  ws2812b.item[8].frameBufferPointer = &frame_buffer[8];
  ws2812b.item[8].frameBufferSize = sizeof(&frame_buffer[8]);

  // UC_LED19_Pin == GPIO_PIN_4
  ws2812b.item[9].channel = 4;            
  ws2812b.item[9].frameBufferPointer = &frame_buffer[9];
  ws2812b.item[9].frameBufferSize = sizeof(&frame_buffer[9]);

  // UC_LED21_Pin == GPIO_PIN_5
  ws2812b.item[10].channel = 5;            
  ws2812b.item[10].frameBufferPointer = &frame_buffer[10];
  ws2812b.item[10].frameBufferSize = sizeof(&frame_buffer[10]);

  // UC_LED23_Pin == GPIO_PIN_6
  ws2812b.item[11].channel = 6;            
  ws2812b.item[11].frameBufferPointer = &frame_buffer[11];
  ws2812b.item[11].frameBufferSize = sizeof(&frame_buffer[11]);

  // UC_LED25_Pin == GPIO_PIN_7
  ws2812b.item[12].channel = 7;            
  ws2812b.item[12].frameBufferPointer = &frame_buffer[12];
  ws2812b.item[12].frameBufferSize = sizeof(&frame_buffer[12]);

  // UC_LED27_Pin == GPIO_PIN_8
  ws2812b.item[13].channel = 8;            
  ws2812b.item[13].frameBufferPointer = &frame_buffer[13];
  ws2812b.item[13].frameBufferSize = sizeof(&frame_buffer[13]);

  ws2812b_init();

  ws2812b.startTransfer = 1;
  ws2812b_handle();
}

void led_reset() {
  uint8_t strip, led;

  for(strip = 0; strip < WS2812_BUFFER_COUNT; ++strip) {
    for(led = 0; led < WS2812B_NUMBER_OF_LEDS; ++led) {
      frame_buffer[strip][led*3 + 0] = 0;
      frame_buffer[strip][led*3 + 1] = 0;
      frame_buffer[strip][led*3 + 2] = 0;
    }
  }
}

void led_transfer() {
  if(ws2812b.transferComplete) {
    ws2812b.startTransfer = 1;
    ws2812b_handle();
  }
}

void led_test(uint8_t r, uint8_t g, uint8_t b) {
  uint8_t led, strip;

  for(strip = 0; strip < WS2812_BUFFER_COUNT; ++strip) {
    //visRainbow(frame_buffer[strip], 3*WS2812B_NUMBER_OF_LEDS, WS2812B_NUMBER_OF_LEDS);
    for(led = 0; led < WS2812B_NUMBER_OF_LEDS; ++led) {
      frame_buffer[strip][led*3 + 0] = (float32_t)r * BRIGHTNESS_RATIO;
      frame_buffer[strip][led*3 + 1] = (float32_t)g * BRIGHTNESS_RATIO;
      frame_buffer[strip][led*3 + 2] = (float32_t)b * BRIGHTNESS_RATIO;
      
      
      led_transfer();
      HAL_Delay(50);
      
    }

    // HAL_Delay(1000);
    //   led_transfer();

    // frame_buffer[strip][4*3 + 0] = r;
    // frame_buffer[strip][5*3 + 1] = g;
    // frame_buffer[strip][6*3 + 2] = b;

    // HAL_Delay(200);
    // led_transfer();
  }
}

// bar indicates the horizontal location of the LEDs to be lit up, indexed from 0
// level indicates the highest LED that will be lit, indexed from 0, all others above will be off
void led_bar(uint8_t bar, uint8_t level, uint8_t r, uint8_t g, uint8_t b) {
  bar = bar >= WS2812_BUFFER_COUNT * 2 - 1 ? (WS2812_BUFFER_COUNT - 1) * 2 : bar;
  bar = bar < 0 ? 0 : bar;

  uint8_t strip = (WS2812_BUFFER_COUNT * 2 - bar + 1) / 2 - 1;

  uint8_t _crementer;
  uint8_t loop_start;

  if(bar % 2) {
    _crementer = -1;
    loop_start = WS2812B_NUMBER_OF_LEDS - 1;
  }
  else {
    _crementer = 1;
    loop_start = 0;
  }
  
  uint8_t led;
  for(led = loop_start; led != abs(WS2812B_NUMBER_OF_LEDS / 2 - loop_start); led += _crementer) {

    frame_buffer[strip][led*3 + 0] = abs(led - loop_start) <= level ? (uint8_t)((float32_t)r * BRIGHTNESS_RATIO) : 0;
    frame_buffer[strip][led*3 + 1] = abs(led - loop_start) <= level ? (uint8_t)((float32_t)g * BRIGHTNESS_RATIO) : 0;
    frame_buffer[strip][led*3 + 2] = abs(led - loop_start) <= level ? (uint8_t)((float32_t)b * BRIGHTNESS_RATIO) : 0;
  }
}

void led_bars(uint8_t* level_ticker, uint8_t speed) {
  int strip, iled;

  float32_t sin_arg = ((float32_t)*level_ticker) / 255.0;
  float32_t sin_val = arm_sin_f32(2*PI*sin_arg);
  
  uint8_t bar_level = WS2812B_NUMBER_OF_LEDS / 4 - ((float32_t)WS2812B_NUMBER_OF_LEDS) / 4.0 * sin_val + 1; 
  char pstr[40];
  uint8_t _crementer;
  uint8_t bar_level_offset;
  uint8_t led;

  // sprintf(pstr, "ARG: %f, VAL: %f, TICK: %d, LEV: %d", sin_arg, sin_val, *level_ticker, bar_level);
  // print(pstr);

  for(strip = WS2812_BUFFER_COUNT - 1; strip >= 0; --strip) {
    _crementer = 1;
    bar_level_offset = 0;
   
    led = 0;
    iled = 0;
    for(iled = 0; iled < WS2812B_NUMBER_OF_LEDS; ++iled) {
      led = iled == WS2812B_NUMBER_OF_LEDS / 2 ? WS2812B_NUMBER_OF_LEDS - 1 : led;

      if(iled >= WS2812B_NUMBER_OF_LEDS / 2) {
        _crementer = -1;
        bar_level_offset = WS2812B_NUMBER_OF_LEDS - 1;
      }
      else {
        _crementer = 1;
        bar_level_offset = 0;
      }

      frame_buffer[strip][led*3 + 0] = 0;
      frame_buffer[strip][led*3 + 1] = abs(led - bar_level_offset) < bar_level ? BRIGHTNESS : 0;
      frame_buffer[strip][led*3 + 2] = 0;
        
      led += _crementer;
    }
  }

  *level_ticker = *level_ticker + speed;
}