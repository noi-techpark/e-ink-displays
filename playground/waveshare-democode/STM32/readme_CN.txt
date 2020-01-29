/*****************************************************************************
* | File      	:   Readme_CN.txt
* | Author      :   Waveshare team
* | Function    :   Help with use
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2019-07-24
* | Info        :   在这里提供一个中文版本的使用文档，以便你的快速使用
******************************************************************************/
这个文件是帮助您使用本例程。

1.基本信息：
本例程是基于Arduino进行开发的，例程均在Arduino UNO上进行了验证;
本例程使用e-Paper Shield模块进行了验证。

2.管脚连接：
管脚连接你可以在DEV_Config.h中查看，这里也再重述一次：
e-Paper Shield   =>    STM32F103
SCLK             ->    PA5
MISO             ->    PA6
MOSI             ->    PA7
EPD_CS           ->    PB6
EPD_DC           ->    PC7
EPD_RST          ->    PA9
EPD_BUSY         ->    PA8
SD_CS_0          ->    PB10
SPIRAM_CS        ->    PB4

3.基本使用：
由于本工程是一个综合工程，对于使用而言，你可能需要阅读以下内容：
栗子1：
    如果你购买的5.83inch e-paper，那么你应该把对应的115行代码的注释去掉，即：
        //		EPD_5in83_test();
    修改成：
        EPD_5in83_test();
栗子2：
    如果你购买的2.9inch e-paper (B)，由于2.9寸的B型和C型是公用的驱动代码，
    那么你应该把对应的129行代码的注释去掉，即：
        //		EPD_2in9bc_test();
    修改成：
        EPD_2in9bc_test();
注意：对于EPD_1in54_V2_test()和EPD_2in13_V2_test()请注意你的屏幕背面是否贴有V2标识。
然后编译烧录
