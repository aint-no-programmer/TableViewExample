#include "IAdapter.h"

IAdapter::IAdapter(DataModel *dataModel, QMLAdapter* qmlAdapter, QObject *parent)
    : QObject(parent),
      _dataModel(dataModel),
      _qmlAdapter(qmlAdapter)

{
    if (dataModel == nullptr || qmlAdapter == nullptr) throw std::invalid_argument("Nullptr passed into Adapter constructor");

    connect(this, &IAdapter::chooseMeControlEnabling, _qmlAdapter, &QMLAdapter::onChooseMeControlEnabling, Qt::DirectConnection);
}

void IAdapter::createPDFThreadSafe(const QString &fileName)
{
    if (thread() == QThread::currentThread())
    {
        createPDF(fileName);
    }
    else
    {
        QMetaObject::invokeMethod(this, "createPDF", Qt::QueuedConnection,
                                  Q_ARG(QString, fileName));
    }
}

void IAdapter::processColorIDFolderThreadSafe(const QString &folderName)
{
    QString fileName_cutted(folderName);
#ifdef WINDOWS
    fileName_cutted.remove(0, 1);
#endif
    if (thread() == QThread::currentThread())
    {
        processColorIDFolder(fileName_cutted);
    }
    else
    {
        QMetaObject::invokeMethod(this, "processColorIDFolder", Qt::QueuedConnection,
                                  Q_ARG(QString, fileName_cutted));
    }
}

void IAdapter::processColorIDThreadSafe(const QString &fileName)
{
    QString fileName_cutted(fileName);
#ifdef WINDOWS    
    fileName_cutted.remove(0, 1);
#endif
    if (thread() == QThread::currentThread())
    {

        processColorID(fileName_cutted);
    }
    else
    {
        QMetaObject::invokeMethod(this, "processColorID", Qt::QueuedConnection,
                                  Q_ARG(QString, fileName_cutted));
    }
}

void IAdapter::createPDF(const QString &fileName)
{
    //setup document
    QTextDocument document;
    document.setDocumentMargin(10);
    QTextCursor cursor(&document);

    QTextTableFormat format;
    format.setCellPadding(10);
    //format.setCellSpacing(20);
    format.setAlignment(Qt::AlignCenter);
    format.setBorder(1);

    cursor.movePosition(QTextCursor::Start);
    //create table: getDataSize() + 1 - because first row is header and others are data;
    cursor.insertTable(_dataModel->getDataSize() + 1, TableHeaders.size(), format);

    //make bold font for headers
    QTextCharFormat charFormat = cursor.charFormat();
    auto font = charFormat.font();
    font.setBold(true);
    charFormat.setFont(font);
    //make headers
    for (auto& header: TableHeaders)
    {
        cursor.insertText(header, charFormat);
        cursor.movePosition(QTextCursor::NextCell);
    }
    //make content
    QVector<TableData> data = _dataModel->getAllData();
    for(size_t i = 0; i < data.size(); ++i)
    {
        auto tableData = data.value(i);
        //fileName
        cursor.insertText(tableData.fileName.fileName());
        cursor.movePosition(QTextCursor::NextCell);
        //ColorPrediction
        auto colorConvert = [this](ColorPrediction& a){
            return a == ColorPrediction::Red? "Red" : "Female";
        };
        cursor.insertText(colorConvert(tableData.colorPrediction));
        cursor.movePosition(QTextCursor::NextCell);
        //LLR
        cursor.insertText(QString::number(tableData.LLR, 'f', 2));
        cursor.movePosition(QTextCursor::NextCell);
        //Reliability
        cursor.insertText(QString::number(tableData.reliability, 'f', 3));
        cursor.movePosition(QTextCursor::NextCell);
        //path
        cursor.insertText(tableData.path.absolutePath());
        cursor.movePosition(QTextCursor::NextCell);
    }

    //Printer
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    document.print(&printer);
}

void IAdapter::processColorID(const QString &fileName)
{
    emit chooseMeControlEnabling(false);    //lock control
    auto tt =fileName.toStdString();
    TableData tableData = work(fileName);
    _dataModel->addData(tableData);

    emit chooseMeControlEnabling(true);     //unlock control
}

void IAdapter::processColorIDFolder(const QString &folderName)
{
    std::string tt = folderName.toStdString();
    std::string rr = folderName.toStdString();
    //get files list
    QDir folder(folderName);
    //set name filters
    QStringList filters;
    //filters << "*.png";
    QFileInfoList files = folder.entryInfoList(filters, QDir::Files, QDir::NoSort);
    //process each file
    for (const auto& file : files)
    {
        processColorID(file.absoluteFilePath());
    }

}
