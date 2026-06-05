#include "Hook_ResizeBuffers.hpp"

#include <ExiliumClient/CExiliumGUI.hpp>

auto Hook_ResizeBuffers( IDXGISwapChain* pSwapChain , UINT BufferCount , UINT Width , UINT Height , DXGI_FORMAT NewFormat , UINT SwapChainFlags ) -> HRESULT
{
	GetExiliumGUI()->OnResizeBuffers( pSwapChain );

	return ResizeBuffers_o( pSwapChain , BufferCount , Width , Height , NewFormat , SwapChainFlags );
}
