#pragma once

#include <Common/Common.hpp>

class CExiliumMenu final
{
public:
	auto OnRenderMenu() -> void;

private:
	auto RenderCheckBox( const char* szTitle , const char* szStrID , bool& SettingsItem ) -> bool;
	auto RenderComboBox( const char* szTitle , const char* szStrID , int& v , const char* Items[] , int ItemsCount ) -> bool;
	auto RenderColorEdit( const char* szTitle , const char* szStrID , float* Color ) -> bool;
	auto RenderSliderInt( const char* szTitle , const char* szStrID , int& Value , int Min , int Max ) -> bool;

private:
	int m_SelectedCategory = 0;
	int m_SelectedItemIndex = 0;
	int m_SelectedSkinIndex = 0;
	float m_Wear = 0.0f;
	int m_Seed = 0;
	int m_StatTrak = -1;
};

auto GetExiliumMenu() -> CExiliumMenu*;
