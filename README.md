# STM32 Smart Greenhouse

**Author: southpaw**

An STM32F407VG greenhouse prototype exploring environmental sensing,
plant-profile selection and an LCD user interface.

| Target | Sensor | User interface |
|---|---|---|
| STM32F407VG | BME280 over I2C | 16×2 I2C LCD and two buttons |

## Implemented in this source snapshot

- BME280 initialization and temperature, pressure and humidity compensation.
- Temperature refresh in the main application loop.
- Plant-profile selection using a button-driven menu.
- LCD display of the selected profile and integer temperature.
- A PD12 output controlled on a button event using the selected profile's
  temperature-limit constant.

The PD12 decision currently uses a profile constant, not measured temperature.
Automatic soil-based irrigation, servo ventilation and grow-light control are
future work; they are not implemented by this source snapshot.

## Architecture and source map

| Path under project_button/ | Responsibility |
|---|---|
| Core/Src/main.c | Initialization and application loop |
| Core/Src/bme_280.c | BME280 access and compensation |
| Core/Src/button.c | Active-low button debounce and press events |
| Core/Src/menu.c and plant_profile.c | Profile selection and profile data |
| Core/Src/lcd_display_2x16_i2c_driver.c | LCD interface |
| Drivers/ | HAL and CMSIS dependencies |

## Connections defined in code

| Function | MCU pins |
|---|---|
| BME280 I2C1 SCL / SDA | PB6 / PB7 |
| LCD I2C2 SCL / SDA | PB10 / PB11 |
| Next profile / select | PC6 / PA10, active low |
| Experimental digital output | PD12 |

Verify the actual board, voltage levels, external power stages and output
polarity before connecting actuators.

## Development setup

The source includes STM32CubeMX configuration, HAL/CMSIS, startup assembly
and linker scripts under [project_button](project_button).
Use the .ioc and supplied sources when restoring a compatible STM32 development
project. A portable, documented standalone build command is not yet included
in this published snapshot.

## Status and limitations

The loop uses blocking I2C calls, sensor polling, LCD delays and HAL_Delay(500).
It should not be described as a non-blocking scheduler.
Short button presses may be missed while the application is blocked.

No new tests, firmware builds or board checks were run for this documentation
update. Actuator safety and unattended greenhouse operation are not validated.

## Türkçe özet

STM32F407VG üzerinde BME280 ölçümü, bitki profili seçimi ve LCD gösterimi
içeren bir sera prototipi. Mevcut kodda otomatik sulama, servo havalandırma
ve LED iklim kontrolü tamamlanmış değildir. Belgelenen kapsam, depodaki
uygulamanın mevcut davranışına dayanır.

## Authorship and licensing

Application development and embedded integration: **southpaw**.
Vendor HAL/CMSIS notices remain applicable. A project-wide license has not
yet been selected.
