#pragma once

#include <cstdint>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <map>

#include <ImGui/imgui.h>
#include <ImGui/imgui_internal.h>

extern float accent_colour[4];

namespace custom {
    bool selected(const char* label, bool tab = false);
    void InitFonts();
    void BeginStyle();
    void EndStyle();
}
