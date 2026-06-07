#pragma once

#include <Common/Common.hpp>
#include <ImGui/imgui.h>

namespace Settings
{
	namespace Aimbot
	{
		inline auto Active = false;
		inline auto Fov = 10;
		inline auto Smooth = 5.0f;
		inline auto Bone = 0;
		inline auto VisibleOnly = true;
		inline auto HoldMode = true;
	}
	namespace Trigger
	{
		inline auto Active = false;
		inline auto Delay = 50;
		inline auto PostDelay = 100;
		inline auto HeadOnly = true;
		inline auto VisibleOnly = true;
	}
	namespace RCS
	{
		inline auto Active = false;
		inline auto ScaleX = 50.0f;
		inline auto ScaleY = 50.0f;
		inline auto OnlyWhileShooting = true;
	}
	namespace Movement
	{
		inline auto Bhop = false;
		inline auto AutoStrafe = false;
		inline auto EdgeJump = false;
	}
	namespace Misc
	{
		inline auto NoFlash = false;
	}
	namespace Visual
	{
		inline auto Active = true;
		inline auto Team = true;
		inline auto Enemy = true;
		inline auto OnlyVisible = false;
		inline auto PlayerBox = true;
		inline auto BoneESP = true;
		inline auto BoneESPTeam = true;
		inline auto BoneESPEnemy = true;
		inline auto Glow = true;
		inline auto GlowTeam = true;
		inline auto GlowEnemy = true;
		inline auto HealthBar = true;
		inline auto NameESP = true;
		inline auto Distance = false;
		inline auto WeaponLabel = true;

		inline auto PlayerBoxType = 3;
	}
	namespace Menu
	{
		inline auto MenuAlpha = 200;
		inline auto MenuStyle = 0;
	}
	namespace Colors
	{
		namespace Visual
		{
			inline ImVec4 PlayerBoxTT = { 255.f / 255.f , 75.f / 255.f , 75.f / 255.f  , 1.f };
			inline ImVec4 PlayerBoxTT_Visible = { 0 , 1.f , 0.f , 1.f };
			inline ImVec4 PlayerBoxCT = { 65.f / 255.f , 200 / 255.f , 255.f / 255.f , 1.f };
			inline ImVec4 PlayerBoxCT_Visible = { 0 , 1.f , 0.f , 1.f };
			inline ImVec4 BoneESPTT = { 255.f / 255.f , 75.f / 255.f , 75.f / 255.f  , 1.f };
			inline ImVec4 BoneESPTT_Visible = { 0 , 1.f , 0.f , 1.f };
			inline ImVec4 BoneESPCT = { 65.f / 255.f , 200 / 255.f , 255.f / 255.f , 1.f };
			inline ImVec4 BoneESPCT_Visible = { 0 , 1.f , 0.f , 1.f };
			inline ImVec4 GlowTT = { 255.f / 255.f , 75.f / 255.f , 75.f / 255.f  , 1.f };
			inline ImVec4 GlowTT_Visible = { 0 , 1.f , 0.f , 1.f };
			inline ImVec4 GlowCT = { 65.f / 255.f , 200 / 255.f , 255.f / 255.f , 1.f };
			inline ImVec4 GlowCT_Visible = { 0 , 1.f , 0.f , 1.f };
		}
	}
}
