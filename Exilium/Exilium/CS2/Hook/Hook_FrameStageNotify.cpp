#include "Hook_FrameStageNotify.hpp"

#include <ExiliumClient/CExiliumClient.hpp>

auto Hook_FrameStageNotify( CSource2Client* pCSource2Client , int FrameStage ) -> void
{
	GetExiliumClient()->OnFrameStageNotify( FrameStage );

	return FrameStageNotify_o( pCSource2Client , FrameStage );
}
