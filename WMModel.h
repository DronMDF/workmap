
#pragma once

#include <QAbstractItemModel>
#include <QVariant>
#include <QList>

#include "WMItem.h"

class WMModel : public QAbstractItemModel
{
	Q_OBJECT

public:
	WMModel (QObject *parent = 0);
	~WMModel ();

	virtual QVariant headerData(int section, Qt::Orientation orientation,
			int role) const;
	virtual Qt::ItemFlags flags(const QModelIndex &index) const;
	virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
	virtual QModelIndex index(int row, int column,
			const QModelIndex &parent = QModelIndex()) const;
	virtual QModelIndex parent(const QModelIndex &index) const;
	virtual QVariant data(const QModelIndex &index, int role) const;
	virtual bool setData(const QModelIndex &index, const QVariant &value,
			int role = Qt::EditRole);

	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;

	virtual bool insertRows(int position, int rows,
			const QModelIndex &parent = QModelIndex());


protected:
	WMItem *getItem(const QModelIndex &index) const;

	WMItem rootItem;
};
