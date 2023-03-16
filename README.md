基于瑞芯微RK3588开发板的车牌识别

环境：瑞芯微RK3588开发板（ARM64），Ubuntu22.04，QT5.7

项目背景：

## **一、移植依赖库libcurl，openssl和jsincpp库**  

### 1.1  openssl库简介  

​         OpenSSL 是一个安全套接字层密码库，囊括主要的密码算法、常用的密钥和证书封装管理功能及SSL协议，并提供丰富的应用程序供测试或其它目的使用。  

### 1.2 移植

#### 1.2.1 解压压缩包进进入解压后的目录  

tar -vxf openssl-1.0.2s.tar.gz 

cd openssl-1.0.2s

#### 1.2.2  配置编译参数  

 setarch i386 ./config no-asm shared --prefix=/usr/local/openssl/  

setarch i386：声明生成的是32位CPU，如果是64位CPU则去除该部分

 <!----prefix ：指定make install后生成目录的路径，不修改此项则默认为OPENSSLDIR目录(/usr/local/ssl)。-->

<!--shared ：生成动态连接库。-->

<!--no-asm： 是在交叉编译过程中不使用汇编代码代码加速编译过程，原因是它的汇编代码是对arm格式不支持的-->

#### 1.2.3  修改Makefile里面的编译器参数  

CC= arm-none-linux-gnueabi-gcc
AR= arm-none-linux-gnueabi-ar $(ARFLAGS) r

RANLIB= arm-none-linux-gnueabi-ranlib

NM= arm-none-linux-gnueabi-nm

####  1.2.4 编译并安装

make
make install
安装成功后可以看到在 /usr/local/目录下已经安装好了头文件和库文件

### 2.1 curl库简介  

​       curl主要功能就是用不同的协议连接和沟通不同的服务器，也就是相当封装了的sockPHP 支持libcurl（允许你用不同的协议连接和沟通不同的服务器）。 lcurl当前支持http, https, ftp, gopher, telnet, dict, file, 和ldap 协议。libcurl同样支持HTTPS证书授权，HTTP POST, HTTP PUT, FTP 上传（当然你也可以使用PHP的ftp扩展）, HTTP基本表单上传，代理，cookies,和用户认证。  

### 2.2 移植

#### 2.2.1 解压压缩包进进入解压后的目录  

tar -vxf curl-7.65.0.tar.gz 

cd curl-7.65.0

#### 2.2.2 配置编译参数  

./configure --prefix=/usr/local/curl/ --host=arm-none-linux-gnueabi CC=arm-none-linux-gnueabi-gcc CXX=arm-none-linux-gnueabi-g++ --with-ssl=/usr/local/openssl

<!----prefix=/usr/local/curl/  指定安装路径为/usr/local/curl/-->

<!----host 指定运行平台为arm-->

<!--CC和 CXX  指定交叉编译器-->

<!----with-ssl--> 

#### 2.2.3 编译安装

make
make install

### 3.1 jsoncpp库简介  

​        JSON全称为JavaScript ObjectNotation，它是一种轻量级的数据交换格式，易于阅读、编写、解析。jsoncpp是c++解析JSON串常用的解析库之一  

### 3.2 移植

#### 3.2.1 解压压缩包

tar -vxf jsoncpp-1.6.5.tar.gz
cd jsoncpp-1.6.5/

#### 3.2.2 编译

arm-none-linux-gnueabi-g++ -c *.cpp -I./include -fPIC

mkdir lib

ar cr ./lib/libjsoncpp.a *.o

arm-none-linux-gnueabi-g++ -shared -fPIC *.cpp -I./include -o ./lib/libjsoncpp.so

在 /usr/local/创建json文件夹，并把第5步的lib拷贝进去来和第4步arm_jsoncpp拷贝到json文件夹

## 二、编译Opencv

### 1.1 Opencv简介

OpenCV是一个跨平台的计算机视觉库，可以运行在Linux、Windows和Mac OS操作系统上，它轻量级而且高效 --由一系列C函数和少量C++类构成，同时也提供了Python接口，实现了图像处理和计算机视觉的很多通用算法。

### 1.2 编译

目标板：RK3588
PC：ubuntu20.04
opencv版本：4.7.0：https://opencv.org/releases/
编译工具链：gcc-arm-10.3-2021.07-x86_64-aarch64-none-linux-gnu：https://developer.arm.com/downloads/-/gnu-a

#### 1.2.1 安装gcc、g++

sudo apt install gcc g++

检查版本 gcc -v

#### 1.2.2 安装Cmake、make

sudo snap install cmake --classic

sudo apt install make

#### 1.2.3 解压Opencv和交叉编译器

unzip opencv-4.7.0zip

随后进入解压后的文件夹，并新建build与install目录。build用来存放cmake的中间文件，install用来存放安装文件，将来粘贴到板子上 

cd opencv-3.4.5
mkdir build
mkdir install

 同样，解压交叉编译工具链： 

tar -xvf gcc-arm-10.3-2021.07-x86_64-aarch64-none-linux-gnu.tar.xz

 之后将其bin子目录加入`.bashrc`: 

export PATH="/home/wjp/gcc-arm-10.3-2021.07-x86_64-aarch64-none-linux-gnu/bin:$PATH"

重新启动使环境变量生效

