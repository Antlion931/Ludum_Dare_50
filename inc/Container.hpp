#pragma once
#include <SFML/Graphics.hpp>
#include "Node.hpp"

class Container : public Node {
    public:
        Container();

    protected:
        void onResize(Resolution resolution) override;
};