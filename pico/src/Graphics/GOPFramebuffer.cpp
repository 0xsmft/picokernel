#include "GOPFramebuffer.h"

GOPFramebuffer::GOPFramebuffer( size_t buffSize, u32* pBaseAddr, u32 w, u32 h, u32 pixelsPerScanline, u32 bpp ) 
    : m_BufferSize( buffSize ), m_pBaseAddress( pBaseAddr ), m_Width( w ), m_Height( h ), m_PixelsPerScanline( pixelsPerScanline ), m_BPP( bpp )
{
}

void GOPFramebuffer::Clear( u32 color ) 
{
    for( size_t y = 0; y < m_Height; ++y )
	{
		for( size_t x = 0; x < m_Width; ++x )
		{
			m_pBaseAddress[ y * m_PixelsPerScanline + x ] = color;
		}
	}

    m_CursorPosition = {};
}
