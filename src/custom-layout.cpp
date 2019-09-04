#include "custom-layout.hpp"

QLayoutItem* CustomLayout::itemAt(int index) const
{
    return (index < 0 || index >= this->count()) ? nullptr : m_items[index];
}

QLayoutItem* CustomLayout::takeAt(int index)
{
    QLayoutItem* item = m_items[index];

    m_items.erase(m_items.begin() + index);

    return item;
}
