#include "custom-layout.hpp"

void CustomLayout::addItem(QLayoutItem* item) { m_items.push_back(item); }

int CustomLayout::count() const { return m_items.size(); }

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

QSize CustomLayout::sizeHint() const { return QSize(600, 400); }
