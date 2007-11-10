
#pragma once

#include <QAbstractItemModel>
#include <QVariant>

class WMModel : public QAbstractItemModel
{
	Q_OBJECT

public:
	WMModel (QObject *parent = 0)
		: QAbstractItemModel(parent)
	{
	}

	virtual ~WMModel ()
	{
	}

	virtual QVariant headerData(int section, Qt::Orientation orientation,
					int role) const
	{
		if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
			return QVariant(tr("Work tree"));

		return QVariant();
	}

	virtual int columnCount(const QModelIndex &parent = QModelIndex()) const
	{
		return 1;
	}

	virtual QModelIndex index(int row, int column,
                       const QModelIndex &parent = QModelIndex()) const
	{
		return QModelIndex();
	}

	virtual QModelIndex parent(const QModelIndex &index) const
	{
		return QModelIndex();
	}

	virtual QVariant data(const QModelIndex &index, int role) const
	{
		if (!index.isValid())
			return QVariant();

		return QVariant(tr("data"));
	}

	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const
	{
		return 0;
	}
};
