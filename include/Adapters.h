#ifndef ADAPTERS_H
#define ADAPTERS_H

#include "IAdapter.h"
#include "CommonStructs.h"

/*-----------------------------------------------------------------------------------*/
/*
 * Class that make fake prediction from filename;
 */
class FakePrediction
{
public:
    TableData fakeWork(const QString& fileName);
};

/*-----------------------------------------------------------------------------------*/
/*
 * FakeApater like a prototype for real adapter;
 * Real adapter should be inherits IAdapter with overriding work() function;
 */

class FakeAdapter : public IAdapter
{
public:
    FakeAdapter(DataModel* dataModel, QMLAdapter* qmlAdapter, QObject* parent = nullptr);
    TableData work(const QString& fileName) override;
private:
    void testDelay(const int& sec = 0);
    FakePrediction _predictionModel;
};

#endif // ADAPTERS_H
