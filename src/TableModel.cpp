#include "TableModel.h"


void TableModel::setDataModel(DataModel *dataModel)
{
    if (!dataModel)
    {
        GUI_DEBUG("Null pointer dataModel* here.");
        return;
    }
    _dataModel = dataModel;
    connect(_dataModel, &DataModel::update, this, &TableModel::onUpdate, Qt::QueuedConnection);
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return TableHeaders.value(section, "none");
}

int TableModel::rowCount(const QModelIndex &) const
{
    return _dataModel->getDataSize();
}

int TableModel::columnCount(const QModelIndex &) const
{
    return TableHeaders.size();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    auto getData = [this](const QModelIndex &index)->QVariant{

        auto tableData = _dataModel->getData(index.row());
        if (!tableData.isValid) return QVariant();

        switch(index.column())
        {
        case 0: return QVariant::fromValue(tableData.fileName.fileName());
        case 1: return QVariant::fromValue(tableData.colorPrediction == ColorPrediction::Red? QString("Red") : QString("Blue"));
        case 2: return QVariant::fromValue(QString::number(tableData.LLR, 'f', 2));
        case 3: return QVariant::fromValue(QString::number(tableData.reliability, 'f', 3));
        case 4: return QVariant::fromValue(tableData.path.absolutePath());
        case 5: return QVariant::fromValue(double(tableData.LLR));
        }
        return QVariant();
    };

    switch (role) {
    case Qt::DisplayRole:
        return getData(index);
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> TableModel::roleNames() const
{
    return { {Qt::DisplayRole, "display"} };
}

void TableModel::onUpdate() {
    GUI_DEBUG("onNewData");
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    endInsertRows();

    emit dataChanged(index(rowCount() - 1, 0), index(rowCount() - 1, columnCount() - 1));
}
