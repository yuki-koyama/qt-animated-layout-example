#include "animated-layout.hpp"
#include <QApplication>
#include <QKeyEvent>
#include <QLabel>
#include <QTimer>
#include <QWidget>
#include <memory>

class CustomWidget : public QWidget
{
public:
    CustomWidget() : QWidget(nullptr)
    {
        animated_layout = new AnimatedLayout();

        QLabel* label_green = new QLabel("Press\nSpace Key!");
        label_green->setStyleSheet("background-color: rgba(64, 128, 128, 0.5);");
        label_green->setAlignment(Qt::AlignCenter);
        animated_layout->addWidget(label_green);

        QLabel* label_purple = new QLabel("Press\nSpace Key!");
        label_purple->setStyleSheet("background-color: rgba(128, 64, 128, 0.5);");
        label_purple->setAlignment(Qt::AlignCenter);
        animated_layout->addWidget(label_purple);

        this->setLayout(animated_layout);

        m_timer = std::make_unique<QTimer>();
        m_timer->callOnTimeout([=]() { animated_layout->update(); });
        m_timer->setInterval(1000 / 60);
        m_timer->start();
    }

protected:
    void keyPressEvent(QKeyEvent* event) override
    {
        if (event->key() == Qt::Key_Space)
        {
            animated_layout->setRandomTargetPositions();
        }
    }

private:
    std::unique_ptr<QTimer> m_timer;
    AnimatedLayout*         animated_layout;
};

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    CustomWidget widget;
    widget.show();

    return app.exec();
}
