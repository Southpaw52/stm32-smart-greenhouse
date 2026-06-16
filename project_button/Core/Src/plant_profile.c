/*
 * plant_profile.c
 *
 *  Created on: 17 Mar 2026
 *      Author: bahti
 */
#include "plant_profile.h"

plant_profile_t plant_profiles[plant_count] =
{
		[plant_feslegen] =
		{
				.name = "Feslegen",
				.soil_moisture_low = 37,
				.soil_moisture_high = 40,
				.temp_low = 24.5,
				.temp_high = 26.0,
				.humidity_target = 50
		},

		[plant_domates] =
		{
				.name = "Domates",
				.soil_moisture_low = 35,
				.soil_moisture_high = 45,
				.temp_low = 22.0,
				.temp_high = 28.0,
				.humidity_target = 60
		},

		[plant_marul] =
		{
				.name ="Marul",
				.soil_moisture_low = 40,
				.soil_moisture_high = 60,
				.temp_low = 16.0,
				.temp_high = 22.0,
				.humidity_target = 70
		},

		[plant_biber] =
		{
				.name ="Biber",
				.soil_moisture_low = 30,
				.soil_moisture_high = 45,
				.temp_low = 20.0,
				.temp_high = 28.0,
				.humidity_target = 55
		}
};
