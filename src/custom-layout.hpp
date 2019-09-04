#ifndef custom_layout_hpp
#define custom_layout_hpp

#include <QLayout>

class CustomLayout : public QLayout
{
public:
    void         addItem(QLayoutItem* item) override {}
    int          count() const override { return 0; }
    QLayoutItem* itemAt(int index) const override { return nullptr; }
    QLayoutItem* takeAt(int index) override { return nullptr; }

    QSize sizeHint() const override { return QSize(); }
};

#endif /* custom_layout_hpp */
