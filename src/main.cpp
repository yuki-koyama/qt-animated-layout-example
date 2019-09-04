#include "custom-layout.hpp"
#include <QApplication>
#include <QLabel>
#include <QWidget>

class CustomWidget : public QWidget
{
public:
    CustomWidget() : QWidget(nullptr)
    {
        CustomLayout* layout = new CustomLayout();
        layout->addWidget(new QLabel("Hello World!"));

        this->setLayout(layout);
    }
};

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    CustomWidget widget;
    widget.show();

    return app.exec();
}