source ~/.bashrc

#### 1.2.4 开始编译

启动cmake-gui 进行编译

sudo cmake-gui

可以参考以下资料进行编译配置

https://www.ebaina.com/articles/140000013416
https://zhuanlan.zhihu.com/p/84839635
https://blog.csdn.net/xidaoliang/article/details/124730226?spm=1001.2014.3001.5502

#进入在opencv下创建好的build文件下

cd ......opencv/build

make -j20     // -j后面的参数代表进程数，为可选项，可以根据自己电脑的状态进行选择，理论上会提升编译的速度

遇到的问题

报错：#error “No suitable threading library available.” #error "No suitable threading library available.
解决：https://www.cnblogs.com/leoking01/p/16046212.html</u>
报错：undefined reference to ‘png_init_filter_functions_neon’
解决：修改3rdparty/libpng/pngpriv.h 

128： /*# if (defined(__ARM_NEON__) || defined(__ARM_NEON)) && \*/
129：if defined(PNG_ARM_NEON) && (defined(__ARM_NEON__) || defined(__ARM_NEON)) && \

编译成功后会在install文件中生成相关文件，直接把install文件复制在板子上就可以

#### 1.2.5 开发板的配置

将板子上工程里的CMakeLists.txt文件中配置好新编译的opencv库的路径编译项目工程生成可执行文件 

. build-linux-RK3588.sh

. run.sh

目前opencv编译成功了，但是移植到板子上编译项目时会出现
这类错误：error while loading shared libraries: …/…/lib/libopencv_core.so
按照以下博客操作没有解决问题
http://blog.chinaunix.net/uid-28669227-id-4843715.html
https://blog.csdn.net/Cwenge/article/details/85326197

如果还是不能解决问题可以使用编译好的opencv（注：编译真的让人崩溃o_O  ~~  !!!!!!!）

## 三、制作支持百度AI和opencv的文件系统

可以参考我之前的博客https://blog.csdn.net/qq_39993800/article/details/129466828?spm=1001.2014.3001.5501

### 1.1 添加openssl到文件系统

把制作好的根文件系统拷贝到ubuntu ，解压并进入解压生成的目录 ，输入以下命令把编译好的openssl拷贝到根文件系统的/usr/local/路径下面 ，cp -r /usr/local/openssl/ ./usr/local/  

修改根文件系统的环境变量，输入命令sudo vi ./etc/init.d/rcS           

添加openssl的环境变量 ，cp -r /usr/local/openssl/lib/* ./lib/  

### 1.2 添加curl到文件系统

把编译好的curl库拷贝到根文件系统的/usr/local/路径下面 ，sudo cp -r /usr/local/curl/ ./usr/local/   

修改根文件系统的环境变量，输入命令sudo vi ./etc/init.d/rcS  

添加curl的环境变量  ，PATH=$PATH:/usr/local/curl/bin 

拷贝 ubuntu下的/usr/local/curl/lib 下的所有文件拷贝到. /lib 目录下  ，cp -r /usr/local/curl/lib/* ./lib/   

### 1.3 添加jsoncpp到文件系统

在根文件系统./usr/local/下面创建一个json的文件  ，sudo mkdir json

将编译好的jsoncpp 目录下的 include 文件夹和lib复制到根文件系统./usr/local/json/ 目录 ， cp -r /usr/local/json/* ./json/  

拷贝 /usr/local/json/lib 下的所有文件到 ./lib 目录下  ，cp -r /usr/local/json/lib/* ./lib/  

### 1.4 添加opencv到文件系统

将编译好的opencv拷贝到根文件系统的 ./usr/local/下面  ，cp -r /usr/local/opencv-4.7.0/ ./usr/local/  

将编译好的opencv库拷贝到根文件系统的 ./lib下面  ， cp -r /opt/opencv-arm/lib/* ./lib/  

使用命令“cd lib/”进入“.lib”文件夹。使用以下命令创建链接。因为自带的 libstdc++.so.6.0.10 不支持GLIBCXX_3.4.11，运行程序会报错  

cd ./lib/

rm -rf libstdc++.so.6

cp -r /usr/local/arm/4.4.1/arm-none-linux-gnueabi/libc/usr/lib/libstdc++.so.6.0.12 ./

ln -s libstdc++.so.6.0.12 libstdc++.so.6

###  1.5 添加中文字库

在跟文件系统的./opt/qt-5.7.0/lib/下使用mkdir fonts 创建一个存放字库的文件，然后将文件“wenquanyi.ttf”拷贝到根文件系统的“./opt/qt-5.7.0/lib/fonts”  

打开根文件系统的/etc/profile，添加字库的环境变量，注意这里字库的环境变量一定要写在QT库的路径下面，export QT_QPA_FONTDIR=$QT_ROOT/lib/fonts  

### 1.6 打包文件系统

 生成可以下载的 system.img 文件需要工具“mkimage” ，在根目录解压它，然后回到解压根文件系统的目录下，我们输入以下命令生成文件系统，注意这里的我们指定的linux的空间大小为2G，所以我们在烧写的时候要使用2G的分区，也就是命令fdisk -c 0 2048 300 300         

 make_ext4fs -s -l 2092957696 -a root -L linux system.img root  

 最后，我们把生成的文件系统烧写到开发板并验证是否可以启动成功  