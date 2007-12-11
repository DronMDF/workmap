
class WMWorkManager
{
public:
	WMWork *CreateWork (Qstring parent = QString());
	int SubWorkNum (Qstring parent);

	WMWork *getWork (Qstring id);
	void deleteWork (Qstring id);
};