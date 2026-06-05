#include "CExiliumMenu.hpp"

#include <ImGui/imgui.h>

#include <ExiliumClient/Settings/Settings.hpp>
#include <ExiliumClient/CExiliumGUI.hpp>
#include <ExiliumClient/Features/CInventoryChanger/CInventoryItemsManager.hpp>

static CExiliumMenu g_CExiliumMenu{};

auto CExiliumMenu::OnRenderMenu() -> void
{
	const float MenuAlpha = static_cast<float>( Settings::Menu::MenuAlpha ) / 255.f;

	ImGui::PushStyleVar( ImGuiStyleVar_Alpha , MenuAlpha );
	ImGui::SetNextWindowSize( ImVec2( 500 , 500 ) , ImGuiCond_FirstUseEver );

	if ( ImGui::Begin( XorStr( CHEAT_NAME ) , 0 ) )
	{
		if ( ImGui::CollapsingHeader( XorStr( "Visuals" ) ) )
		{
			RenderCheckBox( XorStr( "Active" ) , XorStr( "##Visual.Active" ) , Settings::Visual::Active );
			RenderCheckBox( XorStr( "Team" ) , XorStr( "##Visual.Team" ) , Settings::Visual::Team );
			RenderCheckBox( XorStr( "Enemy" ) , XorStr( "##Visual.Enemy" ) , Settings::Visual::Enemy );
			RenderCheckBox( XorStr( "OnlyVisible" ) , XorStr( "##Visual.OnlyVisible" ) , Settings::Visual::OnlyVisible );

			RenderCheckBox( XorStr( "Player Box" ) , XorStr( "##Visual.PlayerBox" ) , Settings::Visual::PlayerBox );

			const char* PlayerBoxTypeItems[] = 
			{ 
				"Box" , "Outline Box" , "Coal Box" , "Outline Coal Box" 
			};

			RenderComboBox( XorStr( "PlayerBox Type" ) , XorStr( "##Visual.PlayerBoxType" ) , Settings::Visual::PlayerBoxType , PlayerBoxTypeItems , IM_ARRAYSIZE( PlayerBoxTypeItems ) );

			RenderCheckBox( XorStr( "Bone ESP" ) , XorStr( "##Visual.BoneESP" ) , Settings::Visual::BoneESP );
			if ( Settings::Visual::BoneESP )
			{
				ImGui::Indent();
				RenderCheckBox( XorStr( "  Bone ESP Team" ) , XorStr( "##Visual.BoneESPTeam" ) , Settings::Visual::BoneESPTeam );
				RenderCheckBox( XorStr( "  Bone ESP Enemy" ) , XorStr( "##Visual.BoneESPEnemy" ) , Settings::Visual::BoneESPEnemy );
				ImGui::Unindent();
			}

			RenderCheckBox( XorStr( "Glow" ) , XorStr( "##Visual.Glow" ) , Settings::Visual::Glow );
			if ( Settings::Visual::Glow )
			{
				ImGui::Indent();
				RenderCheckBox( XorStr( "  Glow Team" ) , XorStr( "##Visual.GlowTeam" ) , Settings::Visual::GlowTeam );
				RenderCheckBox( XorStr( "  Glow Enemy" ) , XorStr( "##Visual.GlowEnemy" ) , Settings::Visual::GlowEnemy );
				ImGui::Unindent();
			}
		}

		if ( ImGui::CollapsingHeader( XorStr( "Colors" ) ) )
		{
			RenderColorEdit( XorStr( "Player Box TT" ) , XorStr( "##Colors.Visual.PlayerBoxTT" ) , &Settings::Colors::Visual::PlayerBoxTT.x );
			RenderColorEdit( XorStr( "Player Box TT Visible" ) , XorStr( "##Colors.Visual.PlayerBoxTT_Visible" ) , &Settings::Colors::Visual::PlayerBoxTT_Visible.x );
			RenderColorEdit( XorStr( "Player Box CT" ) , XorStr( "##Colors.Visual.PlayerBoxCT" ) , &Settings::Colors::Visual::PlayerBoxCT.x );
			RenderColorEdit( XorStr( "Player Box CT Visible" ) , XorStr( "##Colors.Visual.PlayerBoxCT_Visible" ) , &Settings::Colors::Visual::PlayerBoxCT_Visible.x );

			RenderColorEdit( XorStr( "Bone ESP TT" ) , XorStr( "##Colors.Visual.BoneESPTT" ) , &Settings::Colors::Visual::BoneESPTT.x );
			RenderColorEdit( XorStr( "Bone ESP TT Visible" ) , XorStr( "##Colors.Visual.BoneESPTT_Visible" ) , &Settings::Colors::Visual::BoneESPTT_Visible.x );
			RenderColorEdit( XorStr( "Bone ESP CT" ) , XorStr( "##Colors.Visual.BoneESPCT" ) , &Settings::Colors::Visual::BoneESPCT.x );
			RenderColorEdit( XorStr( "Bone ESP CT Visible" ) , XorStr( "##Colors.Visual.BoneESPCT_Visible" ) , &Settings::Colors::Visual::BoneESPCT_Visible.x );

			RenderColorEdit( XorStr( "Glow TT" ) , XorStr( "##Colors.Visual.GlowTT" ) , &Settings::Colors::Visual::GlowTT.x );
			RenderColorEdit( XorStr( "Glow TT Visible" ) , XorStr( "##Colors.Visual.GlowTT_Visible" ) , &Settings::Colors::Visual::GlowTT_Visible.x );
			RenderColorEdit( XorStr( "Glow CT" ) , XorStr( "##Colors.Visual.GlowCT" ) , &Settings::Colors::Visual::GlowCT.x );
			RenderColorEdit( XorStr( "Glow CT Visible" ) , XorStr( "##Colors.Visual.GlowCT_Visible" ) , &Settings::Colors::Visual::GlowCT_Visible.x );
		}

		if ( ImGui::CollapsingHeader( XorStr( "Menu" ) ) )
		{
			RenderSliderInt( XorStr( "Menu Alpha" ) , XorStr( "##Menu.MenuAlpha" ) , Settings::Menu::MenuAlpha , 100 , 255 );

			const char* MenuStyleItems[] =
			{
				"Indigo" , "Vermillion" , "Classic Steam"
			};

			if ( RenderComboBox( XorStr( "Menu Style" ) , XorStr( "##Menu.MenuStyle" ) , Settings::Menu::MenuStyle , MenuStyleItems , IM_ARRAYSIZE( MenuStyleItems ) ) )
				GetExiliumGUI()->UpdateStyle();
		}

		if ( ImGui::CollapsingHeader( XorStr( "Inventory Changer" ) ) )
		{
			auto* pInventoryManager = GetInventoryItemsManager();
			auto& dumpedItems = pInventoryManager->GetDumpedItems();

			const char* CategoryItems[] = { "Weapons", "Knives", "Gloves", "Agents", "Music Kits" };
			ImGui::Combo( XorStr( "Category" ), &m_SelectedCategory, CategoryItems, IM_ARRAYSIZE( CategoryItems ) );

			CInventoryItemsManager::EDumpedItemType_t targetType = CInventoryItemsManager::DUMPED_ITEM_TYPE_NONE;
			if ( m_SelectedCategory == 0 ) targetType = CInventoryItemsManager::DUMPED_ITEM_TYPE_WEAPON;
			else if ( m_SelectedCategory == 1 ) targetType = CInventoryItemsManager::DUMPED_ITEM_TYPE_KNIFE;
			else if ( m_SelectedCategory == 2 ) targetType = CInventoryItemsManager::DUMPED_ITEM_TYPE_GLOVE;
			else if ( m_SelectedCategory == 3 ) targetType = CInventoryItemsManager::DUMPED_ITEM_TYPE_AGENT;
			else if ( m_SelectedCategory == 4 ) targetType = CInventoryItemsManager::DUMPED_ITEM_TYPE_MUSIC;

			// Filter items by selected category
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
							m_SelectedSkinIndex = 0; // Reset skin index when item changes
						}
						if ( is_selected )
							ImGui::SetItemDefaultFocus();
						ImGui::PopID();
					}
					ImGui::EndCombo();
				}

				// Skins
				if ( targetType == CInventoryItemsManager::DUMPED_ITEM_TYPE_AGENT || targetType == CInventoryItemsManager::DUMPED_ITEM_TYPE_MUSIC )
				{
					// Agents don't have skins in the same way, Music kits are handled differently
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

				// Additional options
				if ( targetType == CInventoryItemsManager::DUMPED_ITEM_TYPE_WEAPON || targetType == CInventoryItemsManager::DUMPED_ITEM_TYPE_KNIFE || targetType == CInventoryItemsManager::DUMPED_ITEM_TYPE_GLOVE )
				{
					ImGui::SliderFloat( XorStr( "Wear" ), &m_Wear, 0.0f, 1.0f, "%.5f" );
					ImGui::SliderInt( XorStr( "Seed" ), &m_Seed, 0, 1000 );
					ImGui::SliderInt( XorStr( "StatTrak" ), &m_StatTrak, -1, 999999, m_StatTrak == -1 ? "Off" : "%d" );
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
		if ( ImGui::CollapsingHeader( XorStr( "Inventory Manager" ) ) )
		{
			auto* pInventoryManager = GetInventoryItemsManager();
			auto& addedItems = pInventoryManager->GetAddedItems();

			if ( addedItems.empty() )
			{
				ImGui::Text( XorStr( "No items added to inventory yet." ) );
			}
			else
			{
				if ( ImGui::BeginTable( XorStr( "InventoryManagerTable" ), 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg ) )
				{
					ImGui::TableSetupColumn( XorStr( "ID" ), ImGuiTableColumnFlags_WidthFixed, 50.0f );
					ImGui::TableSetupColumn( XorStr( "Item" ), ImGuiTableColumnFlags_WidthStretch );
					ImGui::TableSetupColumn( XorStr( "Action" ), ImGuiTableColumnFlags_WidthFixed, 80.0f );
					ImGui::TableHeadersRow();

					// We need to store IDs to delete to avoid modifying map while iterating
					std::vector<uint64_t> idsToDelete;

					for ( auto& [id, addedItem] : addedItems )
					{
						ImGui::TableNextRow();
						ImGui::TableSetColumnIndex( 0 );
						ImGui::Text( "%llu", id );

						ImGui::TableSetColumnIndex( 1 );
						std::string fullItemName;
						
						// Get the base weapon name since addedItem doesn't store it if it's a skin
						std::string baseName = pInventoryManager->GetWeaponName( addedItem.m_DefIdx );
						
						if ( addedItem.m_ItemType == CInventoryItemsManager::DUMPED_ITEM_TYPE_AGENT || addedItem.m_ItemType == CInventoryItemsManager::DUMPED_ITEM_TYPE_MUSIC )
						{
							fullItemName = addedItem.m_DisplayName;
						}
						else
						{
							if ( baseName != "Unknown" )
								fullItemName = baseName + " | " + addedItem.m_DisplayName;
							else
								fullItemName = addedItem.m_DisplayName;
						}

						ImGui::Text( "%s", fullItemName.c_str() );

						ImGui::TableSetColumnIndex( 2 );
						ImGui::PushID( static_cast<int>( id ) );
						if ( ImGui::Button( XorStr( "Delete" ), ImVec2( -1, 0 ) ) )
						{
							idsToDelete.push_back( id );
						}
						ImGui::PopID();
					}

					ImGui::EndTable();

					// Delete items after iteration
					for ( uint64_t id : idsToDelete )
					{
						pInventoryManager->RemoveItemFromInventoryByID( id );
					}
				}
			}
		}
	}

	ImGui::End();

	ImGui::PopStyleVar();
}

