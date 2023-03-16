#include "widget.h"
#include "ui_widget.h"
#include "ocr.h"

#include <highgui.h>
#include <cv.h>
#include <QTimer> //包含QTimer头文件


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setAutoFillBackground(true);      //这句要加上，否则可能显示不出背景图
    QPalette playpalette=this->palette();
    playpalette.setBrush(QPalette::Window,QBrush(QPixmap(":/background.jpg").scaled(this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    this->setPalette(playpalette);
    ui->title->setAttribute(Qt::WA_TranslucentBackground);


    InitCamara();
    connect(&timer,SIGNAL(timeout()),this,SLOT(ReadFarme()));
}


void Widget::InitCamara()  //这个函数属于Widget
{
    //打开摄像头
    //这句代码的意思是打开video4，括号中的參数仅仅要有:
    // 0 , -1, 202 但要依据你自己的情况改,实測204可以成功打开
    camera = cvCreateCameraCapture(204);
    timer.start(50);

}

// 设置APPID/AK/SK
std::string app_id = "18416581";
std::string api_key = "wXlkQlKGVrjOO8DFwoj2Sxzw";
std::string secret_key = "Vwfu2fy0p78gN6hMdfTCKkyOxau3RDq5";

aip::Ocr client(app_id, api_key, secret_key);



std::string GetPlateNumber(std::string PincturePath)
{
    Json::Value result;

    std::string image;
    aip::get_file_content(PincturePath.c_str(), &image);

    // 调用车牌识别
    result = client.license_plate(image, aip::null);

    // 如果有可选参数
    std::map<std::string, std::string> options;
    options["multi_detect"] = "true";

    // 带参数调用车牌识别
    result = client.license_plate(image, options);


    if(result["error_code"].isNull())
    {
          return (result["words_result"][0]["number"].asString() + ",欢迎光临.");
    }
    else
    {
     return ("识别失败");
    }
    return ("识别失败");
}



Widget::~Widget()
{
    delete ui;
}


void Widget::ReadFarme()

{

//从摄像头读取一张图片
//这个函数cvQueryFrame作用是从摄像头或者文件中抓取一帧
//参数为视频获取结构也就是我在初始化摄像头声明的CvCapture *camera;

frame = cvQueryFrame(camera);

//将图片格式转换成QImage格式，否则不能再lable上显示

imag = QImage((const uchar*)frame->imageData,

                                frame->width,

                                frame->height,

                                QImage::Format_RGB888).rgbSwapped();

                //用label显示一张图片
    ui->frame->setPixmap(QPixmap::fromImage(imag));
}





void Widget::on_identiyfBt_clicked()
{
    std::string PlateNumber ;

    int Ret;


    frame = cvQueryFrame(camera);


    //将图片格式转换成QImage格式，否则不能再lable上显示

    imag = QImage((const uchar*)frame->imageData,

    frame->width,

    frame->height,

    QImage::Format_RGB888).rgbSwapped();

    //用label显示一张图片

    ui->picture->setPixmap(QPixmap::fromImage(imag));



    //保存图片到本地

    imag.save("./PlateNumber.jpg", "JPG", 100);


    //把拍下来的照片传递给百度AI接口获取车牌号

    PlateNumber = GetPlateNumber("./PlateNumber.jpg");


    //把接口返回来的数据显示到屏幕上

    ui->recve->setText(QString::fromStdString(PlateNumber));
}
