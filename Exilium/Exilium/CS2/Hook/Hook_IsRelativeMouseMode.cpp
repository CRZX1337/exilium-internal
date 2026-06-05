#include "Hook_IsRelativeMouseMode.hpp"

#include <ExiliumClient/CExiliumGUI.hpp>

auto Hook_IsRelativeMouseMode( CInputSystem* pInputSystem , bool Active ) -> void
{
	GetExiliumGUI()->m_bMainActive = Active;

	if ( GetExiliumGUI()->IsVisible() )
		return IsRelativeMouseMode_o( pInputSystem , false );

	return IsRelativeMouseMode_o( pInputSystem , Active );
}
