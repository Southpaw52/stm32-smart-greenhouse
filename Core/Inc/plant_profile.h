/*
 * plant_profile.h
 *
 *  Created on: 17 Mar 2026
 *      Author: bahti
 */

#ifndef INC_PLANT_PROFILE_H_
#define INC_PLANT_PROFILE_H_
#include <stdint.h>

typedef enum
{
	plant_feslegen = 0,
	plant_domates,
	plant_marul,
	plant_biber,
	plant_count
}plant_type_t;

typedef struct
{
	const char *name;

	uint8_t soil_moisture_low;
	uint8_t soil_moisture_high;

	float temp_low;
	float temp_high;

	uint8_t humidity_target; // şimdilik sadece bilgi
}plant_profile_t;

extern plant_profile_t plant_profiles[plant_count];

#endif /* INC_PLANT_PROFILE_H_ */
