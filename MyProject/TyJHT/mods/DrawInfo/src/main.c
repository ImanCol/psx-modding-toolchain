#include <stdint.h>
#include "../../../include/common.h"
// Key memory addresses and function pointers

// Memory address that likely contains game state data
#define DAT_800c6178        ((volatile uint32_t*)0x800C6178)  

// BIOS printf function for debug output
#define BIOS_PRINTF         ((void(*)(const char*, ...))0x80018f30)

// Function to get any point in the game (possibly for navigation)
#define GET_ANYPOINT         ((void(*)(int))0x8001eccc)

// Memory address containing vehicle-related data
#define VEHICLE_DATA        ((volatile uint8_t*)0x8006B8F4) 

//define int CdGetSector(void *madr,int size) en la direccion 8001ab48
#define CdGetSector        ((int(*)(void*, int))0x8001ab48)
//define CdlFILE * CdSearchFile(CdlFILE *$30,char *name) en 8001c4d0
#define CdSearchFile       ((CdlFILE*(*)(CdlFILE* fp, char* name))0x8001c4d0)
//define int FUN_8001d400(unsigned int param_1,char param_2,uint32_t    param_3) en 8001d400
#define FUN_8001d400       ((int(*)(int,unsigned char, int))0x8001d400) // corrected 'unsigner' to 'unsigned'
//define uint FUN_8003f61c(char *param_1) en 8003f61c
#define FUN_8003f61c       ((uint32_t(*)(char*))0x8003f61c) // corrected 'unsigner' to 'unsigned'
//define void FUN_8001abcc(int param_1,char *param_2) en 8001abcc
#define FUN_8001abcc       ((void(*)(int,char*))0x8001abcc) // corrected 'unsigner' to 'unsigned'
//define unsigned int * FUN_800179a8(int param_1) en 800179a8
#define FUN_800179a8       ((unsigned int*(*)(int))0x800179a8) // added function pointer definition
//define int CdGetSector(void *madr,int size) en 8001ab48
#define CD_getsector        ((int(*)(void*, int))0x8001c1e0) // added function pointer definition
//define int FUN_80017b00(int param_1,int param_2,int param_3) en 80017b00
#define FUN_80017b00       ((int(*)(int,int,int))0x80017b00) // added function pointer definition

// Function pointer to change driver/character color
void (*const DriverColor)(uint32_t, uint32_t) = (void (*)(uint32_t, uint32_t))0x8001EF34;

// Function pointer declaration for point calculation (same as GET_ANYPOINT but different syntax)
uint32_t (*const FUN_8001eccc)(uint32_t) = (uint32_t (*)(uint32_t))0x8001ECCC;

// Function pointer for vertical sync operation
uint32_t (*const VSync)(uint32_t) = (uint32_t (*)(uint32_t))0x80054c4c;

// Initialization function for player setup
// player_param1: player-related parameter
// player_flags: flags for player configuration

//int Init(void *madr, uint8_t _size) {
CdlFILE *Init(CdlFILE *$30,char *name) {}

CdlFILE *hook_CdSearchFile(CdlFILE *result,char *name) {
    // TODO:
    //BIOS_PRINTF("Bot %d: Índice inválido 0x%02X\n", i+1, vehicle_index);
    //BIOS_PRINTF("Hola mundo!\n");
    //imprimir contenido de madr y _size en biod_printf
    //BIOS_PRINTF("Contenido de madr: %p, Tamaño: %d\n", madr, _size);
    //8002bf94 size 3
    //CdGetSector(madr, _size); // Call the function to get a sector from the CD
    //BIOS_PRINTF("Contenido de madr: %p, Tamaño: %d\n", fp, sizeof(fp) ); // Print the content of 'madr' and its size
    //Contenido de madr: 0x800354a0, Tamaño: 4
    //BIOS_PRINTF("Contenido de filename: %s\n", filename ? filename : "NULL"); // Print the filename or "NULL" if it's invalid
    //if (filename) {
        //CdSearchFile(fp, filename); // Call the function to search for a file on the CD
        //mostrar resultados de CdSearchFile
        //BIOS_PRINTF("Resultado de CdSearchFile: %p\n", fp); // Print the result of the file search
        //BIOS_PRINTF("Tamaño del archivo: %d\n", fp->size); // Print the size of the file found
        //BIOS_PRINTF("Posición del archivo: %d:%d:%d:%d\n", fp->pos.track, fp->pos.minute, fp->pos.second, fp->pos.sector); // Print the position of the file found
    //}
    //return fp;
    //return valor?
    
//cambiar el nombre del archivo a SYSTEM.CNF
    name = "\\RESOURCE.RES;1"; //manual File name to search for

    //ver contenido de CdlFILE
    BIOS_PRINTF("Contenido de $30: %p\n", result); // Print the content of '$30' pointer
    BIOS_PRINTF("Contenido de name: %s\n", name ? name : "NULL"); // Print the filename or "NULL" if it's invalid

    // Call CdSearchFile and store result
    result = CdSearchFile(result, name);

    if (result) {
        BIOS_PRINTF("File found: %s\n", result->name);
        BIOS_PRINTF("name: %s\n", name);
        BIOS_PRINTF("File size: %d bytes\n", result->size);
        BIOS_PRINTF("Position - Track:%d Min:%d Sec:%d Sector:%d\n", 
            result->pos.track, result->pos.minute, 
            result->pos.second, result->pos.sector);
    } else {
        BIOS_PRINTF("File not found\n");
    }

    // Print position in integer format if file was found
    if (result) {
        int pos_int = ((result->pos.minute >> 4) * 10 + (result->pos.minute & 0xf)) * 0x3c +
                      ((result->pos.second >> 4) * 10 + (result->pos.second & 0xf)) * 0x4b +
                      ((result->pos.sector >> 4) * 10 + (result->pos.sector & 0xf)) - 0x96;
        BIOS_PRINTF("Position as integer: %d\n", pos_int);
    }
    
    return result;
}

