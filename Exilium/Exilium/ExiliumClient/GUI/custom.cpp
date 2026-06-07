#include "custom.h"
#include "globals.h"
#include "bytearray.h"

#include <ImGui/imgui.h>

#pragma warning (disable : 4244) // O_o

ImFont* tab_title = nullptr;
ImFont* font_icon = nullptr;
ImFont* poppins = nullptr;

struct tab_anim
{
    float label_anim;
    float hovered_anim;
    float active_anim;
};

bool custom::selected(const char* label, bool tab)
{
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(label);
    const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
    ImVec2 pos = window->DC.CursorPos;

    const ImRect rect(pos, ImVec2(pos.x + label_size.x, pos.y + label_size.y));
    ImGui::ItemSize(ImVec4(rect.Min.x, rect.Min.y, rect.Max.x, rect.Max.y), style.FramePadding.y);
    if (!ImGui::ItemAdd(rect, id))
        return false;

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(rect, id, &hovered, &held, NULL);

    static std::map <ImGuiID, tab_anim> anim;
    auto it_anim = anim.find(id);
    if (it_anim == anim.end())
    {
        anim.insert({ id, {0.6f, 0.f, 0.f} });
        it_anim = anim.find(id);
    }

    it_anim->second.label_anim = ImLerp(it_anim->second.label_anim, tab ? 0.0f : 0.6f, 0.05f * (1.0f - ImGui::GetIO().DeltaTime));
    it_anim->second.hovered_anim = ImLerp(it_anim->second.hovered_anim, hovered ? 0.2f : 0.0f, 0.03f * (1.0f - ImGui::GetIO().DeltaTime));
    it_anim->second.active_anim = ImLerp(it_anim->second.active_anim, tab ? 1.0f : 0.0f, 0.08f * (1.0f - ImGui::GetIO().DeltaTime));

    window->DrawList->AddText(ImVec2((rect.Min.x + rect.Max.x) / 2.f - (label_size.x / 2.f), (rect.Min.y + rect.Max.y) / 2.f - (label_size.y / 2.f)), ImColor(1.0f, 1.0f, 1.0f, it_anim->second.label_anim + it_anim->second.hovered_anim), label);
    window->DrawList->AddText(ImVec2((rect.Min.x + rect.Max.x) / 2.f - (label_size.x / 2.f), (rect.Min.y + rect.Max.y) / 2.f - (label_size.y / 2.f)), ImColor(accent_colour[0], accent_colour[1], accent_colour[2], it_anim->second.active_anim), label);

    return pressed;
}

void custom::InitFonts()
{
    ImGuiIO& io = ImGui::GetIO();

    poppins = io.Fonts->AddFontFromMemoryTTF(poppin_font, sizeof(poppin_font), 14.0f);
    tab_title = io.Fonts->AddFontFromMemoryTTF(poppin_font, sizeof(poppin_font), 19.0f);
    font_icon = io.Fonts->AddFontFromMemoryTTF(icon_font, sizeof(icon_font), 16.0f);
}

static ImVec4 accent_lighter()
{
    ImVec4 c(accent_colour[0], accent_colour[1], accent_colour[2], accent_colour[3]);
    return ImVec4(
        ImMin(c.x * 1.3f, 1.0f),
        ImMin(c.y * 1.3f, 1.0f),
        ImMin(c.z * 1.3f, 1.0f),
        c.w
    );
}

static ImVec4 accent_darker()
{
    ImVec4 c(accent_colour[0], accent_colour[1], accent_colour[2], accent_colour[3]);
    return ImVec4(c.x * 0.7f, c.y * 0.7f, c.z * 0.7f, c.w);
}

