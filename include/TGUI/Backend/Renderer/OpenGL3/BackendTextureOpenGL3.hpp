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


#ifndef TGUI_BACKEND_TEXTURE_OPENGL3_HPP
#define TGUI_BACKEND_TEXTURE_OPENGL3_HPP

#include <TGUI/Backend/Renderer/BackendTexture.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Texture implementation that makes use of modern OpenGL
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API BackendTextureOpenGL3 : public BackendTexture
    {
    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Destructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ~BackendTextureOpenGL3() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Loads the texture from an array of 32-bits RGBA pixels, but don't take ownership of the pixels
        ///
        /// @param size   Width and height of the image to create
        /// @param pixels Pointer to array of size.x*size.y*4 bytes with RGBA pixels, or nullptr to create an empty texture
        /// @param smooth Should the smooth filter be enabled or not?
        ///
        /// @warning Unlike the load function, loadTextureOnly won't store the pixels and isTransparentPixel thus won't work
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool loadTextureOnly(Vector2u size, const std::uint8_t* pixels, bool smooth) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes whether the smooth filter is enabled or not
        ///
        /// @param smooth  True if smoothing should be enabled, false if it should be disabled
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSmooth(bool smooth) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the id of the OpenGL texture
        /// @return Texture id
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getInternalTexture() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        unsigned int m_textureId = 0;
    };
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_BACKEND_TEXTURE_OPENGL3_HPP
