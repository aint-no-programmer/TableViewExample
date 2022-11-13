#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QObject>
#include <QString>
#include <QMutexLocker>
#include <QVector>

#include "CommonStructs.h"

class DataModel : public QObject
{
    Q_OBJECT
public:
    DataModel();
    QVector<TableData> getAllData();
    void addData(const TableData& tableData);
    TableData getData(const int& index) const;
    int getDataSize() const;
signals:
    void update();
private:
    QVector<TableData> _tableDatas;
    //aux
    mutable QMutex _mutex;
};

#endif // DATAMODEL_H
