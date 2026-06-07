#include "CExiliumMenu.hpp"

#include <ImGui/imgui.h>
#include <Common/Include/XorStr/XorStr.hpp>

#include <ExiliumClient/Settings/Settings.hpp>
#include <ExiliumClient/CExiliumGUI.hpp>
#include <ExiliumClient/Features/CInventoryChanger/CInventoryItemsManager.hpp>
#include <ExiliumClient/GUI/custom.h>
#include <ExiliumClient/GUI/globals.h>

static CExiliumMenu g_CExiliumMenu{};

bool CExiliumMenu::toggled = false;
float CExiliumMenu::open_alpha = 0.0f;

auto CExiliumMenu::OnRenderMenu() -> void
{
	// Handle INSERT key toggle
	if ( GetAsyncKeyState( VK_INSERT ) & 1 )
	{
		toggled = !toggled;
		ImGui::GetIO().MouseDrawCursor = toggled;
		ShowCursor( !toggled );
	}

	// Alpha animation
	open_alpha = ImClamp( open_alpha + 2.f * ImGui::GetIO().DeltaTime * ( toggled ? 1.5f : -1.5f ), 0.f, 1.f );

	if ( open_alpha <= 0.0f )
		return;

	ImGui::PushStyleVar( ImGuiStyleVar_Alpha, open_alpha );
	ImGui::SetNextWindowSize( ImVec2( 838, 535 ), ImGuiCond_Always );
	ImGui::SetNextWindowPos( ImVec2( 100, 100 ), ImGuiCond_FirstUseEver );

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground;

	if ( ImGui::Begin( XorStr( "##Exilium" ), nullptr, window_flags ) )
	{
		ImVec2 window_pos = ImGui::GetWindowPos();
		ImVec2 window_size = ImGui::GetWindowSize();
		ImDrawList* draw = ImGui::GetWindowDrawList();

		// Left panel background
		draw->AddRectFilled( window_pos, window_pos + ImVec2( 161, 535 ), IM_COL32( 32, 32, 32, 255 ), 10.0f, ImDrawFlags_RoundCornersTopLeft | ImDrawFlags_RoundCornersBottomLeft );
		draw->AddRect( window_pos, window_pos + ImVec2( 161, 535 ), IM_COL32( 50, 50, 50, 255 ), 10.0f, ImDrawFlags_RoundCornersTopLeft | ImDrawFlags_RoundCornersBottomLeft );

		// Right panel background
		draw->AddRectFilled( window_pos + ImVec2( 161, 0 ), window_pos + ImVec2( 838, 535 ), IM_COL32( 26, 26, 26, 255 ), 10.0f, ImDrawFlags_RoundCornersTopRight | ImDrawFlags_RoundCornersBottomRight );
		draw->AddRect( window_pos + ImVec2( 161, 0 ), window_pos + ImVec2( 838, 535 ), IM_COL32( 50, 50, 50, 255 ), 10.0f, ImDrawFlags_RoundCornersTopRight | ImDrawFlags_RoundCornersBottomRight );

		// Title
		draw->AddText( tab_title, 19.0f, window_pos + ImVec2( 20, 15 ), IM_COL32( 255, 255, 255, 255 ), XorStr( "EXILIUM" ) );

		// Bottom user box
		ImVec2 user_box_min = window_pos + ImVec2( 9, 486 );
		ImVec2 user_box_max = window_pos + ImVec2( 152, 523 );
		draw->AddRectFilled( user_box_min, user_box_max, IM_COL32( 41, 41, 41, 255 ), 5.0f );
		draw->AddRect( user_box_min, user_box_max, IM_COL32( 50, 50, 50, 255 ), 5.0f );
		draw->AddText( poppins, 14.0f, user_box_min + ImVec2( 10, 10 ), IM_COL32( 255, 255, 255, 255 ), XorStr( "Exilium User" ) );
		draw->AddText( poppins, 12.0f, user_box_min + ImVec2( 10, 28 ), IM_COL32( 105, 105, 105, 255 ), XorStr( "Lifetime" ) );

		// TABS - Left Panel
		ImGui::SetCursorPos( ImVec2( 13, 99 ) );
		if ( ImGui::Rendertab( XorStr( "r" ), XorStr( "Legit Bot" ), m_tab == 0 ) ) m_tab = 0;

		ImGui::SetCursorPos( ImVec2( 13, 137 ) );
		if ( ImGui::Rendertab( XorStr( "t" ), XorStr( "Triggerbot" ), m_tab == 1 ) ) m_tab = 1;

		ImGui::SetCursorPos( ImVec2( 13, 175 ) );
		if ( ImGui::Rendertab( XorStr( "a" ), XorStr( "RCS" ), m_tab == 2 ) ) m_tab = 2;

		ImGui::SetCursorPos( ImVec2( 13, 228 ) );
		if ( ImGui::Rendertab( XorStr( "x" ), XorStr( "Players" ), m_tab == 3 ) ) m_tab = 3;

		ImGui::SetCursorPos( ImVec2( 13, 266 ) );
		if ( ImGui::Rendertab( XorStr( "w" ), XorStr( "World" ), m_tab == 4 ) ) m_tab = 4;

		ImGui::SetCursorPos( ImVec2( 13, 328 ) );
		if ( ImGui::Rendertab( XorStr( "z" ), XorStr( "Movement" ), m_tab == 5 ) ) m_tab = 5;

		ImGui::SetCursorPos( ImVec2( 13, 366 ) );
		if ( ImGui::Rendertab( XorStr( "s" ), XorStr( "Inventory" ), m_tab == 6 ) ) m_tab = 6;

		ImGui::SetCursorPos( ImVec2( 13, 404 ) );
		if ( ImGui::Rendertab( XorStr( "c" ), XorStr( "Config" ), m_tab == 7 ) ) m_tab = 7;

		// Category labels
		draw->AddText( poppins, 17.0f, window_pos + ImVec2( 13, 81 ), IM_COL32( 105, 105, 105, 255 ), XorStr( "Aimbot" ) );
		draw->AddText( poppins, 17.0f, window_pos + ImVec2( 13, 213 ), IM_COL32( 105, 105, 105, 255 ), XorStr( "Visuals" ) );
		draw->AddText( poppins, 17.0f, window_pos + ImVec2( 13, 310 ), IM_COL32( 105, 105, 105, 255 ), XorStr( "Misc" ) );

		// TAB CONTENT - Right Panel
		switch ( m_tab )
		{
		case 0: // Legit Bot
		{
			ImGui::SetCursorPos( ImVec2( 169, 38 ) );
			ImGui::MenuChild( XorStr( "General" ), ImVec2( 320, 220 ) );
			ImGui::Checkbox( XorStr( "Legit Aimbot" ), &Settings::Aimbot::Active );
			ImGui::SliderInt( XorStr( "FOV" ), &Settings::Aimbot::Fov, 0, 30 );
			ImGui::SliderFloat( XorStr( "Smooth" ), &Settings::Aimbot::Smooth, 0.0f, 20.0f );
			const char* boneItems[] = { XorStr( "Head" ), XorStr( "Neck" ), XorStr( "Body" ) };
			ImGui::Combo( XorStr( "Bone" ), &Settings::Aimbot::Bone, boneItems, IM_ARRAYSIZE( boneItems ) );
			ImGui::Checkbox( XorStr( "Visible Only" ), &Settings::Aimbot::VisibleOnly );
			ImGui::EndChild();

			ImGui::SetCursorPos( ImVec2( 169, 300 ) );
			ImGui::MenuChild( XorStr( "Keys" ), ImVec2( 320, 100 ) );
			ImGui::Checkbox( XorStr( "Hold to Aim" ), &Settings::Aimbot::HoldMode );
			ImGui::EndChild();
			break;
		}

		case 1: // Triggerbot
		{
			ImGui::SetCursorPos( ImVec2( 169, 38 ) );
			ImGui::MenuChild( XorStr( "Triggerbot" ), ImVec2( 320, 220 ) );
			ImGui::Checkbox( XorStr( "Enable" ), &Settings::Trigger::Active );
			ImGui::SliderInt( XorStr( "Delay ms" ), &Settings::Trigger::Delay, 0, 500 );
			ImGui::SliderInt( XorStr( "Release ms" ), &Settings::Trigger::PostDelay, 0, 300 );
			ImGui::Checkbox( XorStr( "Head Only" ), &Settings::Trigger::HeadOnly );
			ImGui::Checkbox( XorStr( "Visible Only" ), &Settings::Trigger::VisibleOnly );
			ImGui::EndChild();
			break;
		}

		case 2: // RCS
		{
			ImGui::SetCursorPos( ImVec2( 169, 38 ) );
			ImGui::MenuChild( XorStr( "Recoil Control" ), ImVec2( 320, 180 ) );
			ImGui::Checkbox( XorStr( "Enable RCS" ), &Settings::RCS::Active );
			ImGui::SliderFloat( XorStr( "X Scale" ), &Settings::RCS::ScaleX, 0.0f, 100.0f );
			ImGui::SliderFloat( XorStr( "Y Scale" ), &Settings::RCS::ScaleY, 0.0f, 100.0f );
			ImGui::Checkbox( XorStr( "Only While Firing" ), &Settings::RCS::OnlyWhileShooting );
			ImGui::EndChild();
			break;
		}

		case 3: // Players (ESP)
		{
			ImGui::SetCursorPos( ImVec2( 169, 38 ) );
			ImGui::MenuChild( XorStr( "Player ESP" ), ImVec2( 320, 240 ) );
			ImGui::Checkbox( XorStr( "Active" ), &Settings::Visual::Active );
			ImGui::Checkbox( XorStr( "Enemy" ), &Settings::Visual::Enemy );
			ImGui::Checkbox( XorStr( "Team" ), &Settings::Visual::Team );
			ImGui::Checkbox( XorStr( "Visible Only" ), &Settings::Visual::OnlyVisible );
			ImGui::Checkbox( XorStr( "Player Box" ), &Settings::Visual::PlayerBox );
			const char* boxTypeItems[] = { XorStr( "Box" ), XorStr( "Outline Box" ), XorStr( "Coal Box" ), XorStr( "Outline Coal Box" ) };
			ImGui::Combo( XorStr( "Box Type" ), &Settings::Visual::PlayerBoxType, boxTypeItems, IM_ARRAYSIZE( boxTypeItems ) );
			ImGui::Checkbox( XorStr( "Bone ESP" ), &Settings::Visual::BoneESP );
			ImGui::Checkbox( XorStr( "Glow" ), &Settings::Visual::Glow );
			ImGui::EndChild();

			ImGui::SameLine();
			ImGui::SetCursorPos( ImVec2( 499, 38 ) );
			ImGui::MenuChild( XorStr( "ESP Extras" ), ImVec2( 320, 160 ) );
			ImGui::Checkbox( XorStr( "Health Bar" ), &Settings::Visual::HealthBar );
			ImGui::Checkbox( XorStr( "Name" ), &Settings::Visual::NameESP );
			ImGui::Checkbox( XorStr( "Distance" ), &Settings::Visual::Distance );
			ImGui::Checkbox( XorStr( "Weapon Label" ), &Settings::Visual::WeaponLabel );
			ImGui::EndChild();
			break;
		}

		case 4: // World
		{
			ImGui::SetCursorPos( ImVec2( 169, 38 ) );
			ImGui::MenuChild( XorStr( "Misc Visuals" ), ImVec2( 320, 140 ) );
			ImGui::Checkbox( XorStr( "No Flash" ), &Settings::Misc::NoFlash );
			ImGui::EndChild();
			break;
		}

		case 5: // Movement
		{
			ImGui::SetCursorPos( ImVec2( 169, 38 ) );
			ImGui::MenuChild( XorStr( "Movement" ), ImVec2( 320, 160 ) );
			ImGui::Checkbox( XorStr( "Bhop" ), &Settings::Movement::Bhop );
			ImGui::Checkbox( XorStr( "Auto Strafe" ), &Settings::Movement::AutoStrafe );
			ImGui::Checkbox( XorStr( "Edge Jump" ), &Settings::Movement::EdgeJump );
			ImGui::EndChild();
			break;
		}

		case 6: // Inventory Changer
		{
			ImGui::SetCursorPos( ImVec2( 169, 38 ) );
			ImGui::MenuChild( XorStr( "Inventory Changer" ), ImVec2( 650, 470 ) );
			{
				auto* pInventoryManager = GetInventoryItemsManager();
				auto& dumpedItems = pInventoryManager->GetDumpedItems();

				const char* CategoryItems[] = { XorStr( "Weapons" ), XorStr( "Knives" ), XorStr( "Gloves" ), XorStr( "Agents" ), XorStr( "Music Kits" ) };
				ImGui::Combo( XorStr( "Category" ), &m_SelectedCategory, CategoryItems, IM_ARRAYSIZE( CategoryItems ) );

				CInventoryItemsManager::EDumpedItemType_t targetType = CInventoryItemsManager::DUMPED_ITEM_TYPE_NONE;
				if ( m_SelectedCategory == 0 ) targetType = CInventoryItemsManager::DUMPED_ITEM_TYPE_WEAPON;
				else if ( m_SelectedCategory == 1 ) targetType = CInventoryItemsManager::DUMPED_ITEM_TYPE_KNIFE;
				else if ( m_SelectedCategory == 2 ) targetType = CInventoryItemsManager::DUMPED_ITEM_TYPE_GLOVE;
				else if ( m_SelectedCategory == 3 ) targetType = CInventoryItemsManager::DUMPED_ITEM_TYPE_AGENT;
				else if ( m_SelectedCategory == 4 ) targetType = CInventoryItemsManager::DUMPED_ITEM_TYPE_MUSIC;

				std::vector<CInventoryItemsManager::DumpedItem_t*> filteredItems;
				for ( auto& item : dumpedItems )
				{
					if ( item.m_ItemType == targetType )
						filteredItems.push_back( &item );
				}

				if ( !filteredItems.empty() )
				{
					if ( m_SelectedItemIndex >= filteredItems.size() )
						m_SelectedItemIndex = 0;

					auto* pSelectedItem = filteredItems[m_SelectedItemIndex];

					if ( ImGui::BeginCombo( XorStr( "Item" ), pSelectedItem->m_DisplayName.c_str() ) )
					{
						for ( size_t i = 0; i < filteredItems.size(); ++i )
						{
							ImGui::PushID( static_cast<int>( i ) );
							bool is_selected = ( m_SelectedItemIndex == i );
							if ( ImGui::Selectable( filteredItems[i]->m_DisplayName.c_str(), is_selected ) )
							{
								m_SelectedItemIndex = static_cast<int>( i );
								m_SelectedSkinIndex = 0;
							}
							if ( is_selected )
								ImGui::SetItemDefaultFocus();
							ImGui::PopID();
						}
						ImGui::EndCombo();
					}

					if ( targetType == CInventoryItemsManager::DUMPED_ITEM_TYPE_AGENT || targetType == CInventoryItemsManager::DUMPED_ITEM_TYPE_MUSIC )
					{
					}
					else
					{
						if ( pSelectedItem->m_DumpedSkins.size() > 0 )
						{
							if ( m_SelectedSkinIndex >= pSelectedItem->m_DumpedSkins.size() )
								m_SelectedSkinIndex = 0;

							auto& selectedSkin = pSelectedItem->m_DumpedSkins[m_SelectedSkinIndex];

							if ( ImGui::BeginCombo( XorStr( "Skin" ), selectedSkin.m_DisplayName.c_str() ) )
							{
								for ( size_t i = 0; i < pSelectedItem->m_DumpedSkins.size(); ++i )
								{
									ImGui::PushID( static_cast<int>( i ) );
									bool is_selected = ( m_SelectedSkinIndex == i );
									if ( ImGui::Selectable( pSelectedItem->m_DumpedSkins[i].m_DisplayName.c_str(), is_selected ) )
										m_SelectedSkinIndex = static_cast<int>( i );
									if ( is_selected )
										ImGui::SetItemDefaultFocus();
									ImGui::PopID();
								}
								ImGui::EndCombo();
							}
						}
					}

					if ( targetType == CInventoryItemsManager::DUMPED_ITEM_TYPE_WEAPON || targetType == CInventoryItemsManager::DUMPED_ITEM_TYPE_KNIFE || targetType == CInventoryItemsManager::DUMPED_ITEM_TYPE_GLOVE )
					{
						ImGui::SliderFloat( XorStr( "Wear" ), &m_Wear, 0.0f, 1.0f, XorStr( "%.5f" ) );
						ImGui::SliderInt( XorStr( "Seed" ), &m_Seed, 0, 1000 );
						ImGui::SliderInt( XorStr( "StatTrak" ), &m_StatTrak, -1, 999999, m_StatTrak == -1 ? XorStr( "Off" ) : XorStr( "%d" ) );
					}

					if ( ImGui::Button( XorStr( "Add Item" ), ImVec2( -1, 30 ) ) )
					{
						if ( targetType == CInventoryItemsManager::DUMPED_ITEM_TYPE_AGENT )
						{
							pInventoryManager->AddSelectedSkinToInventory( pSelectedItem->m_DefIdx, 0, 0.0f, false, 0, -1 );
						}
						else if ( targetType == CInventoryItemsManager::DUMPED_ITEM_TYPE_MUSIC )
						{
							if ( pSelectedItem->m_DumpedSkins.size() > 0 )
								pInventoryManager->AddMusicToInventory( pSelectedItem->m_DefIdx, pSelectedItem->m_DumpedSkins[m_SelectedSkinIndex].m_ID, false );
						}
						else
						{
							if ( pSelectedItem->m_DumpedSkins.size() > 0 )
								pInventoryManager->AddSelectedSkinToInventory( pSelectedItem->m_DefIdx, pSelectedItem->m_DumpedSkins[m_SelectedSkinIndex].m_ID, m_Wear, false, m_Seed, m_StatTrak );
						}
					}
				}
				else
				{
					ImGui::Text( XorStr( "No items found. Please join a game first to scan items." ) );
				}
			}
			ImGui::EndChild();
			break;
		}

		case 7: // Config
		{
			ImGui::SetCursorPos( ImVec2( 169, 38 ) );
			ImGui::MenuChild( XorStr( "Config" ), ImVec2( 650, 300 ) );
			ImGui::Text( XorStr( "Config system coming soon..." ) );
			ImGui::Button( XorStr( "Save Config" ), ImVec2( -1, 30 ) );
			ImGui::Button( XorStr( "Load Config" ), ImVec2( -1, 30 ) );
			ImGui::EndChild();
			break;
		}
		}
	}

	ImGui::End();

	ImGui::PopStyleVar();
}

auto GetExiliumMenu() -> CExiliumMenu*
{
	return &g_CExiliumMenu;
}
