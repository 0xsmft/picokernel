#pragma once

#if !defined(NULL)
#define NULL 0
#endif

#if !defined(PC_ASM)
#define PC_ASM __asm__
#endif

#if !defined(PC_VOLATILE)
#define PC_VOLATILE __volatile__
#endif

#if !defined(PC_ASM_VOLATILE)
#define PC_ASM_VOLATILE PC_ASM PC_VOLATILE
#endif

#if !defined(PC_ATTR_INTERRUPT)
#define PC_ATTR_INTERRUPT __attribute__((interrupt))
#endif

#if !defined(PC_ATTR_PACKED)
#define PC_ATTR_PACKED __attribute__((packed))
#endif

#if !defined(PC_ATTR_ALIGN)
#define PC_ATTR_ALIGN(x) __attribute__((aligned(x)))
#endif
