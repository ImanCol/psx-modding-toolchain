#include <stdint.h>
#include "../../../include/common.h"

// Direcciones clave
#define DAT_800c6178        ((volatile uint32_t*)0x800C6178)  // Estructuras de vehículos //0x800C6178 = bot?
#define BIOS_PRINTF         ((void(*)(const char*, ...))0x8005f09c)
#define GET_ANYPOINT         ((void(*)(int))0x8001eccc)
#define VEHICLE_DATA        ((volatile uint8_t*)0x8006B8F4)    // Índices de vehículos
void (*const DriverColor)(uint32_t, uint32_t) = (void (*)(uint32_t, uint32_t))0x8001EF34;

// Declaración de la función FUN_8001eccc usando puntero (sin #define)
uint32_t (*const FUN_8001eccc)(uint32_t) = (uint32_t (*)(uint32_t))0x8001ECCC;
uint32_t (*const VSync)(uint32_t) = (uint32_t (*)(uint32_t))0x80054c4c;

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
    "WonderWogan", "Thunderbolt", "Dakota Stunt Cycle",         // 0x00-0x02
    "Samson Tow Truck", "Livingston Truck", "Xanadu RV",
    "Palomino XIII", "El Guerrero", "Blue Burro Bus",    // 0x07
    "Excelsior Stretch", "Tsunami", "Marathon",
    "Moon Trekker", "Grubb Dual Loader", "Chrono Stinger", // 0x0C-0x0D
    "Vertigo", "Goliath Halfttrack", "Wapiti 4WD"
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

// ===================================================
// 1. Variables para control de velocidad y color
// ===================================================
static uint8_t r = 0, g = 0;              // Componentes de color
static uint8_t color_speed = 1;            // Velocidad base (1-10)
static uint32_t frame_counter = 0;         // Contador de frames


// ===================================================
// 2. Función para ajustar la velocidad del efecto
// ===================================================
void SetColorSpeed(uint8_t speed) {
    color_speed = (speed == 0) ? 1 : (speed > 10) ? 10 : speed; // Rango 1-10
}


// ===================================================
// 3. Generar color con incrementos controlados por velocidad
// ===================================================
uint32_t get_dynamic_color() {
    // Aumentar componentes según la velocidad
    r = (r + color_speed * 1) % 0x90;  // Rojo: +1 por nivel de velocidad
    g = (g + color_speed * 2) % 0x90;  // Verde: +2 por nivel de velocidad
    
    return 0x00000000 | (r << 8) | g;   // Formato 0x007FRRGG
}



// Generador de números pseudoaleatorios (simple)
static uint32_t rand_seed = 1;

uint32_t simple_rand() {
    rand_seed = rand_seed * 1103515245 + 12345;
    return (rand_seed >> 16) & 0x7FFF; // Devuelve valor entre 0-32767
}


// Generar color aleatorio en formato 0x007FRRGG
uint32_t get_random_color() {
    uint8_t r = ((simple_rand() + color_speed * 1) % 0x90); // 0x00-0x7F (rojo)
    uint8_t g = ((simple_rand() + color_speed * 2) % 0x90); // 0x00-0x7F (verde)
    return 0x00000000 | (r << 8) | g;   // Formato: 0x007FRRGG
}


void Init(int player_param1, uint8_t player_flags) {
        // Generar color único para el bot


    // Configurar velocidad inicial
    SetColorSpeed(0);  // Velocidad media (5/10)

    
        frame_counter++;
    // Actualizar cada 3 frames para suavizar el efecto
    if (frame_counter % (11 - color_speed) == 0) {  // Velocidad 1=10 frames, 10=1 frame
    /*    uint32_t color = get_dynamic_color() | 0x80000000;  // Flag de bot
        
        // Aplicar a vehículo de prueba (índice 0x06)
        DriverColor(DAT_800c6178[0x06], 0x005f0001);
    */




//


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

    uint32_t vehicle_struct = 0;

    // 2. Procesar cada bot
    for (int i = 0; i < 6; i++) {
        uint8_t vehicle_index = bot_indices[i];
        BIOS_PRINTF("Bot %d: Índice 0x%02X\n", i+1, vehicle_index);

        // Validar índice
        if (vehicle_index >= 18) {
            //BIOS_PRINTF("Bot %d: Índice inválido 0x%02X\n", i+1, vehicle_index);
            continue;
        }
        // Asignar color + flag de bot (0x80000000)
        uint32_t color = get_random_color();  // Flag de bot



        // Obtener estructura del vehículo (offset fijo + índice)
        //uint32_t vehicle_struct = DAT_800c6178[vehicle_index];

        switch (i)
        {
        case 5:
        {
                 //Solo aplicable al Player 1
        //vehicle_struct = FUN_8001eccc(DAT_800c6178[vehicle_index]);
        //vehicle_struct = (DAT_800c6178)[0 + 0x28];
        vehicle_struct = (DAT_800c6178)[vehicle_index];
        //(DAT_800c6178)[0 + 0x28] = vehicle_struct;
        //BIOS_PRINTF("5| Bot %d: encontrada (idx=0x%02X)\n", i+1, vehicle_index);
        goto setColor;   
        }
        case 4:
        {            //Player 2 y bots
            //aun falla pintando los mismos vehiculos del mismo color (a excepsion de player 1)
            //vehicle_struct = (DAT_800c6178)[1 + 0x28];
            vehicle_struct = (DAT_800c6178)[vehicle_index];
            //color = color | 0x80000000;
            //BIOS_PRINTF("4| Bot %d: encontrada (idx=0x%02X)\n", i+1, vehicle_index);
            goto setColor;

        }
        default:
        {
    //Player 2 y bots
            //aun falla pintando los mismos vehiculos del mismo color (a excepsion de player 1)
            vehicle_struct = (DAT_800c6178)[vehicle_index];
            //color = color | 0x80000000;
            //BIOS_PRINTF("4| Bot %d: encontrada (idx=0x%02X)\n", i+1, vehicle_index);
            goto setColor;
        } 
    }

        continue;

        setColor:
        if (vehicle_struct == 0) {
            BIOS_PRINTF("Bot %d: Estructura no encontrada (idx=0x%02X)\n", i+1, vehicle_index);
            continue;
        }
         
        
        // Depuración detallada
        BIOS_PRINTF("Bot %d: %s (idx=0x%02X) -> Addrs=0x%08X -> Color=0x%08X\n", 
                   i+1, 
                   VEHICLE_NAMES[vehicle_index], 
                   vehicle_index, 
                   vehicle_struct,
                   color);

        DriverColor(vehicle_struct, color);
        
        
    }

    /*
     //int testing =  GET_ANYPOINT(0x0);
 uint32_t player_base = DAT_800c6178[VEHICLE_DATA[0]];  // Índice del jugador
 uint32_t player_unique_addr = FUN_8001eccc(player_base);
 (DAT_800c6178)[0 + 0x28] = player_unique_addr;
  BIOS_PRINTF("player_base %02X: INfo (player_unique_addr=0x%02X) compare player_param1=%02X\n", player_base, player_unique_addr,player_param1);
*/}
 return;
}