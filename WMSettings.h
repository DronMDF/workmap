
#include <QSettings>

class WMSettings : public QSettings
{
public:
	WMSettings()
		: QSettings ("MDF Group", "WorkMap")
	{
	}
};
