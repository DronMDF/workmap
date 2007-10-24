
#include <QtGui>

#include "WMWindow.h"
#include "WMSettings.h"


WMWindow::WMWindow()
{
	setAttribute(Qt::WA_DeleteOnClose);
	readSettings ();

	setWindowTitle (tr ("WorkMap"));

	// Создаем меню.
	//menuFile.setTitle (tr("&File"));
	//menuBar()->addMenu(&menuFile);

	//statusBar()->addWidget (QLabel (tr("Application Started")));

	QTreeWidget *tree = new QTreeWidget(this);
	tree->setColumnCount (3);

	QTreeWidgetItem *item1 = new QTreeWidgetItem(tree, QStringList() << "item1" << "***" << "done");
	new QTreeWidgetItem(tree, QStringList() << "item2" << "***" << "done");
	new QTreeWidgetItem(tree, QStringList() << "item3" << "***" << "done");
	new QTreeWidgetItem(item1, QStringList() << "item12" << "***" << "done");
	new QTreeWidgetItem(item1, QStringList() << "item13" << "***" << "done");

	setCentralWidget (tree);
}

WMWindow::~WMWindow ()
{
	writeSettings ();
}

// -----------------------------------------------------------------------------
// private

void WMWindow::readSettings()
{
	WMSettings settings;
	QPoint pos = settings.value ("pos", QPoint(200, 200)).toPoint();
	QSize size = settings.value ("size", QSize(400, 400)).toSize();
	move (pos);
	resize (size);
}

void WMWindow::writeSettings()
{
	WMSettings settings;
	settings.setValue ("pos", pos());
	settings.setValue ("size", size());
}
