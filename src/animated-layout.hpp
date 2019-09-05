#ifndef animated_layout_hpp
#define animated_layout_hpp

#include <Eigen/Core>
#include <QLayout>
#include <chrono>
#include <memory>
#include <vector>

class QTimer;

class AnimatedLayout : public QLayout
{
public:
    AnimatedLayout();
    ~AnimatedLayout();

    void         addItem(QLayoutItem* item) override;
    void         addWidget(QWidget* widget);
    int          count() const override;
    QLayoutItem* itemAt(int index) const override;
    QLayoutItem* takeAt(int index) override;

    QSize sizeHint() const override;
    void  setGeometry(const QRect& rect) override;

    void play();
    void stop();

    void setRandomTargetPositions();

private:
    struct ItemWrapper
    {
        QLayoutItem*    item;
        Eigen::Vector2d target_position;
        Eigen::Vector2d current_position;
    };

    std::vector<ItemWrapper> m_item_wrappers;

    double                                m_elapsed_time;
    std::chrono::system_clock::time_point m_previous_time;
    std::chrono::system_clock::time_point m_origin_time;

    std::unique_ptr<QTimer> m_timer;
};

#endif /* animated_layout_hpp */
