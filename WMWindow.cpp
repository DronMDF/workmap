
#include <QtGui>

#include <modeltest.h>

#include "WMWindow.h"
#include "WMSettings.h"
#include "WMModel.h"


WMWindow::WMWindow()
{
	WMModel *model = new WMModel ();
	ModelTest test(model);

	view = new QTreeView ();
	view->setModel (model);

	view->setEditTriggers(QAbstractItemView::DoubleClicked
				| QAbstractItemView::SelectedClicked
				| QAbstractItemView::EditKeyPressed);

	setCentralWidget(view);

	// Временно но задепрекатим.
	textEdit = new QTextEdit;

	createActions();
	createMenus();
	createToolBars();
	createStatusBar();

	readSettings();

	connect(textEdit->document(), SIGNAL(contentsChanged()),
		this, SLOT(documentWasModified()));

	setCurrentFile("");
}

WMWindow::~WMWindow()
{
}

void WMWindow::closeEvent (QCloseEvent *event)
{
	if (maybeSave()) {
		writeSettings();
		event->accept();
	} else {
		event->ignore();
	}
}

void WMWindow::newFile()
{
	if (maybeSave()) {
		textEdit->clear();
		setCurrentFile("");
	}
}

void WMWindow::open()
{
	if (maybeSave()) {
		QString fileName = QFileDialog::getOpenFileName(this);
		if (!fileName.isEmpty())
		loadFile(fileName);
	}
}

bool WMWindow::save()
{
	if (curFile.isEmpty()) {
		return saveAs();
	} else {
		return saveFile(curFile);
	}
}

bool WMWindow::saveAs()
{
	QString fileName = QFileDialog::getSaveFileName(this);
	if (fileName.isEmpty())
		return false;

	return saveFile(fileName);
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
	setWindowModified(true);
}

void WMWindow::insertWork()
{
// 	if (view->state() == QAbstractItemView::EditingState)
// 		return;

	QModelIndex index = view->selectionModel()->currentIndex();
	QAbstractItemModel *model = view->model();

	const int row = index.row() + 1;
	if (!model->insertRow(row, index.parent())) {
		QMessageBox::warning (this, tr("warning"), tr("Unable to insert item"));
		return;
	}

	QModelIndex child = model->index(row, 0, index.parent());
	model->setData (child, QVariant(tr("unnamed")));
	view->selectionModel()->setCurrentIndex(child,
		QItemSelectionModel::ClearAndSelect);

	updateActions();
}

void WMWindow::insertSub()
{
// 	if (view->state() == QAbstractItemView::EditingState)
// 		return;

	QModelIndex index = view->selectionModel()->currentIndex();
	QAbstractItemModel *model = view->model();

	if (model->columnCount(index) == 0) {
		if (!model->insertColumn(0, index))
			return;
	}

	const int row = model->rowCount(index);
	if (!model->insertRow(row, index))
		return;

	QModelIndex child = model->index(row, 0, index);
	model->setData (child, QVariant(tr("unnamed")));

	view->selectionModel()->setCurrentIndex(child,
		QItemSelectionModel::ClearAndSelect);

	updateActions();
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
	connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

	saveAct = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
	saveAct->setShortcut(tr("Ctrl+S"));
	saveAct->setStatusTip(tr("Save the document to disk"));
	connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

	saveAsAct = new QAction(tr("Save &As..."), this);
	saveAsAct->setStatusTip(tr("Save the document under a new name"));
	connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

	exitAct = new QAction(tr("E&xit"), this);
	exitAct->setShortcut(tr("Ctrl+Q"));
	exitAct->setStatusTip(tr("Exit the application"));
	connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

	cutAct = new QAction(QIcon(":/images/cut.png"), tr("Cu&t"), this);
	cutAct->setShortcut(tr("Ctrl+X"));
	cutAct->setStatusTip(tr("Cut the current selection's contents to the "
				"clipboard"));
	connect(cutAct, SIGNAL(triggered()), textEdit, SLOT(cut()));

	copyAct = new QAction(QIcon(":/images/copy.png"), tr("&Copy"), this);
	copyAct->setShortcut(tr("Ctrl+C"));
	copyAct->setStatusTip(tr("Copy the current selection's contents to the "
				"clipboard"));
	connect(copyAct, SIGNAL(triggered()), textEdit, SLOT(copy()));

	pasteAct = new QAction(QIcon(":/images/paste.png"), tr("&Paste"), this);
	pasteAct->setShortcut(tr("Ctrl+V"));
	pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
				"selection"));
	connect(pasteAct, SIGNAL(triggered()), textEdit, SLOT(paste()));

	aboutAct = new QAction(tr("&About"), this);
	aboutAct->setStatusTip(tr("Show the application's About box"));
	connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

	aboutQtAct = new QAction(tr("About &Qt"), this);
	aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
	connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

	cutAct->setEnabled(false);
	copyAct->setEnabled(false);
	connect(textEdit, SIGNAL(copyAvailable(bool)),
		cutAct, SLOT(setEnabled(bool)));
	connect(textEdit, SIGNAL(copyAvailable(bool)),
		copyAct, SLOT(setEnabled(bool)));

	insertWorkAct = new QAction (tr("Insert work"), this);
	//insertWorkAct->setShortcut (Qt::Key_Enter);
	insertWorkAct->setShortcut (Qt::Key_Return);
	insertWorkAct->setStatusTip (tr("Insert new work at some level"));
	connect (insertWorkAct, SIGNAL (triggered()), this, SLOT(insertWork()));

	insertSubAct = new QAction (tr("Insert subwork"), this);
	insertSubAct->setShortcut (Qt::Key_Insert);
	insertSubAct->setStatusTip (tr("Insert new subwork"));
	connect (insertSubAct, SIGNAL (triggered()), this, SLOT(insertSub()));
}

