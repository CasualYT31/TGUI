/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2022 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Backend/Window/Backend.hpp>
#include <TGUI/Loading/Theme.hpp>
#include <TGUI/Timer.hpp>
#include <TGUI/Font.hpp>
#include <TGUI/DefaultFont.hpp>
#include <TGUI/Backend/Font/BackendFontFactory.hpp>
#include <TGUI/Backend/Renderer/BackendRenderer.hpp>
#include <TGUI/Backend/Window/BackendGui.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    namespace
    {
        std::shared_ptr<Backend> globalBackend = nullptr;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool isBackendSet()
    {
        return (globalBackend != nullptr);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void setBackend(std::shared_ptr<Backend> backend)
    {
        TGUI_ASSERT(!backend || !globalBackend, "setBackend() was called with a backend while there already was a backend");

        // Do some cleanup when we destroy the backend
        if (!backend)
        {
            // Stop all timers (as they could contain resources that have to be destroyed before the main function exits)
            Timer::clearTimers();

            // Destroy the global font
            Font::setGlobalFont(nullptr);

            // Destroy the global theme
            Theme::setDefault(nullptr);
        }

        globalBackend = std::move(backend);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::shared_ptr<Backend> getBackend()
    {
        TGUI_ASSERT(globalBackend != nullptr, "getBackend() was called while there is no backend");
        return globalBackend;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Backend::setDestroyOnLastGuiDetatch(bool destroyOnDetatch)
    {
        m_destroyOnLastGuiDetatch = destroyOnDetatch;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Backend::attachGui(BackendGui* gui)
    {
        m_guis.insert(gui);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Backend::detatchGui(BackendGui* gui)
    {
        // Don't check if it existed, detach is called for every gui while attached is only called for properly initialized guis
        m_guis.erase(gui);

        if (m_destroyOnLastGuiDetatch && m_guis.empty())
            setBackend(nullptr);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Font Backend::createDefaultFont()
    {
        if (m_fontBackend)
            return {static_cast<const unsigned char*>(defaultFontBytes), sizeof(defaultFontBytes)};
        else
            return {};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Backend::setFontScale(float scale)
    {
        if (scale == m_fontScale)
            return;

        m_fontScale = scale;

        // Invalidate all font textures
        for (auto* font : m_registeredFonts)
            font->setFontScale(scale);

        // Update the size of all texts in all widgets
        for (auto& gui : m_guis)
        {
            for (auto& widget : gui->getWidgets())
                widget->updateTextSize();
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Backend::openVirtualKeyboard(const FloatRect&)
    {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Backend::closeVirtualKeyboard()
    {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Backend::setClipboard(const String& contents)
    {
        m_clipboardContents = contents;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    String Backend::getClipboard() const
    {
        return m_clipboardContents;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::unique_ptr<std::uint8_t[]> Backend::readFileFromAndroidAssets(const String&, std::size_t&) const
    {
        return nullptr;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::shared_ptr<BackendFont> Backend::createFont()
    {
        return getFontBackend()->createFont();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::shared_ptr<BackendText> Backend::createText()
    {
        return getRenderer()->createText();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::shared_ptr<BackendTexture> Backend::createTexture()
    {
        return getRenderer()->createTexture();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Backend::hasRenderer() const
    {
        return (m_renderer != nullptr);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::shared_ptr<BackendRenderer> Backend::getRenderer() const
    {
        TGUI_ASSERT(m_renderer != nullptr, "getRenderer() called on backend while no BackendRenderer was created yet. Has a window been attached to a gui object yet?");
        return m_renderer;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Backend::setRenderer(std::shared_ptr<BackendRenderer> renderer)
    {
        m_renderer = std::move(renderer);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Backend::hasFontBackend() const
    {
        return (m_fontBackend != nullptr);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::shared_ptr<BackendFontFactory> Backend::getFontBackend() const
    {
        TGUI_ASSERT(m_fontBackend != nullptr, "getFontBackend() called on backend while no BackendFont was created yet. Has a window been attached to a gui object yet?");
        return m_fontBackend;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Backend::setFontBackend(std::shared_ptr<BackendFontFactory> fontBackend)
    {
        m_fontBackend = std::move(fontBackend);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Backend::registerFont(BackendFont* font)
    {
        m_registeredFonts.insert(font);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Backend::unregisterFont(BackendFont* font)
    {
        m_registeredFonts.erase(font);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////