#include "custom-layout.hpp"
#include <QWidget>
#include <cmath>

CustomLayout::CustomLayout() : m_elapsed_time(0.0), m_origin_time(std::chrono::system_clock::now()) {}

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
    const std::chrono::system_clock::time_point current_time = std::chrono::system_clock::now();
    const std::chrono::duration<double>         diff         = current_time - m_origin_time;

    m_elapsed_time = diff.count();

    QLayout::setGeometry(rect);

    constexpr int w = 100;
    constexpr int h = 100;

    for (QLayoutItem* item : m_items)
    {
        const QRect geom(rect.x(), rect.y() + 0.5 * (1.0 + std::sin(m_elapsed_time)) * rect.height() - h / 2, w, h);

        item->setGeometry(geom);
    }
}
