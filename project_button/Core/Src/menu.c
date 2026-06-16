/*
 * menu.c
 *
 *  Created on: 22 Mar 2026
 *      Author: bahti
 */
#include "menu.h"

void MENU_Init(menu_t *menu)
{
	menu->current = plant_feslegen;
}

void MENU_Next(menu_t *menu)
{
	if (menu->current < (plant_count - 1))
	{
		menu->current++;
	}
	else
	{
		menu->current = plant_feslegen;
	}
}
