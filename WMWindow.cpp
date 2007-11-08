
#include <QtGui>

#include "WMWindow.h"
#include "WMSettings.h"


WMWindow::WMWindow()
{
	init();
}

void WMWindow::closeEvent (QCloseEvent *event)
{
	writeSettings ();
	event->accept();
}

// -----------------------------------------------------------------------------
// Инициализация

void WMWindow::init()
{
	//setAttribute(Qt::WA_DeleteOnClose);

	setWindowTitle ("WorkMap");

	QStandardItemModel *model = new QStandardItemModel;
	tree = new QTreeView;
	tree->setModel (model);
	//tree->setHeaderHidden(true);	Эта штука появилась в QT4.4

	setCentralWidget(tree);

	createActions();
	createMenus();
	createToolBars();
	createStatusBar();

	readSettings();
}

void WMWindow::createActions()
{
	newAct = new QAction(QIcon(":/images/new.png"), tr("&New"), this);
	newAct->setShortcut(tr("Ctrl+N"));
	newAct->setStatusTip(tr("Create a new file"));
	connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

	openAct = new QAction(QIcon(":/images/open.png"), tr("&Open..."), this);
	openAct->setShortcut(tr("Ctrl+O"));
	openAct->setStatusTip(tr("Open an existing file"));
	connect(openAct, SIGNAL(triggered()), this, SLOT(openFile()));

	saveAct = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
	saveAct->setShortcut(tr("Ctrl+S"));
	saveAct->setStatusTip(tr("Save the document to disk"));
	connect(saveAct, SIGNAL(triggered()), this, SLOT(saveFile()));

	saveAsAct = new QAction(tr("Save &As..."), this);
	saveAsAct->setStatusTip(tr("Save the document under a new name"));
	connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveFileAs()));

	closeAct = new QAction(tr("&Close"), this);
	closeAct->setShortcut(tr("Ctrl+W"));
	closeAct->setStatusTip(tr("Close this window"));
	connect(closeAct, SIGNAL(triggered()), this, SLOT(close()));

	exitAct = new QAction(tr("E&xit"), this);
	exitAct->setShortcut(tr("Ctrl+Q"));
	exitAct->setStatusTip(tr("Exit the application"));
	connect(exitAct, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

	aboutAct = new QAction(tr("&About"), this);
	aboutAct->setStatusTip(tr("Show the application's About box"));
	connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

	aboutQtAct = new QAction(tr("About &Qt"), this);
	aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
	connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void WMWindow::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(newAct);
	fileMenu->addAction(openAct);
	fileMenu->addAction(saveAct);
	fileMenu->addAction(saveAsAct);
	fileMenu->addSeparator();
	fileMenu->addAction(closeAct);
	fileMenu->addAction(exitAct);

	menuBar()->addSeparator();

	helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(aboutAct);
	helpMenu->addAction(aboutQtAct);
}

void WMWindow::createToolBars()
{
	fileToolBar = addToolBar(tr("File"));
	fileToolBar->addAction(newAct);
	fileToolBar->addAction(openAct);

	fileToolBar->addAction(saveAct);
}

void WMWindow::createStatusBar()
{
	statusBar()->showMessage(tr("Ready"));
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

// -----------------------------------------------------------------------------
// Слоты

void WMWindow::newFile()
{
}

void WMWindow::openFile()
{
}

bool WMWindow::saveFile()
{
	return true;
}

bool WMWindow::saveFileAs()
{
	return true;
}

void WMWindow::about()
{
    QMessageBox::about(this, tr("About WorkMap"),
             tr("The <b>WorkMap</b> is experemental project management software "
                "with MindMap futures.<br/>"
		"Author: Andrey Valyaev "
		"<a href='mailto:dron@infosec.ru'>dron@infosec.ru</a>."));
}

void WMWindow::documentWasModified()
{
}
