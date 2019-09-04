#include "animated-layout.hpp"
#include <QWidget>
#include <cmath>

AnimatedLayout::AnimatedLayout()
    : m_elapsed_time(0.0), m_previous_time(std::chrono::system_clock::now()),
      m_origin_time(std::chrono::system_clock::now())
{
}

AnimatedLayout::~AnimatedLayout()
{
    QLayoutItem* item = takeAt(0);
    while (item != nullptr)
    {
        delete item;

        item = takeAt(0);
    }
}

void AnimatedLayout::addItem(QLayoutItem* item) { m_item_wrappers.push_back({item, {300.0, 200.0}, {300.0, 300.0}}); }

void AnimatedLayout::addWidget(QWidget* widget) { addItem(new QWidgetItem(widget)); }

int AnimatedLayout::count() const { return m_item_wrappers.size(); }

QLayoutItem* AnimatedLayout::itemAt(int index) const
{
    return (index < 0 || index >= this->count()) ? nullptr : m_item_wrappers[index].item;
}

QLayoutItem* AnimatedLayout::takeAt(int index)
{
    if (index < 0 || index >= this->count())
    {
        return nullptr;
    }

    QLayoutItem* item = m_item_wrappers[index].item;

    m_item_wrappers.erase(m_item_wrappers.begin() + index);

    return item;
}

QSize AnimatedLayout::sizeHint() const { return QSize(600, 400); }

void AnimatedLayout::setGeometry(const QRect& rect)
{
    QLayout::setGeometry(rect);

    const std::chrono::system_clock::time_point current_time = std::chrono::system_clock::now();
    const std::chrono::duration<double>         elapsed_time = current_time - m_origin_time;
    const std::chrono::duration<double>         delta_time   = current_time - m_previous_time;

    m_elapsed_time  = elapsed_time.count();
    m_previous_time = current_time;

    constexpr int    w     = 100;
    constexpr int    h     = 100;
    constexpr double decay = 5.0;

    for (ItemWrapper& item_wrapper : m_item_wrappers)
    {
        const Eigen::Vector2d& target_position  = item_wrapper.target_position;
        const Eigen::Vector2d& current_position = item_wrapper.current_position;

        const Eigen::Vector2d new_position =
            target_position - (target_position - current_position) * std::exp(-decay * delta_time.count());

        const QRect geom(rect.x() - w / 2 + new_position(0), rect.y() - h / 2 + new_position(1), w, h);

        item_wrapper.item->setGeometry(geom);
        item_wrapper.current_position = new_position;
    }
}

void AnimatedLayout::setRandomTargetPositions()
{
    const auto random_position_generator = [](const int width, const int height) -> Eigen::Vector2d {
        return (0.5 * (Eigen::Array2d::Random() + Eigen::Array2d::Ones()) * Eigen::Array2d(width, height)).matrix();
    };

    for (ItemWrapper& item_wrapper : m_item_wrappers)
    {
        item_wrapper.target_position = random_position_generator(this->geometry().width(), this->geometry().height());
    }
}
