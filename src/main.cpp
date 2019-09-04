#include <QApplication>
#include <QWidget>

class CustomWidget : public QWidget
{

};

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    CustomWidget widget;
    widget.show();

    return app.exec();
}
