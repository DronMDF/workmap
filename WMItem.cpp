
#include <QObject>

#include "WMItem.h"

WMItem::WMItem (WMItem *parent)
	: parentItem (parent)
{
}

WMItem::~WMItem ()
{
	qDeleteAll (childItems);
}

WMItem *WMItem::parent()
{
	return parentItem;
}

WMItem *WMItem::child (int number)
{
	return childItems.value(number);
}

int WMItem::childCount() const
{
	return childItems.count();
}

int WMItem::childNumber() const
{
	if (parentItem)
		return parentItem->childItems.indexOf(const_cast<WMItem*>(this));

	return 0;
}

QVariant WMItem::data(int column) const
{
	if (column == 0)
		return name;

	return QVariant(QObject::tr("item data"));
}

bool WMItem::setData(int column, const QVariant &value)
{
	Q_ASSERT (column == 0);

	name = value.toString();
	return true;
}

bool WMItem::insertChildren (int position, int count)
{
	if (position < 0 || position > childItems.size())
		return false;

	for (int row = 0; row < count; ++row) {
		WMItem *item = new WMItem (this);
		childItems.insert(position, item);
	}

	return true;
}

bool WMItem::removeChildren(int position, int count)
{
	if (position < 0 || position + count > childItems.size())
		return false;

	for (int row = 0; row < count; ++row)
		delete childItems.takeAt(position);

	return true;
}
