#include <stdint.h>
#include "../../../include/common.h"

// Direcciones clave
#define DAT_800c6178        ((volatile uint32_t*)0x800C6178)  // Estructuras de vehículos
#define BIOS_PRINTF         ((void(*)(const char*, ...))0x8005f09c)
#define GET_ANYPOINT         ((void(*)(int))0x8001eccc)
#define VEHICLE_DATA        ((volatile uint8_t*)0x8006B8F4)    // Índices de vehículos


// Declaración de la función FUN_8001eccc usando puntero (sin #define)
uint32_t (*const FUN_8001eccc)(uint32_t) = (uint32_t (*)(uint32_t))0x8001ECCC;

// Tabla de colores para 18 vehículos (0x00-0x11)
const uint32_t COLOR_TABLE[18] = {
    0x007F000C,  // 00: Naranja
    0x007F001A,  // 01: Verde
    0x007F003F,  // 02: Amarillo
    0x007F0052,  // 03: Cyan
    0x007F006B,  // 04: Azul
    0x007F0025,  // 05: Naranja
    0x007F003A,  // 06: Verde claro
    0x007F004F,  // 07: Rosa
    0x007F005A,  // 08: Morado
    0x007F006F,  // 09: Azul claro
    0x007F001F,  // 0A: Verde oscuro
    0x007F002F,  // 0B: Amarillo oscuro
    0x007F003F,  // 0C: Amarillo claro
    0x007F004A,  // 0D: Turquesa
    0x007F005F,  // 0E: Lila
    0x007F006A,  // 0F: Azul marino
    0x007F0015,  // 10: Rojo oscuro
    0x007F002A   // 11: Verde lima
};

// Mapeo de índices a nombres de vehículos (para depuración)
const char* VEHICLE_NAMES[18] = {
    "Vehículo 00", "Jhon Torque", "Dakota",         // 0x00-0x02
    "Vehículo 03", "Vehículo 04", "Vehículo 05",
    "Vehículo 06", "El Guerrero", "Vehículo 08",    // 0x07
    "Vehículo 09", "Vehículo 0A", "Vehículo 0B",
    "Moon Trekker", "Gruv Dual Loader", "Vehículo 0E", // 0x0C-0x0D
    "Vehículo 0F", "Vehículo 10", "Vehículo 11"
};

/*
void DriverColor(uint32_t vehicle_struct, uint32_t color_flags) {
    ((void (*)(uint32_t, uint32_t))0x8001EF34)(vehicle_struct, color_flags);
}
*/

void Init(int player_param1, uint8_t player_flags) {



    //0. Pintar Vehiculo Original (Player 1)
    BIOS_PRINTF("Player %d: INfo (Addrs=0x%02X)\n", 1, player_param1);

    //DriverColor(player_param1, player_flags);

    // 1. Obtener índices de bots (posiciones invertidas)
    uint8_t bot_indices[] = {
        VEHICLE_DATA[5],  // Bot 1 (originalmente posición 2)
        VEHICLE_DATA[4],  // Bot 2 (originalmente posición 3)
        VEHICLE_DATA[3],  // Bot 3 (originalmente posición 4)
        VEHICLE_DATA[2]   // Bot 4 (originalmente posición 5)
    };

    // 2. Procesar cada bot
    for (int i = 0; i < 4; i++) {
        uint8_t vehicle_index = bot_indices[i];

        // Validar índice
        if (vehicle_index >= 18) {
            //BIOS_PRINTF("Bot %d: Índice inválido 0x%02X\n", i+1, vehicle_index);
            continue;
        }

        // Obtener estructura del vehículo (offset fijo + índice)
        uint32_t vehicle_struct = DAT_800c6178[vehicle_index];
        if (vehicle_struct == 0) {
            BIOS_PRINTF("Bot %d: Estructura no encontrada (idx=0x%02X)\n", i+1, vehicle_index);
            continue;
        }

        // Asignar color + flag de bot (0x80000000)
        uint32_t color = COLOR_TABLE[vehicle_index];
        DriverColor(vehicle_struct, color);
        
        // Depuración detallada
        
        BIOS_PRINTF("Bot %d: %s (idx=0x%02X) -> Addrs=0x%08X -> Color=0x%08X\n", 
                   i+1, 
                   VEHICLE_NAMES[vehicle_index], 
                   vehicle_index, 
                   vehicle_struct,
                   color);
        
    }


    /*
     //int testing =  GET_ANYPOINT(0x0);
 uint32_t player_base = DAT_800c6178[VEHICLE_DATA[0]];  // Índice del jugador
 uint32_t player_unique_addr = FUN_8001eccc(player_base);
 (DAT_800c6178)[0 + 0x28] = player_unique_addr;
  BIOS_PRINTF("player_base %02X: INfo (player_unique_addr=0x%02X) compare player_param1=%02X\n", player_base, player_unique_addr,player_param1);
*/
 return;
}