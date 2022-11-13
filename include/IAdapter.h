#ifndef IADAPTER_H
#define IADAPTER_H

#include <QDir>
#include <QTextTable>
#include <QTextDocument>
#include <QTextCursor>
#include <QPrinter>
#include <QMetaObject>
#include <QThread>
#include <QObject>

#include "QMLAdapter.h"
#include "DataModel.h"
#include "TableModel.h"

#include <stdexcept>

/*-----------------------------------------------------------------------------------*/
class IAdapter : public QObject
{
    Q_OBJECT
public:
    IAdapter(DataModel* dataModel, QMLAdapter *qmlAdapter, QObject* parent = nullptr);
    Q_INVOKABLE void createPDFThreadSafe(const QString& fileName);
    Q_INVOKABLE void processColorIDFolderThreadSafe(const QString& folderName);
    Q_INVOKABLE void processColorIDThreadSafe(const QString& fileName);
signals:
    void chooseMeControlEnabling(const bool&);
protected:
    virtual TableData work(const QString& fileName) = 0;
private slots:
    void createPDF(const QString& fileName);
    void processColorID(const QString& fileName);
    void processColorIDFolder(const QString& folderName);
private:
    DataModel* _dataModel;
    QMLAdapter* _qmlAdapter;
};
/*-----------------------------------------------------------------------------------*/

#endif // IADAPTER_H
