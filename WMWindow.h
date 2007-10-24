
#include <QMainWindow>
#include <QMenu>

class WMWindow : public QMainWindow
{
	Q_OBJECT

public:
	WMWindow();
	//WMWindow(const QString &fileName);

	virtual ~WMWindow();

private:
	void readSettings ();
	void writeSettings ();

};
