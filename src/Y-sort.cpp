#include "Y-sort.hpp"
#include <algorithm>

void YSort::onDraw(sf::RenderTarget &target)
{
    std::sort(m_children.begin(), m_children.end(), YComparator);
}