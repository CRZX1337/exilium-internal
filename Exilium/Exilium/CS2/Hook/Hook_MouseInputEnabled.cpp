#include "Hook_MouseInputEnabled.hpp"

#include <ExiliumClient/CExiliumGUI.hpp>

auto Hook_MouseInputEnabled( void* RCX ) -> bool
{
	if ( GetExiliumGUI()->IsVisible() )
		return false;

	return MouseInputEnabled_o( RCX );
}
