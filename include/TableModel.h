#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <qqml.h>
#include <QAbstractTableModel>
#include <DataModel.h>

class TableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    void setDataModel(DataModel* dataModel);
    Q_INVOKABLE QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    int rowCount(const QModelIndex & = QModelIndex()) const override;

    int columnCount(const QModelIndex & = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;
public slots:
    void onUpdate();
private:
    DataModel* _dataModel;
};

#endif // TABLEMODEL_H
