#include "GDT.h"

PC_ATTR_ALIGN(0x1000) GDT g_GDT = 
{
   	{ 0, 0, 0, 0x00, 0x00, 0 }, // Null
	{ 0, 0, 0, 0x9a, 0xa0, 0 }, // Krnl Code
	{ 0, 0, 0, 0x92, 0xa0, 0 }, // Krnl Data
	{ 0, 0, 0, 0x00, 0x00, 0 }, // User Null
	{ 0, 0, 0, 0xfa, 0xa0, 0 }, // User Code Segment
	{ 0, 0, 0, 0xf2, 0xa0, 0 }, // User Data Segment
};
