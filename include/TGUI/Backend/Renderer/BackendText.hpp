/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2021 Bruno Van de Velde (vdv_b@tgui.eu)
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


#ifndef TGUI_BACKEND_TEXT_HPP
#define TGUI_BACKEND_TEXT_HPP

#include <TGUI/Text.hpp>
#include <TGUI/Backend/Font/BackendFont.hpp>
#include <TGUI/Backend/Renderer/BackendTexture.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Base class for text implementations that depend on the backend
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API BackendText
    {
    public:

        /// Type of the data that is passed to BackendRenderTarget where the actual rendering happens
        using TextVertexData = std::vector<std::pair<std::shared_ptr<BackendTexture>, std::shared_ptr<std::vector<Vertex>>>>;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Virtual destructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ~BackendText() = default;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the size of the text
        /// @return Size of the bounding box around the text
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Vector2f getSize();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the text
        /// @param string  Text that should be displayed
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setString(const String& string);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the text
        /// @return The current text
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const String& getString() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the size of the characters
        /// @param characterSize  Maximum size available for characters above the baseline
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setCharacterSize(unsigned int characterSize);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the character size of the text
        /// @return The current text size
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getCharacterSize() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the color of the text
        /// @param color  Text color
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setFillColor(const Color& color);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the text fill color
        /// @return text color
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Color getFillColor() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the color of the text outline
        /// @param color  Outline color
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setOutlineColor(const Color& color);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the text outline color
        /// @return outline color
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Color getOutlineColor() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the thickness of the text outline
        /// @param thickness  Outline thickness
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setOutlineThickness(float thickness);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the text outline thickness
        /// @return text outline thickness
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        float getOutlineThickness() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the text style
        /// @param style  New text style
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setStyle(TextStyles style);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the style of the text
        /// @return The current text style
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TextStyles getStyle() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the font used by the text
        /// @param font  New text font
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setFont(const std::shared_ptr<BackendFont>& font);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the font of the text
        /// @return text font
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::shared_ptr<BackendFont> getFont() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the top-left position of the character at the provided index
        /// @param index  Index of the character for which the position should be returned
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Vector2f findCharacterPos(std::size_t index) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the information that is needed to render this text
        /// @return Data that contains the textures and vertices used by this text
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TextVertexData getVertexData();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Recreates all vertices if required
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateVertices();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Helper function used by updateVertices to add vertices for a glyph
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void addGlyphQuad(std::vector<Vertex>& vertices, Vector2f position, const Vertex::Color& color, const FontGlyph& glyph, float italicShear);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Helper function used by updateVertices to add vertices for a line
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void addLine(std::vector<Vertex>& vertices, float lineLength, float lineTop, const Vertex::Color& color, float offset, float thickness, float outlineThickness);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        std::shared_ptr<BackendFont> m_font;

        String m_string;
        unsigned int m_characterSize = getGlobalTextSize();
        Color m_fillColor;
        Color m_outlineColor;
        float m_outlineThickness = 0;
        TextStyles m_style = TextStyle::Regular;

        Vector2f m_size;
        std::shared_ptr<std::vector<Vertex>> m_vertices;
        std::shared_ptr<std::vector<Vertex>> m_outlineVertices;
        bool m_verticesNeedUpdate = true;
    };
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_BACKEND_TEXT_HPP
