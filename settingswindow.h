#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QFont>
#include <QList>
#include <QTabWidget>
#include <QFontDatabase>
#include <QHBoxLayout>
#include <QColor>
#include <QMouseEvent>
#include <QGraphicsDropShadowEffect>

#include <iostream>
#include <string>

using namespace std;

namespace Ui {
class settingsWindow;
}

class settingsWindow : public QWidget
{
    Q_OBJECT

public:
    QPushButton * colorBtns[8];
    string * mainColorStr = nullptr;
    QColor * mainColor = nullptr;

    explicit settingsWindow(QWidget *parent = nullptr);
    ~settingsWindow();

    void init();
private slots:
    void slot_close() { this->close(); };
    void changeColor ();
private:
    Ui::settingsWindow *ui;

    void mouseMoveEvent (QMouseEvent * event);
    void mousePressEvent (QMouseEvent * event);

    void reloadStyles();
    string qcolorToStr (QColor color);

    QPoint lastMousePosition;
    bool moving;

    QWidget * titlebarWidget;
    QLabel * windowTitle;
    QPushButton * closeBtn;
    QPushButton * minimizeBtn;
    QTabWidget  * tabs;

    QColor colors[16];
};

#endif // SETTINGSWINDOW_H