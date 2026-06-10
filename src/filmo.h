#ifndef filmo_h
#define filmo_h

 enum MCU_type : uint8_t {
    RP2XXX,
    ESP32,
    MSP430,
    none
};

static int mcuIs = MCU_type::none;

int freeRTOSused = 0;

#if defined(TARGET_RP2040) || defined(TARGET_RP2350)
mcuIs = MCU_type::RP2XXX;
freeRTOSused = 1;
#endif
#if defined(ESP_32)
mcuIs = MCU_type::ESP32;
freeRTOSused = 1;
#endif
#if defined(TI_MSP430)
mcuIs = MCU_type::MSP430;
freeRTOSused = 0;
#endif



#define _logic 'l'
#define _motor 'm'
#define _combo 'i'



#ifdef filmotype_motor 
#include "communication/commander_recognized.h"
#include "communication/commander.h"
#include "general/dial.h"
#endif

#ifdef filmotype_logic

#endif

#ifdef filmotype_physicalShutter
#endif

#ifdef filmotype_digitalShutter
#endif

#ifdef filmotype_encoder
#endif 

#ifdef filmotype_projectorRunner
#include "general/switch.h"
#include "general/dial.h"

#endif

#ifdef filmotype_projectorRelay
#include "general/switch.h"
#include "communication/wireless.h"
#endif


#endif
