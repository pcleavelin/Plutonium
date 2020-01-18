#include <pu/ttf/ttf_FontManager.hpp>

namespace pu::ttf {

    static std::map<std::string, std::shared_ptr<Font>> g_font_table;

    Result LoadFont(const std::string &name, std::shared_ptr<Font> font) {
        PU_RESULT_UNLESS(sdl2::ttf::IsInitialized(), result::ResultTTFNotInitialized);

        auto f = g_font_table.find(name);
        if(f == g_font_table.end()) {
            g_font_table.insert(std::make_pair(name, font));
        }
        return Success;
    }

    Result LoadSystemSharedFont(const std::string &name) {
        auto font = NewInstance<Font>(20);
        auto rc = plInitialize();
        if(R_SUCCEEDED(rc)) {
            for(u32 i = 0; i < PlSharedFontType_Total; i++) {
                PlFontData data = {};
                rc = plGetSharedFontByType(&data, (PlSharedFontType)i);
                if(R_SUCCEEDED(rc)) {
                    font->LoadFromMemory(data.address, data.size);
                }
            }
            plExit();
        }
        if(R_SUCCEEDED(rc)) {
            return LoadFont(name, font);
        }
        return rc;
    }

    Result LoadExternalFont(const std::string &name, const std::string &path) {
        auto font = NewInstance<Font>(20);
        font->LoadFromFile(path);
        return LoadFont(name, font);
    }

    std::shared_ptr<Font> GetFontByName(const std::string &name, s32 size) {
        auto f = g_font_table.find(name);
        if(f != g_font_table.end()) {
            auto font = f->second;
            if(size >= 0) {
                font->SetSize((u32)size);
            }
            return font;
        } 
        return nullptr;
    }

    void RemoveFontByName(const std::string &name) {
        auto f = g_font_table.find(name);
        if(f != g_font_table.end()) {
            g_font_table.erase(name);
        } 
    }

}