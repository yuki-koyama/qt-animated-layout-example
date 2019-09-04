#include "animated-layout.hpp"
#include <QApplication>
#include <QKeyEvent>
#include <QLabel>
#include <QOpenGLWidget>
#include <QTimer>
#include <memory>

class CustomWidget : public QOpenGLWidget
{
public:
    CustomWidget() : QOpenGLWidget(nullptr)
    {
        animated_layout = new AnimatedLayout();

        QLabel* label_c = new QLabel("Press\nSpace Key!");
        label_c->setStyleSheet("background-color: rgba(64, 128, 128, 0.5);");
        label_c->setAlignment(Qt::AlignCenter);
        animated_layout->addWidget(label_c);

        QLabel* label_m = new QLabel("Press\nSpace Key!");
        label_m->setStyleSheet("background-color: rgba(128, 64, 128, 0.5);");
        label_m->setAlignment(Qt::AlignCenter);
        animated_layout->addWidget(label_m);

        QLabel* label_y = new QLabel("Press\nSpace Key!");
        label_y->setStyleSheet("background-color: rgba(128, 128, 64, 0.5);");
        label_y->setAlignment(Qt::AlignCenter);
        animated_layout->addWidget(label_y);

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
