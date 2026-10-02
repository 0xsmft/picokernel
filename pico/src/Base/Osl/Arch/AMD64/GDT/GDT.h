#pragma once

#include "Std/Stdint.h"

struct GDTDescriptor
{
    // Size of the GDT - sizeof(GDT) - 1
    u16 Size = 0;

    // The address of the GDT
    u64 Offset = 0llu;
} PC_ATTR_PACKED;

struct GDTEntry
{
    u16 Limit0 = 0u;
    u16 Base0= 0u;
    
    u8 Base1= 0u;
    u8 AccessBytes= 0u;
    u8 Limit1Flags= 0u;
    u8 Base2= 0u;
} PC_ATTR_PACKED;

struct GDT
{
    GDTEntry Null;
    GDTEntry KernelCode;
    GDTEntry KernelDataSegment;
    GDTEntry UserNullSegment;
    GDTEntry UserCodeSegment;
    GDTEntry UserDataSegment;

} PC_ATTR_PACKED PC_ATTR_ALIGN( 0x1000 );


extern "C" void PcLoadGDT( GDTDescriptor* pDescriptor );

extern GDT g_GDT;
