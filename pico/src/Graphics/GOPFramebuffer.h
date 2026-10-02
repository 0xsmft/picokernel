#pragma once

#include "Std/Maths.h"

class GOPFramebuffer
{
public:
    GOPFramebuffer( size_t buffSize, u32* pBaseAddr, u32 w, u32 h, u32 pixelsPerScanline, u32 bpp );
    ~GOPFramebuffer() = default;

    void Clear( u32 color = 0xFF000000 );

private:
	size_t m_BufferSize = 0llu;
	u32* m_pBaseAddress = nullptr;
	u32 m_Width = 0u;
	u32 m_Height = 0u;
	u32 m_PixelsPerScanline = 0u;
	u32 m_BPP = 0u;

    IVec2 m_CursorPosition{};
};

extern GOPFramebuffer* g_pGlobalBasicFramebuffer;