//Carefull. Posible Overflow Memory is always is djjdjjjdjjj
int hook_8001d400(unsigned int param_1, unsigned char param_2, unsigned int param_3) // changed 'char' to 'unsigned char'
{
    //BIOS_PRINTF("hook_8001d400: param_1: %d, param_2: %d, param_3: %d\n", param_1, param_2, param_3);
    //BIOS_PRINTF("hook_8001d400: param_1: %d, param_2: %c, param_3: %d\n", param_1, (char)param_2, param_3);
    //return FUN_8001d400(param_1, param_2, 0x80);
    //return 0 < iVar2;

    int result = FUN_8001d400(param_1, param_2, param_3);

    //BIOS_PRINTF("hook_8001d400 result: %d\n", result);

    BIOS_PRINTF("Parameters received: param_1: %d, param_2: %d, param_3: %d\n", param_1, param_2, param_3);

    return result;
}



//char * strcpy(char *param_1,char *param_2) en 80018ea0
//#define strcpy ((char*(*)(char*, char*))0x80018ea0)
//int strcmp(char *param_1,char *param_2) en 80018e90
#define strcmp ((int(*)(char*, char*))0x80018e90)
//#include <sys/types.h>
//#include <libcd.h>
//#include <libspu.h>

typedef struct {
	char filename[32];
	uint32_t offset;
	uint32_t size;
} ResourceEntry;

/*
// Función para leer un archivo específico del Resource.res
int ReadResourceFile(const char* filename, void* buffer, int maxSize)
{
	CdlFILE file;
	
	// Buscar el archivo Resource.res
	if (!CdSearchFile(&file, "RESOURCE.RES")) {
		return -1;
	}
	
	// Leer la tabla de contenidos del Resource.res
	ResourceEntry* entries;
	int entryCount;
	
	// TODO: Primero deberías leer el header del Resource.res
	// para obtener la ubicación de las entradas y su cantidad
	
	// Buscar el archivo específico en las entradas
	for (int i = 0; i < entryCount; i++) {
		if (strcmp(entries[i].filename, filename) == 0) {
			// Posicionar el lector en el offset correcto
			CdControl(CdlSeekL, (u_char*)&entries[i].offset, 0);
			
			// Leer los datos
			return CdRead((entries[i].size + 2047) / 2048, 
						 (u_long*)buffer, 
						 CdlModeSpeed);
		}
	}
	
	return -1;
}

*/


