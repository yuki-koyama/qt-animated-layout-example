#include "custom-layout.hpp"
#include <QWidget>

CustomLayout::~CustomLayout()
{
    QLayoutItem* item = takeAt(0);
    while (item != nullptr)
    {
        delete item;

        item = takeAt(0);
    }
}

void CustomLayout::addItem(QLayoutItem* item) { m_items.push_back(item); }

void CustomLayout::addWidget(QWidget* widget) { addItem(new QWidgetItem(widget)); }

int CustomLayout::count() const { return m_items.size(); }

QLayoutItem* CustomLayout::itemAt(int index) const
{
    return (index < 0 || index >= this->count()) ? nullptr : m_items[index];
}

QLayoutItem* CustomLayout::takeAt(int index)
{
    if (index < 0 || index >= this->count())
    {
        return nullptr;
    }

    QLayoutItem* item = m_items[index];

    m_items.erase(m_items.begin() + index);

    return item;
}

QSize CustomLayout::sizeHint() const { return QSize(600, 400); }

void CustomLayout::setGeometry(const QRect& rect)
{
    QLayout::setGeometry(rect);

    constexpr int w = 100;
    constexpr int h = 100;

    for (QLayoutItem* item : m_items)
    {
        const QRect geom(rect.x(), rect.y(), w, h);
        item->setGeometry(geom);
    }
}
