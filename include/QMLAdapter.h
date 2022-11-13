#ifndef QMLADAPTER_H
#define QMLADAPTER_H

#include <QUrl>
#include <QString>
#include <QSettings>
#include <QVariant>
#include <QObject>

#include "CommonStructs.h"

class QMLAdapter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool chooseMeControlEnabled READ chooseMeControlEnabled WRITE setChooseMeControlEnabled NOTIFY chooseMeControlEnabledChanged)
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
    Q_PROPERTY(QString folderName READ folderName WRITE setFolderName NOTIFY folderNameChanged)
    Q_PROPERTY(QString fileNameUrl READ fileNameUrl WRITE setFileNameUrl NOTIFY fileNameUrlChanged)
    Q_PROPERTY(QString folderNameUrl READ folderNameUrl WRITE setFolderNameUrl NOTIFY folderNameUrlChanged)
public:
    /*
     * Auxillary structure for Settings (look at .cpp file)
     */
    struct SettingValue{
        SettingValue(){}
        SettingValue(const bool& isValid, const QVariant& value) : _isValid(isValid), _value(value){}
        SettingValue& operator=(const SettingValue& a)
        {
            _isValid = a._isValid;
            _value = a._value;
            return *this;
        }
        SettingValue(const SettingValue& a)
        {
            _isValid = a._isValid;
            _value = a._value;
        }
        bool isValid(){return _isValid;}
        QVariant value(){return _value;}
    private:
        bool _isValid;
        QVariant _value;
    };

    QMLAdapter(QSettings* settings);
public slots:
    void onChooseMeControlEnabling(const bool& value);
    //q_properties
    bool chooseMeControlEnabled();
    void setChooseMeControlEnabled(const bool& chooseMeControlEnabled);
    //
    QString folderName();
    void setFolderName(const QString& urlFolderName);
    //
    QString folderNameUrl(){return _folderNameUrl;}
    void setFolderNameUrl(const QString& urlFolderNameUrl)
    {
        if (_folderNameUrl == urlFolderNameUrl) return;
        _folderNameUrl = urlFolderNameUrl;
        _settings->setValue("folderNameUrl", _folderNameUrl);
        emit folderNameUrlChanged(_folderNameUrl);
    }
    //
    QString fileName();
    void setFileName(const QString& urlFileName);
    //
    QString fileNameUrl(){return _fileNameUrl;}
    void setFileNameUrl(const QString& urlFileNameUrl)
    {
        if (_fileNameUrl == urlFileNameUrl) return;
        _fileNameUrl = urlFileNameUrl;
        _settings->setValue("fileNameUrl", _fileNameUrl);
        emit fileNameUrlChanged(_fileNameUrl);
    }
signals:
    void fileNameUrlChanged(QString);
    void folderNameUrlChanged(QString);
    void chooseMeControlEnabledChanged(bool);
    void folderNameChanged(QString);
    void fileNameChanged(QString);
private:
    //functions
    void loadSettings();
    //
    QString _fileNameUrl;
    QString _folderNameUrl;
    bool _chooseMeControlEnabled;
    QSettings* _settings;
    QString _folderName;
    QString _fileName;
};


#endif // QMLADAPTER_H
