#ifndef animated_layout_hpp
#define animated_layout_hpp

#include <QLayout>
#include <chrono>
#include <vector>

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

private:
    std::vector<QLayoutItem*> m_items;

    double                                m_elapsed_time;
    std::chrono::system_clock::time_point m_origin_time;
};

#endif /* animated_layout_hpp */
