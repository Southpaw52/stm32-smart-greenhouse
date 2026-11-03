/*
 * menu.h
 *
 *  Created on: 22 Mar 2026
 *      Author: bahti
 */

#ifndef INC_MENU_H_
#define INC_MENU_H_
#include "plant_profile.h"

typedef struct
{
	plant_type_t current;
}menu_t;

void MENU_Init(menu_t *menu);
void MENU_Next(menu_t *menu);

#endif /* INC_MENU_H_ */
