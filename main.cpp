#include <iostream>
#include <string>
#include <cmath>

#include <QApplication>
#include "MainWindow.h"

int main(int argc, char* argv[])
{
   QApplication app(argc, argv);
   MainWindow window;

   QSize availableSize = qApp->desktop()->availableGeometry().size();
   window.resize(availableSize.width(), availableSize.height());
   
   window.show();
   return app.exec();
}