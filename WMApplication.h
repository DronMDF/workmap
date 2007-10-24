
#include <QApplication>
#include <QSessionManager>

class WMApplication : public QApplication
{
public:
	WMApplication (int argc, char **argv);
	virtual ~WMApplication ();

	virtual void commitData (QSessionManager &sm);
};
