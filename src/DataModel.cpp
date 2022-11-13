#include "DataModel.h"

DataModel::DataModel()
{

}

QVector<TableData> DataModel::getAllData()
{
    QMutexLocker locker(&_mutex);
    return _tableDatas;
}

void DataModel::addData(const TableData &tableData)
{
    QMutexLocker locker(&_mutex);
    _tableDatas.push_back(tableData);
    emit update();
}

TableData DataModel::getData(const int &index) const
{
    QMutexLocker locker(&_mutex);
    return _tableDatas.value(index, TableData(false));
}

int DataModel::getDataSize() const
{
    QMutexLocker locker(&_mutex);
    return _tableDatas.size();
}
