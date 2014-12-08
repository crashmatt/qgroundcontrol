#include "QGCSetting.h"

QGCSetting::QGCSetting(QObject *parent, QString name, QObject* pdata) :
    QObject(parent)
{
    p_data = pdata;
    _settingName = name;
}
