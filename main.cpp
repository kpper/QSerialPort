/******************************************************************************/
/* 项目名称: 串口调试助手Demo                                               */
/* 程序版本: V1.0                                               */
/* 使用系统: windows/Qt Creator                                                    */
/* 文件名称: main.c                                                   */
/* 文件功能:下位机调试;                           */
/* 项目描述: 使用qt5.4.2的串口类                                  */
/* 编写人员: kpper                                                           */
/* 编写日期: 2015-11-5                                                    */
/* 修改描述:采用4.8.7+qt5.4.2的串口类
 *                                   */
/******************************************************************************/


#include "serial.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");    //获取系统编码
   QTextCodec::setCodecForLocale(codec);
   QTextCodec::setCodecForCStrings(codec);
   QTextCodec::setCodecForTr(codec);

    Serial w;
    w.show();
    return a.exec();
}
