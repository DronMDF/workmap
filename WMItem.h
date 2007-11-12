
#pragma once

#include <QList>
#include <QVariant>

class WMItem
{
public:
	WMItem(WMItem *parent = 0);
	~WMItem();

	WMItem *child(int number);
	WMItem *parent();

	int childCount() const;
	int childNumber() const;

	QVariant data(int column) const;
	bool setData(int column, const QVariant &value);

	bool insertChildren(int position, int count);
	bool removeChildren(int position, int count);

private:
	QList<WMItem *> childItems;
	WMItem *parentItem;

	QString name;
};
