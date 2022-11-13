#include "Adapters.h"

/*-----------------------------------------------------------------------------------*/
TableData FakePrediction::fakeWork(const QString &fileName)
{
    //todo mytodo check this file:// on WinX64
    TableData tableData;
    tableData.fileName = QFileInfo(fileName);
    tableData.colorPrediction = ColorPrediction::Red;
    tableData.LLR = 121;
    tableData.reliability = 212;
    tableData.path = QDir(QFileInfo(fileName).absolutePath());
    return tableData;
}
/*-----------------------------------------------------------------------------------*/
FakeAdapter::FakeAdapter(DataModel *dataModel, QMLAdapter *qmlAdapter, QObject *parent)
    : IAdapter(dataModel, qmlAdapter, parent){}

TableData FakeAdapter::work(const QString &fileName)
{
    testDelay(1);
    return _predictionModel.fakeWork(fileName);
}

void FakeAdapter::testDelay(const int &sec)
{
    thread()->sleep(sec);
}
/*-----------------------------------------------------------------------------------*/