void WMWindow::updateActions ()
{
	QModelIndex index = view->selectionModel()->currentIndex();

	statusBar()->showMessage(
		QString("current row: %1, column: %2")
			.arg(index.row())
			.arg(index.column()));
}

void WMWindow::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(newAct);
	fileMenu->addAction(openAct);
	fileMenu->addAction(saveAct);
	fileMenu->addAction(saveAsAct);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAct);

// 	editMenu = menuBar()->addMenu(tr("&Edit"));
// 	editMenu->addAction(cutAct);
// 	editMenu->addAction(copyAct);
// 	editMenu->addAction(pasteAct);

	actionMenu = menuBar()->addMenu (tr("&Action"));
	actionMenu->addAction (insertWorkAct);
	actionMenu->addAction (insertSubAct);

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

// 	editToolBar = addToolBar(tr("Edit"));
// 	editToolBar->addAction(cutAct);
// 	editToolBar->addAction(copyAct);
// 	editToolBar->addAction(pasteAct);
}

void WMWindow::createStatusBar()
{
	statusBar()->showMessage(tr("Ready"));
}

void WMWindow::readSettings()
{
	WMSettings settings;
	QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
	QSize size = settings.value("size", QSize(400, 400)).toSize();
	resize(size);
	move(pos);
}

void WMWindow::writeSettings()
{
	WMSettings settings;
	settings.setValue("pos", pos());
	settings.setValue("size", size());
}

bool WMWindow::maybeSave()
{
	if (textEdit->document()->isModified()) {
		int ret = QMessageBox::warning(this, tr("Application"),
			tr("The document has been modified.\n"
			"Do you want to save your changes?"),
			QMessageBox::Yes | QMessageBox::Default,
			QMessageBox::No,
			QMessageBox::Cancel | QMessageBox::Escape);

		if (ret == QMessageBox::Yes)
			return save();
		else if (ret == QMessageBox::Cancel)
			return false;
	}

	return true;
}

void WMWindow::loadFile(const QString &fileName)
{
	QFile file(fileName);
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		QMessageBox::warning(this, tr("Application"),
				tr("Cannot read file %1:\n%2.")
				.arg(fileName)
				.arg(file.errorString()));
		return;
	}

	QTextStream in(&file);
	QApplication::setOverrideCursor(Qt::WaitCursor);
	textEdit->setPlainText(in.readAll());
	QApplication::restoreOverrideCursor();

	setCurrentFile(fileName);
	statusBar()->showMessage(tr("File loaded"), 2000);
}

bool WMWindow::saveFile(const QString &fileName)
{
	QFile file(fileName);
	if (!file.open(QFile::WriteOnly | QFile::Text)) {
		QMessageBox::warning(this, tr("Application"),
				tr("Cannot write file %1:\n%2.")
				.arg(fileName)
				.arg(file.errorString()));
		return false;
	}

	QTextStream out(&file);
	QApplication::setOverrideCursor(Qt::WaitCursor);
	out << textEdit->toPlainText();
	QApplication::restoreOverrideCursor();

	setCurrentFile(fileName);
	statusBar()->showMessage(tr("File saved"), 2000);
	return true;
}

void WMWindow::setCurrentFile(const QString &fileName)
{
	curFile = fileName;
	textEdit->document()->setModified(false);
	setWindowModified(false);

	QString shownName;
	if (curFile.isEmpty())
		shownName = "untitled.txt";
	else
		shownName = strippedName(curFile);

	setWindowTitle(tr("%1[*] - %2").arg(shownName).arg(tr("WorkMap")));
}

QString WMWindow::strippedName(const QString &fullFileName)
{
	return QFileInfo(fullFileName).fileName();
}

