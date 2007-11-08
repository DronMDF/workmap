
#include <QMainWindow>

class QTreeView;
class QAction;
class QMenu;
class QToolBar;

class WMWindow : public QMainWindow
{
	Q_OBJECT

public:
	WMWindow();
	//WMWindow(const QString &fileName);

protected:
	void closeEvent(QCloseEvent *event);

private:
	// Инициализация
	void init();
	void createActions();
	void createMenus();
	void createToolBars();
	void createStatusBar();

	// Настройки
	void readSettings ();
	void writeSettings ();

	QTreeView *tree;

	QAction *newAct;
	QAction *openAct;
	QAction *saveAct;
	QAction *saveAsAct;
	QAction *closeAct;
	QAction *exitAct;
	QAction *aboutAct;
	QAction *aboutQtAct;

	QMenu *fileMenu;
	QMenu *editMenu;
	QMenu *helpMenu;

	QToolBar *fileToolBar;
	QToolBar *editToolBar;

private slots:
	void newFile();
	void openFile();
	bool saveFile();
	bool saveFileAs();
	void about();
	void documentWasModified();
};
