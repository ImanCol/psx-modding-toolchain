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
    0x007F0001,  // 00: Naranja
    0x007F0012,  // 01: Verde
    0x007F0030,  // 02: Amarillo
    0x007F005d,  // 03: Cyan
    0x007F0081,  // 04: Azul
    0x007F00a0,  // 05: Naranja
    0x007F0001,  // 06: Verde claro
    0x007F0012,  // 07: Rosa
    0x007F0030,  // 08: Morado
    0x007F005d,  // 09: Azul claro
    0x007F0001,  // 0A: Verde oscuro
    0x007F0012,  // 0B: Amarillo oscuro
    0x007F0030,  // 0C: Amarillo claro
    0x007F005d,  // 0D: Turquesa
    0x007F0001,  // 0E: Lila
    0x007F0012,  // 0F: Azul marino
    0x007F0030,  // 10: Rojo oscuro
    0x007F005d   // 11: Verde lima
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

//Player1                   Player2
//801EF718=Wonderwogan     
//801E1640=Thunderbolt     801EE850
//801783e8=Dakota          801E1640
static int check = 0;

void Init(int player_param1, uint8_t player_flags) {

if (check == 1)
{
    return;
}
check = 1;
    //uint32_t player_unique_addr = FUN_8001eccc(DAT_800c6178[0x02]);
    //(DAT_800c6178)[0 + 0x28] = player_unique_addr;

    //0. Pintar Vehiculo Original (Player 1)
    //BIOS_PRINTF("Player %d: INfo (Addrs=0x%02X)\n", 1, player_param1);

    //DriverColor(player_unique_addr, player_flags);

    // 1. Obtener índices de bots (posiciones invertidas)
    uint8_t bot_indices[] = {
        VEHICLE_DATA[5],  // Bot 1 (originalmente posición 2)
        VEHICLE_DATA[4],  // Bot 2 (originalmente posición 3)
        VEHICLE_DATA[3],  // Bot 3 (originalmente posición 4)
        VEHICLE_DATA[2],   // Bot 4 (originalmente posición 5)
        VEHICLE_DATA[1],   // Bot 4 (originalmente posición 5)
        VEHICLE_DATA[0]   // Bot 4 (originalmente posición 5)
    };

    uint32_t vehicle_struct =0;

    // 2. Procesar cada bot
    for (int i = 0; i < 6; i++) {
        uint8_t vehicle_index = bot_indices[i];

        // Validar índice
        if (vehicle_index >= 18) {
            BIOS_PRINTF("Bot %d: Índice inválido 0x%02X\n", i+1, vehicle_index);
            continue;
        }
        // Asignar color + flag de bot (0x80000000)
        uint32_t color = COLOR_TABLE[i];

        // Obtener estructura del vehículo (offset fijo + índice)
        //uint32_t vehicle_struct = DAT_800c6178[vehicle_index];
        if(i==5)
        {
            //Solo aplicable al Player 1
        vehicle_struct = FUN_8001eccc(DAT_800c6178[vehicle_index]);
        (DAT_800c6178)[0 + 0x28] = vehicle_struct;
        BIOS_PRINTF("5| Bot %d: encontrada (idx=0x%02X)\n", i+1, vehicle_index);
        goto setColor;
        }
        else
        {
            //Player 2 y bots
            //aun falla pintando los mismos vehiculos del mismo color (a excepsion de player 1)
            vehicle_struct = (DAT_800c6178)[vehicle_index];
            color = color | 0x80000000;
            BIOS_PRINTF("4| Bot %d: encontrada (idx=0x%02X)\n", i+1, vehicle_index);
            goto setColor;
        }
        continue;

        setColor:
        if (vehicle_struct == 0) {
            BIOS_PRINTF("Bot %d: Estructura no encontrada (idx=0x%02X)\n", i+1, vehicle_index);
            continue;
        }

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