void custom::BeginStyle()
{
    ImVec4 accent(accent_colour[0], accent_colour[1], accent_colour[2], accent_colour[3]);
    ImVec4 accent_hover = accent_lighter();
    ImVec4 accent_active = accent_darker();

    ImGui::PushStyleColor(ImGuiCol_Text,                ImVec4(0.87f, 0.86f, 0.87f, 1.00f));
    ImGui::PushStyleColor(ImGuiCol_TextDisabled,        ImVec4(0.33f, 0.33f, 0.33f, 1.00f));
    ImGui::PushStyleColor(ImGuiCol_WindowBg,            ImVec4(0.10f, 0.10f, 0.10f, 1.00f));
    ImGui::PushStyleColor(ImGuiCol_ChildBg,             ImVec4(0.10f, 0.10f, 0.10f, 1.00f));
    ImGui::PushStyleColor(ImGuiCol_PopupBg,             ImVec4(0.12f, 0.12f, 0.12f, 1.00f));
    ImGui::PushStyleColor(ImGuiCol_Border,              ImVec4(0.20f, 0.20f, 0.20f, 1.00f));
    ImGui::PushStyleColor(ImGuiCol_FrameBg,             ImVec4(0.16f, 0.16f, 0.16f, 1.00f));
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered,      ImVec4(0.20f, 0.20f, 0.20f, 1.00f));
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive,       ImVec4(0.24f, 0.24f, 0.24f, 1.00f));
    ImGui::PushStyleColor(ImGuiCol_CheckMark,           accent);
    ImGui::PushStyleColor(ImGuiCol_SliderGrab,          accent);
    ImGui::PushStyleColor(ImGuiCol_SliderGrabActive,    accent_hover);
    ImGui::PushStyleColor(ImGuiCol_Button,              ImVec4(0.16f, 0.16f, 0.16f, 1.00f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered,       accent_hover);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive,        accent_active);
    ImGui::PushStyleColor(ImGuiCol_Header,              accent);
    ImGui::PushStyleColor(ImGuiCol_HeaderHovered,       accent_hover);
    ImGui::PushStyleColor(ImGuiCol_HeaderActive,        accent_active);
    ImGui::PushStyleColor(ImGuiCol_ScrollbarBg,         ImVec4(0.00f, 0.00f, 0.00f, 0.00f));
    ImGui::PushStyleColor(ImGuiCol_ScrollbarGrab,       ImVec4(0.27f, 0.27f, 0.27f, 1.00f));
    ImGui::PushStyleColor(ImGuiCol_ScrollbarGrabHovered, ImVec4(0.33f, 0.33f, 0.33f, 1.00f));
    ImGui::PushStyleColor(ImGuiCol_ScrollbarGrabActive,  ImVec4(0.40f, 0.40f, 0.40f, 1.00f));

    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding,    3.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize,  1.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize,      6.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarSize,    8.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding,    4.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize,  1.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding,   4.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_PopupRounding,    4.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_PopupBorderSize,  1.0f);
}

void custom::EndStyle()
{
    ImGui::PopStyleVar(9);
    ImGui::PopStyleColor(22);
}

bool ImGui::Rendertab(const char* icon, const char* label, bool selected)
{
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiID id = window->GetID(icon);
    const ImVec2 pos = window->DC.CursorPos;
    const ImVec2 size(138.0f, 32.0f);
    const ImRect bb(pos, pos + size);

    ImGui::ItemSize(size);
    if (!ImGui::ItemAdd(bb, id))
        return false;

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held);

    if (hovered || held)
        ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);

    static std::map<ImGuiID, float> hover_anim;
    auto& ha = hover_anim[id];
    ha = ImClamp(ha + g.IO.DeltaTime * 4.0f * (hovered ? 1.0f : -1.0f), 0.0f, 1.0f);

    static std::map<ImGuiID, float> active_anim;
    auto& aa = active_anim[id];
    aa = ImClamp(aa + g.IO.DeltaTime * 6.0f * (selected ? 1.0f : -1.0f), 0.0f, 1.0f);

    ImDrawList* draw = ImGui::GetWindowDrawList();
    ImVec4 accent(accent_colour[0], accent_colour[1], accent_colour[2], accent_colour[3]);

    ImU32 bg = selected
        ? ImColor(41, 41, 41, 255)
        : ImColor(ImLerp(ImVec4(0.10f, 0.10f, 0.10f, 1.0f), ImVec4(0.14f, 0.14f, 0.14f, 1.0f), ha));
    draw->AddRectFilled(bb.Min, bb.Max, bg, 5.0f);

    float bar_w = aa * 2.0f;
    if (bar_w > 0.0f)
        draw->AddRectFilled(
            ImVec2(bb.Min.x, bb.Min.y + 5.0f),
            ImVec2(bb.Min.x + bar_w, bb.Max.y - 5.0f),
            ImColor(accent.x, accent.y, accent.z, aa), 1.0f);

    ImU32 icon_col = selected
        ? ImColor(accent.x, accent.y, accent.z, 1.0f)
        : ImColor(ImLerp(ImVec4(0.50f, 0.50f, 0.50f, 1.0f), ImVec4(0.80f, 0.80f, 0.80f, 1.0f), ha));
    draw->AddText(font_icon, 16.0f, ImVec2(bb.Min.x + 10.0f, bb.Min.y + 8.0f), icon_col, icon);

    ImU32 label_col = selected
        ? ImColor(1.0f, 1.0f, 1.0f, 1.0f)
        : ImColor(ImLerp(ImVec4(0.55f, 0.55f, 0.55f, 1.0f), ImVec4(0.85f, 0.85f, 0.85f, 1.0f), ha));
    draw->AddText(poppins, 13.0f, ImVec2(bb.Min.x + 36.0f, bb.Min.y + 8.0f), label_col, label);

    return pressed;
}
