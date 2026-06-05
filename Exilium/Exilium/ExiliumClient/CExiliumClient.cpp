#include "CExiliumClient.hpp"

#include <CS2/SDK/SDK.hpp>
#include <CS2/SDK/Interface/IEngineToClient.hpp>
#include <CS2/SDK/Interface/IGameEvent.hpp>
#include <CS2/SDK/Update/CCSGOInput.hpp>

#include <ExiliumClient/GUI/CExiliumMenu.hpp>
#include <ExiliumClient/CExiliumGUI.hpp>
#include <ExiliumClient/Fonts/CFontManager.hpp>
#include <ExiliumClient/Render/CRenderStackSystem.hpp>
#include <ExiliumClient/Features/CVisual/CVisual.hpp>
#include <ExiliumClient/Features/CInventoryChanger/CInventoryChanger.hpp>

#include <GameClient/CEntityCache/CEntityCache.hpp>

static CExiliumClient g_CExiliumClient{};

auto CExiliumClient::OnInit() -> void
{

}

auto CExiliumClient::OnFrameStageNotify( int FrameStage ) -> void
{
	GetInventoryChanger()->OnFrameStageNotify( FrameStage );
}

auto CExiliumClient::OnFireEventClientSide( IGameEvent* pGameEvent ) -> void
{
	GetInventoryChanger()->OnFireEventClientSide( pGameEvent );
}

auto CExiliumClient::OnAddEntity( CEntityInstance* pInst , CHandle handle ) -> void
{
	GetEntityCache()->OnAddEntity( pInst , handle );
}

auto CExiliumClient::OnRemoveEntity( CEntityInstance* pInst , CHandle handle ) -> void
{
	GetEntityCache()->OnRemoveEntity( pInst , handle );
}

auto CExiliumClient::OnRender() -> void
{
	if ( GetExiliumGUI()->IsVisible() )
		GetExiliumMenu()->OnRenderMenu();

	GetFontManager()->FirstInitFonts();
	GetFontManager()->m_VerdanaFont.DrawString( 1 , 1 , ImColor( 255 , 255 , 0 ) , FW1_LEFT , XorStr( CHEAT_NAME ) );

	if ( SDK::Interfaces::EngineToClient()->IsInGame() )
	{
		GetRenderStackSystem()->OnRenderStack();
	}
}

auto CExiliumClient::OnClientOutput() -> void
{
	if ( SDK::Interfaces::EngineToClient()->IsInGame() )
	{
		GetVisual()->OnClientOutput();
	}
}

auto CExiliumClient::OnCreateMove( CCSGOInput* pInput , CUserCmd* pUserCmd ) -> void
{
	GetVisual()->OnCreateMove();
}

auto GetExiliumClient() -> CExiliumClient*
{
	return &g_CExiliumClient;
}
