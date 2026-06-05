#pragma once

#include <Common/Common.hpp>

#include <CS2/SDK/Types/CHandle.hpp>
#include <CS2/SDK/Math/Vector3.hpp>

class IGameEvent;
class CEntityInstance;
class CCSGOInput;
class CUserCmd;

class IExiliumClient
{
public:
	virtual void OnFrameStageNotify( int FrameStage ) = 0;
	virtual void OnFireEventClientSide( IGameEvent* pGameEvent ) = 0;
	virtual void OnAddEntity( CEntityInstance* pInst , CHandle handle ) = 0;
	virtual void OnRemoveEntity( CEntityInstance* pInst , CHandle handle ) = 0;
	virtual void OnRender() = 0;
	virtual void OnClientOutput() = 0;
	virtual void OnCreateMove( CCSGOInput* pInput , CUserCmd* pUserCmd ) = 0;
};

class CExiliumClient final : public IExiliumClient
{
public:
	auto OnInit() -> void;

public:
	virtual void OnFrameStageNotify( int FrameStage ) override;
	virtual void OnFireEventClientSide( IGameEvent* pGameEvent ) override;
	virtual void OnAddEntity( CEntityInstance* pInst , CHandle handle ) override;
	virtual void OnRemoveEntity( CEntityInstance* pInst , CHandle handle ) override;
	virtual void OnRender() override;
	virtual void OnClientOutput() override;
	virtual void OnCreateMove( CCSGOInput* pInput , CUserCmd* pUserCmd ) override;
};

auto GetExiliumClient() -> CExiliumClient*;
