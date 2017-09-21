/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2017 Bruno Van de Velde (vdv_b@tgui.eu)
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


#ifndef TGUI_ANIMATION_HPP
#define TGUI_ANIMATION_HPP

#include <TGUI/Widget.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Type of animation to show/hide widget
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    enum class ShowAnimationType
    {
        Fade,          ///< Fade widget in or out
        Scale,         ///< Shrink to the center of the widget to hide or grow from its center to show
        SlideToRight,  ///< Slide to the right to hide or from left to show
        SlideToLeft,   ///< Slide to the left to hide or from right to show
        SlideToBottom, ///< Slide to the bottom to hide or from top to show
        SlideToTop,    ///< Slide to the top to hide or from bottom to show

        SlideFromLeft = SlideToRight, ///< Slide from left to show or to the right to hide
        SlideFromRight = SlideToLeft, ///< Slide from right to show or to the left to hide
        SlideFromTop = SlideToBottom, ///< Slide from top to show or to the bottom to hide
        SlideFromBottom = SlideToTop  ///< Slide from bottom to show or to the top to hide
    };

    namespace priv
    {
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        class TGUI_API Animation
        {
        public:
            enum class Type
            {
                None = 0,
                Move = 1,
                Resize = 2,
                Fade = 4
            };

            virtual ~Animation() = default;

            Type getType() const;

            virtual bool update(sf::Time elapsedTime) = 0;

            virtual void finish();

        protected:
            Type m_type = Type::None;
            Widget::Ptr m_widget;

            sf::Time m_totalDuration;
            sf::Time m_elapsedTime;

            std::function<void()> m_finishedCallback;
        };

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        class TGUI_API MoveAnimation : public Animation
        {
        public:
            MoveAnimation(Widget::Ptr widget, sf::Vector2f start, sf::Vector2f end, sf::Time duration, std::function<void()> finishedCallback = nullptr);

            bool update(sf::Time elapsedTime) override;

            void finish() override;

        private:
            sf::Vector2f m_startPos;
            sf::Vector2f m_endPos;
        };

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        class TGUI_API ResizeAnimation : public Animation
        {
        public:
            ResizeAnimation(Widget::Ptr widget, sf::Vector2f start, sf::Vector2f end, sf::Time duration, std::function<void()> finishedCallback = nullptr);

            bool update(sf::Time elapsedTime) override;

            void finish() override;

        private:
            sf::Vector2f m_startSize;
            sf::Vector2f m_endSize;
        };

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        class TGUI_API FadeAnimation : public Animation
        {
        public:
            FadeAnimation(Widget::Ptr widget, float start, float end, sf::Time duration, std::function<void()> finishedCallback = nullptr);

            bool update(sf::Time elapsedTime) override;

            void finish() override;

        private:
            float m_startOpacity;
            float m_endOpacity;
        };

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    } // namespace priv
} // namespace tgui

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_ANIMATION_HPP
