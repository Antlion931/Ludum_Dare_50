#include "Container.hpp"

void Container::onResize(Resolution resolution) {
    setScale(resolution.getVector2fScale());
}

Container::Container() {
    
}