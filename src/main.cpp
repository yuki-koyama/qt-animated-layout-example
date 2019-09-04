#include "animated-layout.hpp"
#include <QApplication>
#include <QLabel>
#include <QTimer>
#include <QWidget>
#include <memory>

class CustomWidget : public QWidget
{
public:
    CustomWidget() : QWidget(nullptr)
    {
        AnimatedLayout* layout = new AnimatedLayout();
        layout->addWidget(new QLabel("Hello World!"));

        this->setLayout(layout);

        m_timer = std::make_unique<QTimer>();
        m_timer->callOnTimeout([=]() { layout->update(); });
        m_timer->setInterval(1000 / 60);
        m_timer->start();
    }

private:
    std::unique_ptr<QTimer> m_timer;
};

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    CustomWidget widget;
    widget.show();

    return app.exec();
}
