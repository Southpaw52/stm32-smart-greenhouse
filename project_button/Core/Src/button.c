/*
 * button.c
 *
 *  Created on: Mar 4, 2026
 *      Author: bahti
 */

#include "button.h"

void BTN_Init(button_t *b, GPIO_TypeDef *port, uint16_t pin)
{
	b->port = port;
	b->pin  = pin;

	// ACTIVE-LOW normalize:
	// pin LOW (RESET) => basılı => active=1
	// pin HIGH (SET)  => boşta  => active=0
	uint8_t active = (HAL_GPIO_ReadPin(port, pin) == GPIO_PIN_RESET) ? 1 : 0;

	b->raw       = active; //ham sinyal
	b->stable    = active;
	b->t_change  = HAL_GetTick();
	b->press_evt = 0;
}

void BTN_Update(button_t *b, uint32_t now_ms)
{
    // active-low normalize: basılı=1, boşta=0
    uint8_t r = (HAL_GPIO_ReadPin(b->port, b->pin) == GPIO_PIN_RESET) ? 1 : 0;

    // 1) raw değiştiyse zamanı güncelle
    if (r != b->raw)
    {
        b->raw = r;
        b->t_change = now_ms;
    }

    // 2) raw yeterince sabit kaldıysa stable'a geçir
    if ((now_ms - b->t_change) >= DEBOUNCE_MS)
    {
        if (b->stable != b->raw)
        {
            b->stable = b->raw;

            // 3) sadece basılma anında event üret (0 -> 1)
            if (b->stable == 1)
            {
                b->press_evt = 1;
            }
        }
    }
}

uint8_t BTN_GetPress(button_t *b)
{
	if(b->press_evt)
	{
		b->press_evt =0;
		return 1;
	}

	return 0;
}
