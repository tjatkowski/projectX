#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <array>

#include "GuiEvents.hpp"

namespace px {
    
    class Container;

    class Widget :public sf::Drawable, public sf::Transformable
    {
	protected:
		using Callback_t = std::function<void(Widget*)>;
    public:
        Widget();
        virtual ~Widget(){}
        
        //range of relative offset coordiantes: 0-100 [%] of the parent container size
        void addRelativeOffset(sf::Vector2f offset);

        void setParent(Container* parent);

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

        void handleInput(const sf::Event& event);

        void bindCallback(GuiEvent event, Callback_t callback);

        virtual void updateOrigin(){};

    protected:
        std::array<Callback_t, GuiEvent::COUNT> callbacks;
		void invokeEvent(GuiEvent eventKey);
    
    private:
        virtual bool isMouseOver(sf::Vector2f mousePosition) { return false; }

        Container* parent;
    };

}