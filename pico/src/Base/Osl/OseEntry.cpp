#include <Limine/Limine.h>

#include "Base/KernelBoot/EntryKernelStatics.h"

#include "Graphics/GOPFramebuffer.h"

__attribute__( ( used, section( ".limine_requests" ) ) )
static volatile u64 LimineBaseRevision[] = LIMINE_BASE_REVISION( 4 );

__attribute__( ( used, section( ".limine_requests_start" ) ) )
static volatile u64 LimineRequestsStartMarker[] = LIMINE_REQUESTS_START_MARKER;

__attribute__( ( used, section( ".limine_requests" ) ) )
static volatile struct limine_framebuffer_request FramebufferRequest =
{
	.id = LIMINE_FRAMEBUFFER_REQUEST_ID,
	.revision = 0
};

__attribute__( ( used, section( ".limine_requests" ) ) )
static volatile limine_rsdp_request RSDPRequest =
{
	.id = LIMINE_RSDP_REQUEST_ID,
	.revision = 0
};

__attribute__( ( used, section( ".limine_requests" ) ) )
static volatile limine_memmap_request MemmapRequest =
{
	.id = LIMINE_MEMMAP_REQUEST_ID,
	.revision = 0
};

__attribute__( ( used, section( ".limine_requests" ) ) )
static volatile limine_hhdm_request HHDDMRequest =
{
	.id = LIMINE_HHDM_REQUEST_ID,
	.revision = 0
};

__attribute__( ( used, section( ".limine_requests" ) ) )
static volatile limine_module_request ModuleRequest = 
{
	.id = LIMINE_MODULE_REQUEST_ID,
	.revision = 0
};

__attribute__( ( used, section( ".limine_requests" ) ) )
static volatile limine_executable_address_request KernelAddressRequest =
{
	.id = LIMINE_EXECUTABLE_ADDRESS_REQUEST_ID,
	.revision = 0
};

__attribute__( ( used, section( ".limine_requests_end" ) ) )
static volatile u64 LimineRequestsEndMarker[] = LIMINE_REQUESTS_END_MARKER;

static void OslHcf()
{
	for( ;; )
	{
		asm volatile( "hlt" );
	}
}

extern "C" void OseSystemStartup() 
{
	if( LIMINE_BASE_REVISION_SUPPORTED( LimineBaseRevision ) == false )
	{
		OslHcf();
	}

	// Ensure we got a framebuffer.
	if( FramebufferRequest.response == nullptr || FramebufferRequest.response->framebuffer_count < 1 )
	{
		OslHcf();
	}

	struct limine_framebuffer* pFramebuffer = FramebufferRequest.response->framebuffers[ 0 ];

	GOPFramebuffer fb( pFramebuffer->width * pFramebuffer->height, ( u32* ) pFramebuffer->address, pFramebuffer->width, pFramebuffer->height, pFramebuffer->pitch / ( pFramebuffer->bpp / 8 ), pFramebuffer->bpp );
	KEntryKernelStatics::Boot( fb );
}
