/*
 * button.h
 *
 *  Created on: Mar 4, 2026
 *      Author: bahti
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "stm32f4xx_hal.h"

// Debounce süresi (ms) - şimdilik 30ms yeter
#define DEBOUNCE_MS 30

// Tek bir butonun durumunu tutan yapı
typedef struct {
    GPIO_TypeDef *port;   // hangi GPIO portu? (GPIOA, GPIOD...)
    uint16_t pin;         // hangi pin? (GPIO_PIN_0, GPIO_PIN_10...)

    uint8_t raw;          // anlık okuma (active=1 basılı)
    uint8_t stable;       // debounce sonrası kararlı değer (active=1 basılı)
    uint32_t t_change;    // raw değiştiği anın tick'i

    uint8_t press_evt;    // "basıldı" olayı (1 kez)
} button_t;

// Driver fonksiyonları (şimdilik sadece imza)
void BTN_Init(button_t *b, GPIO_TypeDef *port, uint16_t pin);
void BTN_Update(button_t *b, uint32_t now_ms);
uint8_t BTN_GetPress(button_t *b);


#endif /* INC_BUTTON_H_ */