/*
LEVEL_1: Mouse Cleaning
washline, washmach, ironbd, chorse, lbasket, living01, plant1, coftable, rug02, fire07, radiotab, telly,
biglamp, sofa, kitchn01, kitshelv, units01, swbin, tcupbord, frimain, hall01, coat, hallrug, phonetab,
grandclk, elefoot, dinroom, candle, dintable, vacuum, ddresser, ddresser

LEVEL_8: Pumping Iron
cot, truck, jackopen, dollshse, drawers, bedrm08, bed, rug01, rug01, bedsidet, bedsidet, dresser2,
wardrobe, lnding08, landrug, hall07, coat, phonetab, hallrug, grandclk, elefoot, dinroom, candle,
dintable, vacuum, ddresser, ddresser, washrm01, washmach, washline, ironbd, chorse, lbasket, living01,
plant1, coftable, rug02, fire07, radiotab, telly, biglamp, sofa, kitchn01, kitshelv, swbin, tcupbord,
units06, frimain, bathrm08, basin, toilet, bath


LEVEL_X: ALLROMS?
hook_8003f61c: param_1: nursery8
Function result: 193
hook_8003f61c: param_1: cot
Function result: 151
hook_8003f61c: param_1: truck
Function result: 225
hook_8003f61c: param_1: jackopen
Function result: 135
hook_8003f61c: param_1: dollshse
Function result: 149
hook_8003f61c: param_1: drawers
Function result: 150
hook_8003f61c: param_1: bedrm08
Function result: 172
hook_8003f61c: param_1: bed
Function result: 145
hook_8003f61c: param_1: rug01
Function result: 213
hook_8003f61c: param_1: rug01
Function result: 213
hook_8003f61c: param_1: bedsidet
Function result: 146
hook_8003f61c: param_1: bedsidet
Function result: 146
hook_8003f61c: param_1: dresser2
Function result: 162
hook_8003f61c: param_1: wardrobe
Function result: 199
hook_8003f61c: param_1: attic09
Function result: 166
hook_8003f61c: param_1: cobweb2
Function result: 224
hook_8003f61c: param_1: flplank2
Function result: 104
hook_8003f61c: param_1: flplank1
Function result: 103
hook_8003f61c: param_1: flplank3
Function result: 105
hook_8003f61c: param_1: crate
Function result: 200
hook_8003f61c: param_1: crate
Function result: 200
hook_8003f61c: param_1: trunkclo
Function result: 137
hook_8003f61c: param_1: lnding09
Function result: 190
hook_8003f61c: param_1: landrug
Function result: 216
hook_8003f61c: param_1: hall07
Function result: 180
hook_8003f61c: param_1: coat
Function result: 141
hook_8003f61c: param_1: phonetab
Function result: 116
hook_8003f61c: param_1: hallrug
Function result: 215
hook_8003f61c: param_1: grandclk
Function result: 142
hook_8003f61c: param_1: elefoot
Function result: 118
hook_8003f61c: param_1: dinroom
Function result: 173
hook_8003f61c: param_1: candle
Function result: 160
hook_8003f61c: param_1: dintable
Function result: 114
hook_8003f61c: param_1: vacuum
Function result: 143
hook_8003f61c: param_1: ddresser
Function result: 161
hook_8003f61c: param_1: ddresser
Function result: 161
hook_8003f61c: param_1: washrm01
Function result: 195
hook_8003f61c: param_1: washmach
Function result: 125
hook_8003f61c: param_1: washline
Function result: 220
hook_8003f61c: param_1: ironbd
Function result: 107
hook_8003f61c: param_1: chorse
Function result: 126
hook_8003f61c: param_1: lbasket
Function result: 127
hook_8003f61c: param_1: living01
Function result: 191
hook_8003f61c: param_1: plant1
Function result: 119
hook_8003f61c: param_1: coftable
Function result: 113
hook_8003f61c: param_1: rug02
Function result: 214
hook_8003f61c: param_1: radiotab
Function result: 207
hook_8003f61c: param_1: telly
Function result: 111
hook_8003f61c: param_1: fire07
Function result: 131
hook_8003f61c: param_1: biglamp
Function result: 152
hook_8003f61c: param_1: sofa
Function result: 110
hook_8003f61c: param_1: kitchn01
Function result: 183
hook_8003f61c: param_1: kitshelv
Function result: 124
hook_8003f61c: param_1: swbin
Function result: 132
hook_8003f61c: param_1: tcupbord
Function result: 122
hook_8003f61c: param_1: units06
Function result: 134
hook_8003f61c: param_1: frimain
Function result: 115
hook_8003f61c: param_1: bathrm08
Function result: 170
hook_8003f61c: param_1: toilet
Function result: 156
hook_8003f61c: param_1: basin
Function result: 155
hook_8003f61c: param_1: bath
Function result: 157

*/



int hook_800128cc(int param_1,int param_2,int param_3)
{
    //realiza un for de prueba (no alterar los valores originales) donde param_1 (index) de 0 a 238 en FUN_80017b00
    for (int i = 240; i < 500; i++) {
        // Aquí se puede realizar alguna operación con i si es necesario
        int test_result = FUN_80017b00(i, param_2, param_3);
        BIOS_PRINTF("Test result for index %d: %d\n", i, test_result);
    }



    BIOS_PRINTF("hook_800128cc: index: %d, param_2: %x, param_3: %d\n", param_1, param_2, param_3);
    int result = FUN_80017b00(param_1, param_2, param_3);
    BIOS_PRINTF("Result: %d\n", result);
    return result;
}

