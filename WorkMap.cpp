
#include <QApplication>

//#include "WMApplication.h"
#include "WMWindow.h"

int main (int argc, char **argv)
{
	Q_INIT_RESOURCE(WMResources);

	//WMApplication app(argc, argv);
	QApplication app(argc, argv);

	WMWindow win;
	win.show();

	return app.exec();
}
