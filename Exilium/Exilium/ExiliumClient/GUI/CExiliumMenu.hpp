#pragma once

#include <Common/Common.hpp>

class CExiliumMenu final
{
public:
	auto OnRenderMenu() -> void;

private:
	static bool toggled;
	static float open_alpha;
	int m_tab = 0;

private:
	int m_SelectedCategory = 0;
	int m_SelectedItemIndex = 0;
	int m_SelectedSkinIndex = 0;
	float m_Wear = 0.0f;
	int m_Seed = 0;
	int m_StatTrak = -1;
};

auto GetExiliumMenu() -> CExiliumMenu*;
