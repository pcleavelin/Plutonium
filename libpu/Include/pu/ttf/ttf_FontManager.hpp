
#pragma once
#include <pu/ttf/ttf_Font.hpp>

namespace pu::ttf {

    Result LoadFont(const std::string &name, std::shared_ptr<ttf::Font> font);
    Result LoadSystemSharedFont(const std::string &name);
    Result LoadExternalFont(const std::string &name, const std::string &path);
    std::shared_ptr<ttf::Font> GetFontByName(const std::string &name, s32 size = -1);
    void RemoveFontByName(const std::string &name);
    
}