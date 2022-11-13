#include "QMLAdapter.h"



QMLAdapter::QMLAdapter(QSettings *settings) : _settings(settings)
{
    loadSettings();
}

void QMLAdapter::onChooseMeControlEnabling(const bool &value)
{
    setChooseMeControlEnabled(value);
}

bool QMLAdapter::chooseMeControlEnabled(){return _chooseMeControlEnabled;}

void QMLAdapter::setChooseMeControlEnabled(const bool &chooseMeControlEnabled)
{
    if (_chooseMeControlEnabled == chooseMeControlEnabled) return;
    _chooseMeControlEnabled = chooseMeControlEnabled;
    emit chooseMeControlEnabledChanged(_chooseMeControlEnabled);
}

QString QMLAdapter::folderName(){return _folderName;}

void QMLAdapter::setFolderName(const QString &urlFolderName){auto folderName = QUrl(urlFolderName).path(); if (_folderName == folderName) return; _folderName = folderName; _settings->setValue("folderName", _folderName); emit folderNameChanged(_folderName);}

QString QMLAdapter::fileName(){return _fileName;}

void QMLAdapter::setFileName(const QString &urlFileName){auto fileName = QUrl(urlFileName).path(); if (_fileName == fileName) return; _fileName = fileName; _settings->setValue("fileName", _fileName); emit fileNameChanged(_fileName);}

void QMLAdapter::loadSettings()
{
    auto getValue = [this](const QString& key)->SettingValue{
        bool isValid = _settings->contains(key);
        if (!isValid) GUI_DEBUG("[loadSettings] No such key in settings: " << key.toStdString());
        return SettingValue(isValid, _settings->value(key, QVariant()));
    };

    SettingValue temp;
    temp = getValue("fileName");
    if (temp.isValid()) _fileName = temp.value().toString();
    temp = getValue("folderName");
    if (temp.isValid()) _folderName = temp.value().toString();
    temp = getValue("fileNameUrl");
    if (temp.isValid()) _fileNameUrl = temp.value().toString();
    temp = getValue("folderNameUrl");
    if (temp.isValid()) _folderNameUrl = temp.value().toString();
}
