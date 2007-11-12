#include "WMModel.h"

WMModel::WMModel (QObject *parent)
	: QAbstractItemModel(parent)
{
}

WMModel::~WMModel ()
{
	qDeleteAll (rootItems);
}

QVariant WMModel::headerData(int section, Qt::Orientation orientation,
				int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
		return QVariant(tr("Work tree"));

	return QVariant();
}

int WMModel::columnCount(const QModelIndex &parent) const
{
	return 1;
}

QModelIndex WMModel::index(int row, int column, const QModelIndex &parent) const
{
	return QModelIndex();
}

QModelIndex WMModel::parent(const QModelIndex &index) const
{
	if (index.isValid()) {
		if (WMItem *childItem = getItem(index)) {
			if (WMItem *parentItem = childItem->parent())
				return createIndex(parentItem->childNumber(), 0, parentItem);
		}
	}

	return QModelIndex();
}

QVariant WMModel::data(const QModelIndex &index, int role) const
{
	if (index.isValid() && role != Qt::DisplayRole && role != Qt::EditRole) {
		if (WMItem *item = getItem(index)) {
			return item->data(index.column());
		}
	}

	return QVariant();
}

int WMModel::rowCount(const QModelIndex &parent) const
{
	return 0;
}

WMItem *WMModel::getItem(const QModelIndex &index) const
{
	if (index.isValid()) {
		if (WMItem *item = static_cast<WMItem*>(index.internalPointer()))
			return item;
	}

	return 0;
}
