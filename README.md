# qt-animated-layout-example

A custom animated layout example in Qt5

![screen capture](./docs/example.gif)

## Notes

- `AnimatedLayout::setGeometry(const QRect&)` manipulates positions of child widgets based on delta times.
- `AnimatedLayout::update()` should be called in a fixed frame rate by, for example, `QTimer`.
- `AnimatedLayout` can be used with either `QOpenGLWidget` or `QWidget`, but the performance seems to be different. For full screen use, `QOpenGLWidget` is probably more suitable.
