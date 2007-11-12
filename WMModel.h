
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
	virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
	virtual QModelIndex index(int row, int column,
			const QModelIndex &parent = QModelIndex()) const;
	virtual QModelIndex parent(const QModelIndex &index) const;
	virtual QVariant data(const QModelIndex &index, int role) const;
	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;

protected:
	WMItem *getItem(const QModelIndex &index) const;

	QList<WMItem *> rootItems;
};
