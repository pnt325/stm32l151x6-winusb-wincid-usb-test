#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include "main.h"
#include "app.h"

__packed typedef union
{
	uint8_t 		raw[224];

} IOS2DEV;
#define IOS2DEV_LEN (sizeof(IOS2DEV))

#endif //__STRUCTS_H__