auto CExiliumMenu::RenderCheckBox( const char* szTitle , const char* szStrID , bool& SettingsItem ) -> bool
{
	if ( szTitle )
	{
		ImGui::AlignTextToFramePadding();
		ImGui::Text( szTitle );
		ImGui::SameLine( ImGui::CalcTextSize( szTitle ).x + 10.f );
	}

	const auto LeftPadding = ImGui::GetStyle().FramePadding.x;

	ImGui::Dummy( ImVec2( ImGui::GetContentRegionAvail().x - 27.f - LeftPadding , 0.f ) );
	ImGui::SameLine();

	const auto Ret = ImGui::Checkbox( szStrID , &SettingsItem );

	return Ret;
}

auto CExiliumMenu::RenderComboBox( const char* szTitle , const char* szStrID , int& v , const char* Items[] , int ItemsCount ) -> bool
{
	if ( szTitle )
	{
		ImGui::AlignTextToFramePadding();
		ImGui::Text( szTitle );
	}

	ImGui::SameLine();

	ImGui::PushItemWidth( -1.f );
	const auto Ret = ImGui::Combo( szStrID , &v , Items , ItemsCount );
	ImGui::PopItemWidth();

	return Ret;
}

auto CExiliumMenu::RenderColorEdit( const char* szTitle , const char* szStrID , float* Color ) -> bool
{
	if ( szTitle )
	{
		ImGui::AlignTextToFramePadding();
		ImGui::Text( szTitle );
	}

	ImGui::SameLine();

	const auto Ret = ImGui::ColorEdit4( szStrID , Color );

	return Ret;
}

auto CExiliumMenu::RenderSliderInt( const char* szTitle , const char* szStrID , int& Value , int Min , int Max ) -> bool
{
	if ( szTitle )
	{
		ImGui::AlignTextToFramePadding();
		ImGui::Text( szTitle );
	}

	ImGui::SameLine();

	ImGui::PushItemWidth( -1.f );
	const auto Ret = ImGui::SliderInt( szStrID , &Value , Min , Max );
	ImGui::PopItemWidth();

	return Ret;
}

auto GetExiliumMenu() -> CExiliumMenu*
{
	return &g_CExiliumMenu;
}
