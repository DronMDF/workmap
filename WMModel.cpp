
#include <QMessageBox>

#include "WMModel.h"

WMModel::WMModel (QObject *parent)
	: QAbstractItemModel(parent)
{

	rootItem.insertChildren (0, 5);
	rootItem.child(0)->setData (0, "child0");
	rootItem.child(1)->setData (0, "child1");
	rootItem.child(2)->setData (0, "child2");
	rootItem.child(3)->setData (0, "child3");
	rootItem.child(4)->setData (0, "child4");

//	QMessageBox::information (0, tr("info"), QString("View heigth: %1").arg(rowCount()));
}

WMModel::~WMModel ()
{
}

QVariant WMModel::headerData(int section, Qt::Orientation orientation,
				int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
		return QVariant(tr("Work tree"));

	return QVariant();
}

Qt::ItemFlags WMModel::flags(const QModelIndex &index) const
{
	if (index.isValid())
		return Qt::ItemIsEnabled | Qt::ItemIsSelectable;

	return 0;
}

int WMModel::columnCount(const QModelIndex &parent) const
{
	return 1;
}

QModelIndex WMModel::index(int row, int column, const QModelIndex &parent) const
{
	if (hasIndex(row, column, parent)) {
		if (WMItem *parentItem = getItem(parent)) {
			if (WMItem *childItem = parentItem->child(row))
				return createIndex(row, column, childItem);
		}
	}

	return QModelIndex();
}

QModelIndex WMModel::parent(const QModelIndex &index) const
{
	if (index.isValid()) {
		WMItem *childItem = getItem(index);
		if (WMItem *parentItem = childItem->parent()) {
			if (parentItem != &rootItem)
				return createIndex(parentItem->childNumber(), 0, parentItem);
		}
	}

	return QModelIndex();
}

QVariant WMModel::data(const QModelIndex &index, int role) const
{
	if (index.isValid()) {
		if (role == Qt::DisplayRole || role == Qt::EditRole) {
			if (WMItem *item = getItem(index))
				return item->data(index.column());
		}
	}

	return QVariant();
}

bool WMModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (role != Qt::EditRole)
		return false;

	WMItem *item = getItem(index);
	return item->setData(index.column(), value);
}

int WMModel::rowCount(const QModelIndex &parent) const
{
	WMItem *parentItem = getItem(parent);
	return parentItem->childCount();
}

WMItem *WMModel::getItem(const QModelIndex &index) const
{
	if (index.isValid()) {
		if (WMItem *item = static_cast<WMItem *>(index.internalPointer()))
			return item;
	}

	return const_cast<WMItem *>(&rootItem);
}

bool WMModel::insertRows (int position, int rows, const QModelIndex &parent)
{
	WMItem *parentItem = getItem(parent);

	beginInsertRows (parent, position, position + rows - 1);
	bool ok = parentItem->insertChildren(position, rows);
	endInsertRows ();

	return ok;
}
