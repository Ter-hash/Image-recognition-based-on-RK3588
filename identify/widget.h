#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer> //包含QTimer头文件
#include <highgui.h>
#include <cv.h>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    CvCapture *camera;//视频获取结构， 用来作为视频获取函数的一个参数
    void InitCamara();
    QTimer    timer; //声明QTimer对象
    IplImage  *frame; //申请IplImage类型指针，就是申请内存空间来存放每一帧图像
    QImage    imag; //声明QImage对象


private slots:
    void ReadFarme(); //声明槽函数

    void on_identiyfBt_clicked();
};

#endif // WIDGET_H