uint32_t hook_8003f544(char *param_1)
{


    //param_1 = "SOFA"; // Set the string to "candle"
    BIOS_PRINTF("hook_8003f61c: param_1: %s\n", param_1); // Print the content of 'param_1' string
    uint32_t result = FUN_8003f61c(param_1);
    BIOS_PRINTF("Function result: %d (0x%x)\n", result, result);
    return result;
}


//search sector from Resources.res ?
unsigned int * hook_80017b1c(int param_1)
{
    //param_1 = 237;
    BIOS_PRINTF("hook_80017b1c: param_1: %d\n", param_1);
    unsigned int *result = FUN_800179a8(param_1);
    BIOS_PRINTF("FUN_800179a8 result: %p\n", result);
    return result;
}

//param_1 = sector (Resources.res + 23 (offset)) ; param_2 = CdlLOC
void hook_80017b7c(int param_1 ,CdlLOC *param_2)
{
    //param_1 = 7390;
    //param_2 es cdloc insert .minute .second .sector .track
    //BIOS_PRINTF("hook_80017b7c: start Sector: %d, param_2: \nminute: %d, \nsecond: %d, \nsector: %d, \ntrack: %d\n", param_1, param_2->minute, param_2->second, param_2->sector, param_2->track); // Print the parameters received
    FUN_8001abcc(param_1,(char*)param_2); // Call the original function with the provided parameters
    //mostrar resultados de FUN_8001abcc
    BIOS_PRINTF("Resultado de hook_80017b7c: start sector %d\n", param_1); // Print the result of the function call
    //mostras info de param_2 (CdlLOC) .minute .second .sector .track
    //BIOS_PRINTF("Contenido de param_2: \nminute: %d, \nsecond: %d, \nsector: %d, \ntrack: %d\n", param_2->minute, param_2->second, param_2->sector, param_2->track); // Print the content of 'param_2' structure

}

//param_1 = end sector (Resources.res + 23 (offset)); param_2 = unknown (char*)
void hook_80017bfc(int param_1,char *param_2)
{
    //BIOS_PRINTF("hook_80017bfc: end Sector: %d, param_2: %p\n", param_1, param_2); // Print the parameters received
    FUN_8001abcc(param_1,param_2); // Call the original function with the provided parameters
    //resultado de FUN_8001abcc (param_1,param_2)
    BIOS_PRINTF("Resultado de hook_80017bfc: end sector %d\n", param_1); // Print the result of the function call

    //BIOS_PRINTF("Resultado de hook_80017bfc: param_1: %d param_2: %d\n", param_1, param_2); // Print the result of the function call
}

//CD_getsector
int hook_8001ab48(void *madr,int size)
{
    BIOS_PRINTF("hook_8001ab48: madr: %p, size: %d\n", madr, size); // Print the parameters received
    int result = CD_getsector(madr, size); // Call the original function with the provided parameters
    //resultado de CdGetSector
    BIOS_PRINTF("Resultado de CdGetSector: %d\n", result); // Print the result of the function call
    return result;
}

/*
hook_80017b7c: param_1: 263, param_2: 
minute: 0, 
second: 0, 
sector: 0, 
track: 0
Resultado de FUN_8001abcc: 263
Contenido de param_2: 
minute: 0, 
second: 5, 
sector: 56, 
track: 0

hook_80017b7c: param_1: 142, param_2: 
minute: 224, 
second: 81, 
sector: 0, 
track: 82
Resultado de FUN_8001abcc: 142
Contenido de param_2: 
minute: 0, 
second: 3, 
sector: 103, 
track: 82

LEVEL_1: Mouse Cleaning
hook_80017b7c: param_1: 3077, param_2: 
minute: 168, 
second: 213, 
sector: 1, 
track: 128
Resultado de FUN_8001abcc: 3077
Contenido de param_2: 
minute: 0, 
second: 67, 
sector: 2, 
track: 128

hook_80017b7c: param_1: 3079, param_2: 
minute: 0, 
second: 0, 
sector: 0, 
track: 0
Resultado de FUN_8001abcc: 3079
Contenido de param_2: 
minute: 0, 
second: 67, 
sector: 4, 
track: 0


Loading screen?
hook_80017b7c: param_1: 1915, param_2: 
minute: 0, 
second: 0, 
sector: 0, 
track: 0
Resultado de FUN_8001abcc: 1915
Contenido de param_2: 
minute: 0, 
second: 39, 
sector: 64, 
track: 0


CREDITS
hook_80017b7c: param_1: 7390, param_2: 
minute: 100, 
second: 246, 
sector: 31, 
track: 0
Resultado de FUN_8001abcc: 7390
Contenido de param_2: 
minute: 1, 
second: 64, 
sector: 64, 
track: 0





*/
