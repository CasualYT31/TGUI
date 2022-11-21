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


#ifndef TGUI_BACKEND_GUI_HPP
#define TGUI_BACKEND_GUI_HPP


#include <TGUI/Container.hpp>
#include <TGUI/RelFloatRect.hpp>
#include <TGUI/Event.hpp>
#include <TGUI/Cursor.hpp>
#include <chrono>
#include <stack>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Base class for the Gui
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API BackendGui
    {
    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        BackendGui();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Deleted copy constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        BackendGui(const BackendGui& copy) = delete;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Deleted assignment operator overload
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        BackendGui& operator=(const BackendGui& right) = delete;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Virtual destructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ~BackendGui();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the part of the screen to which the gui will render in pixels
        ///
        /// @param viewport  Rect of the window to which the gui should draw
        ///
        /// Example code to render the gui on only the right side of an 800x600 window:
        /// @code
        /// gui.setAbsoluteViewport({400, 0, 400, 600});
        /// @endcode
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setAbsoluteViewport(const FloatRect& viewport);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the part of the screen to which the gui will render as a ratio relative to the window size
        ///
        /// @param viewport  Rect of the window to which the gui should draw, relative to the window size
        ///
        /// The default viewport is set to (0, 0, 1, 1) so that it fills the entire window.
        ///
        /// Example code to render the gui on only the right side of window:
        /// @code
        /// gui.setRelativeViewport({0.5f, 0, 0.5f, 1});
        /// @endcode
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setRelativeViewport(const FloatRect& viewport);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns to which part of the screen the gui will render
        /// @return Rect of the window to which the gui will draw
        ///
        /// By default the viewport will fill the entire screen.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        RelFloatRect getViewport() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the part of the gui that will be used to fill the viewport in pixels
        ///
        /// @param view  Rect of the gui that will be stretched to fill the viewport
        ///
        /// No stretching will occur when the view has the same size as the viewport (default).
        ///
        /// Example code to use the contents of the gui container from top-left (200,100) to bottom-right (600, 400) and stetch
        /// it to fill the viewport (which equals the entire window by default):
        /// @code
        /// gui.setAbsoluteView({200, 100, 400, 300});
        /// @endcode
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setAbsoluteView(const FloatRect& view);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the part of the gui that will be used to fill the viewport
        ///
        /// @param view  Rect of the gui that will be stretched to fill the viewport, relative to the viewport size
        ///
        /// The default view is (0, 0, 1, 1) so that no scaling happens even when the viewport is changed.
        ///
        /// Example code to zoom in on the gui and display everything at 2x the size:
        /// @code
        /// gui.setRelativeView({0, 0, 0.5f, 0.5f});
        /// @endcode
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setRelativeView(const FloatRect& view);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the part of the gui that will be used to fill the viewport
        /// @return
        ///
        /// By default the view will have the same size as the viewport.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        RelFloatRect getView() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Passes the event to the widgets
        ///
        /// @param event  The event that was polled from the window
        ///
        /// @return Has the event been consumed?
        ///         When this function returns false, then the event was ignored by all widgets.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool handleEvent(Event event);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief When the tab key usage is enabled, pressing tab will focus another widget
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTabKeyUsageEnabled(bool enabled);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the tab key usage is enabled (if so, pressing tab will focus another widget)
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool isTabKeyUsageEnabled() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Draws all the widgets that were added to the gui
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void draw();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the internal container of the Gui
        ///
        /// This could be useful when having a function that should accept both the gui and e.g. a child window as parameter.
        ///
        /// @warning Not all functions in the Container class make sense for the Gui (which is the reason that the Gui does not
        ///          inherit from Container), so calling some functions (e.g. setSize) on the container will have no effect.
        ///
        /// @return Reference to the internal Container class
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        RootContainer::Ptr getContainer() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the backend render target that is assigned to the gui
        ///
        /// @return Render target that was created when a window was passed to the gui, or nullptr if it hasn't been created yet
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::shared_ptr<BackendRenderTarget> getBackendRenderTarget() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the global font
        ///
        /// @param font  Font to use
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setFont(const Font& font);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the global font for this gui
        ///
        /// @return Font for widgets in the gui
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Font getFont() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns a list of all the widgets
        ///
        /// @return Vector of all widget pointers
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const std::vector<Widget::Ptr>& getWidgets() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Adds a widget to the container
        ///
        /// @param widgetPtr   Pointer to the widget you would like to add
        /// @param widgetName  If you want to access the widget later then you must do this with this name
        ///
        /// @warning The widget name should not contain whitespace
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void add(const Widget::Ptr& widgetPtr, const String& widgetName = "");


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns a pointer to an earlier created widget
        ///
        /// @param widgetName The name that was given to the widget when it was added to the container
        ///
        /// @return Pointer to the earlier created widget
        ///
        /// The gui will first search for widgets that are direct children of it, but when none of the child widgets match
        /// the given name, a recursive search will be performed.
        ///
        /// @warning This function will return nullptr when an unknown widget name was passed
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Widget::Ptr get(const String& widgetName) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns a pointer to an earlier created widget
        ///
        /// @param widgetName The name that was given to the widget when it was added to the container
        ///
        /// @return Pointer to the earlier created widget.
        ///         The pointer will already be casted to the desired type
        ///
        /// The gui will first search for widgets that are direct children of it, but when none of the child widgets match
        /// the given name, a recursive search will be performed.
        ///
        /// @warning This function will return nullptr when an unknown widget name was passed
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template <class T>
        typename T::Ptr get(const String& widgetName) const
        {
            return m_container->get<T>(widgetName);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes a single widget that was added to the container
        ///
        /// @param widget  Pointer to the widget to remove
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool remove(const Widget::Ptr& widget);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes all widgets that were added to the container
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void removeAllWidgets();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the child widget that is focused inside this container
        ///
        /// @return Focused child widget or nullptr if none of the widgets are currently focused
        ///
        /// If the focused widget is a container then a pointer to that container is returned. If you want to know which widget
        /// is focused inside that container (recursively) then you should use the getFocusedLeaf() function.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Widget::Ptr getFocusedChild() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the leaf child widget that is focused inside this container
        ///
        /// @return Focused leaf child widget or nullptr if none of the widgets are currently focused
        ///
        /// If the focused widget is a container then the getFocusedLeaf() is recursively called on that container. If you want
        /// to limit the search to only direct children of this container then you should use the getFocusedChild() function.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Widget::Ptr getFocusedLeaf() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the leaf child widget that is located at the given position
        ///
        /// @param pos  The location where the widget will be searched, relative to the gui view
        ///
        /// @return Widget at the queried position, or nullptr when there is no widget at that location
        ///
        /// @see getWidgetBelowMouseCursor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Widget::Ptr getWidgetAtPosition(Vector2f pos) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the leaf child widget below the mouse
        ///
        /// @param mousePos  Position of the mouse, in pixel coordinates, relative the the window
        ///
        /// @return Widget below the mouse, or nullptr when the mouse isn't on top of any widgets
        ///
        /// @see getWidgetAtPosition
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Widget::Ptr getWidgetBelowMouseCursor(Vector2i mousePos) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Focuses the next widget in the gui
        ///
        /// @param recursive  If the focused widget is a container, should the next widget inside it be focused instead of
        ///                   focusing the sibling of the container?
        ///
        /// @return Whether a new widget was focused
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool focusNextWidget(bool recursive = true);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Focuses the previous widget in the gui
        ///
        /// @param recursive  If the focused widget is a container, should the next widget inside it be focused instead of
        ///                   focusing the sibling of the container?
        ///
        /// @return Whether a new widget was focused
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool focusPreviousWidget(bool recursive = true);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Unfocus all the widgets
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void unfocusAllWidgets();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Places a widget before all other widgets, to the front of the z-order
        ///
        /// @param widget  The widget that should be moved to the front
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void moveWidgetToFront(const Widget::Ptr& widget);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Places a widget behind all other widgets, to the back of the z-order
        ///
        /// @param widget  The widget that should be moved to the back
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void moveWidgetToBack(const Widget::Ptr& widget);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Places a widget one step forward in the z-order
        ///
        /// @param widget  The widget that should be moved one step forward
        ///
        /// @return New index in the widgets list (one higher than the old index or the same if the widget was already in front),
        ///         or getWidgets().size() if the widget was never added to this container.
        ///
        /// @see moveWidgetToFront
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::size_t moveWidgetForward(const Widget::Ptr& widget);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Places a widget one step backward in the z-order
        ///
        /// @param widget  The widget that should be moved one step backward
        ///
        /// @return New index in the widgets list (one lower than the old index or the same if the widget was already at back),
        ///         or getWidgets().size() if the widget was never added to this container.
        ///
        /// @see moveWidgetToBack
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::size_t moveWidgetBackward(const Widget::Ptr& widget);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the index of a widget in this container
        ///
        /// Widgets are drawn in the order of the list, so overlapping widgets with a higher index will appear on top of others.
        ///
        /// @param widget  Widget that is to be moved to a different index
        /// @param index   New index of the widget, corresponding to the widget position after the widget has been moved
        ///
        /// @return True when the index was changed, false if widget wasn't found in the container or index was too high
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool setWidgetIndex(const Widget::Ptr& widget, std::size_t index);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the current index of a widget in this container
        ///
        /// @return Index of the widget, or -1 if the widget wasn't found in this container
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        int getWidgetIndex(const Widget::Ptr& widget) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the opacity of all widgets
        ///
        /// @param opacity  The opacity of the widgets. 0 means completely transparent, while 1 (default) means fully opaque
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setOpacity(float opacity);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the opacity of all the widgets
        ///
        /// @return The opacity of the widgets. 0 means completely transparent, while 1 (default) means fully opaque
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        float getOpacity() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the character size of all existing and future child widgets.
        ///
        /// @param size  The new text size
        ///
        /// The text size specified in this function overrides the global text size property. By default, the gui does not
        /// pass any text size to the widgets and the widgets will use the global text size as default value.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextSize(unsigned int size);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the character size for future child widgets (and for existing widgets where the size wasn't changed)
        ///
        /// @return The current text size or 0 when no size was explicitly set in this gui
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getTextSize() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Loads the child widgets from a text file
        ///
        /// @param filename  Filename of the widget file
        /// @param replaceExisting  Remove existing widgets first if there are any
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void loadWidgetsFromFile(const String& filename, bool replaceExisting = true);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Saves the child widgets to a text file
        ///
        /// @param filename  Filename of the widget file
        ///
        /// @throw Exception when file could not be opened for writing
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void saveWidgetsToFile(const String& filename);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Loads the child widgets from a string stream
        ///
        /// @param stream  stringstream that contains the widget file
        /// @param replaceExisting  Remove existing widgets first if there are any
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void loadWidgetsFromStream(std::stringstream& stream, bool replaceExisting = true);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Loads the child widgets from a string stream
        ///
        /// @param stream  stringstream that contains the widget file
        /// @param replaceExisting  Remove existing widgets first if there are any
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void loadWidgetsFromStream(std::stringstream&& stream, bool replaceExisting = true);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Saves this the child widgets to a text file
        ///
        /// @param stream  stringstream to which the widget file will be added
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void saveWidgetsToStream(std::stringstream& stream) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Overrides which cursor gets shown
        ///
        /// @param type  Which cursor to show
        ///
        /// @warning You must call restoreOverrideCursor() for every call to setOverrideCursor.
        ///
        /// Until restoreOverrideCursor is called, the cursor will no longer be changed by widgets.
        /// If setOverrideCursor is called multiple times, the cursors are stacked and calling restoreOverrideCursor will only
        /// pop the last added cursor from the stack.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setOverrideMouseCursor(Cursor::Type type);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Undoes the effect of the last call to setOverrideCursor
        ///
        /// This function has to be called for each call to setOverrideCursor. If the stack of overriden cursors becomes empty
        /// then widgets will be able to change the cursor again.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void restoreOverrideMouseCursor();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Function that is used by widgets to change the mouse cursor
        ///
        /// @param type  The requested cursor
        ///
        /// This function is used to change the mouse cursor when the mouse enters or leaves a widget.
        /// If you want to choose a cursor that doesn't get changed when moving the mouse then use setOverrideMouseCursor.
        /// If an override cursor is already set then this function won't be able to change the cursor. When all overrides are
        /// removed with restoreOverrideMouseCursor then the mouse cursor will be changed to what was last requested here.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void requestMouseCursor(Cursor::Type type);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets whether drawing the gui will automatically update the internal clock or whether the user does it manually
        ///
        /// @param drawUpdatesTime  True if gui.draw() updates the clock (default), false if gui.updateTime() has to be called
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setDrawingUpdatesTime(bool drawUpdatesTime);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Updates the internal clock (for timers, animations and blinking edit cursors)
        ///
        /// @return True if the the contents of the screen changed, false if nothing changed
        ///
        /// You do not need to call this function unless you set DrawingUpdatesTime to false (it is true by default).
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool updateTime();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /// @brief Updates the internal clock (for timers, animations and blinking edit cursors)
        ///
        /// This function should not be used directly, use the updateTime() function without arguments instead.
        /// @see updateTime()
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool updateTime(Duration elapsedTime);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /// @brief Converts the pixel coordinate to a position within the view
        /// @param x  X coordinate on the window
        /// @param y  Y coordinate on the window
        /// @return Transformed coordinate within the coordinate system that is used by the widgets
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Vector2f mapPixelToView(int x, int y) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Give the gui control over the main loop
        ///
        /// @param clearColor  background color of the window
        ///
        /// This function is only intended in cases where your program only needs to respond to gui events.
        /// For multimedia applications, games, or other programs where you want a high framerate or do a lot of processing
        /// in the main loop, you should use your own main loop.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mainLoop(Color clearColor = {240, 240, 240}) = 0;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Updates the view and changes the size of the root container when needed.
        // Derived classes should update m_framebufferSize in this function and then call this function from the base class.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void updateContainerSize();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    public:

        SignalFloatRect onViewChange = {"ViewChanged"}; //!< The view was changed. Optional parameter: new view rectangle


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        std::chrono::steady_clock::time_point m_lastUpdateTime;
        bool m_windowFocused = true;

        RootContainer::Ptr m_container = std::make_shared<RootContainer>();

        Widget::Ptr m_visibleToolTip = nullptr;
        Duration m_tooltipTime;
        bool m_tooltipPossible = false;
        Vector2f m_toolTipRelativePos;
        Vector2i m_lastMousePos;

        Vector2i m_framebufferSize;
        RelFloatRect m_viewport{RelativeValue{0}, RelativeValue{0}, RelativeValue{1}, RelativeValue{1}};
        RelFloatRect m_view{RelativeValue{0}, RelativeValue{0}, RelativeValue{1}, RelativeValue{1}};
        FloatRect m_lastView;

        bool m_drawUpdatesTime = true;
        bool m_tabKeyUsageEnabled = true;

        Cursor::Type m_requestedMouseCursor = Cursor::Type::Arrow;
        std::stack<Cursor::Type> m_overrideMouseCursors;

        std::shared_ptr<BackendRenderTarget> m_backendRenderTarget = nullptr;
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_BACKEND_GUI_HPP
