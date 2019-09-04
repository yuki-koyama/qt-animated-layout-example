#ifndef custom_layout_hpp
#define custom_layout_hpp

#include <QLayout>
#include <vector>

class CustomLayout : public QLayout
{
public:
    void         addItem(QLayoutItem* item) override { m_items.push_back(item); }
    int          count() const override { return m_items.size(); }
    QLayoutItem* itemAt(int index) const override;
    QLayoutItem* takeAt(int index) override;

    QSize sizeHint() const override { return QSize(); }

private:
    std::vector<QLayoutItem*> m_items;
};

#endif /* custom_layout_hpp */
