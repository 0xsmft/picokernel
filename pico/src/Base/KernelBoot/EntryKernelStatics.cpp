#include "EntryKernelStatics.h"

#include "Base/Osl/Arch/AMD64/GDT/GDT.h"

void KEntryKernelStatics::Boot( GOPFramebuffer& rFramebuffer ) 
{
    GDTDescriptor gdtDescriptor;
    gdtDescriptor.Size = sizeof( GDT ) - 1;
    gdtDescriptor.Offset = ( u64 ) &g_GDT;

    PcLoadGDT( &gdtDescriptor );

    rFramebuffer.Clear( 0xFF0000FF );

    PC_ASM( "hlt" );
}
