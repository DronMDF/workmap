
#include <QMainWindow>

class QTreeView;
class QAction;
class QMenu;
class QToolBar;
class QTextEdit;

class WMWindow : public QMainWindow
{
	Q_OBJECT

public:
	WMWindow();
	virtual ~WMWindow();

protected:
	virtual void closeEvent(QCloseEvent *event);

private slots:
	void newFile();
	void open();
	bool save();
	bool saveAs();
	void about();
	void documentWasModified();

	void insertWork();
	void insertSub();

private:
	void createActions();
	void updateActions ();
	void createMenus();
	void createToolBars();
	void createStatusBar();
	void readSettings();
	void writeSettings();
	bool maybeSave();
	void loadFile(const QString &fileName);
	bool saveFile(const QString &fileName);
	void setCurrentFile(const QString &fileName);
	QString strippedName(const QString &fullFileName);


	QTextEdit *textEdit QT_DEPRECATED_VARIABLE;
	QString curFile;

	QTreeView *view;

	QMenu *fileMenu;
	QMenu *editMenu;
	QMenu *actionMenu;
	QMenu *helpMenu;

	QToolBar *fileToolBar;
	QToolBar *editToolBar;
	QAction *newAct;
	QAction *openAct;
	QAction *saveAct;
	QAction *saveAsAct;
	QAction *exitAct;
	QAction *cutAct;
	QAction *copyAct;
	QAction *pasteAct;
	QAction *aboutAct;
	QAction *aboutQtAct;

	QAction *insertWorkAct;
	QAction *insertSubAct;
};
