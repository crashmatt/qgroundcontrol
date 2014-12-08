#include "QGCSettingsGroup.h"
#include <QSettings>
#include <QDebug>

QGCSettingsGroup::QGCSettingsGroup(QString parentPath, QString groupName)
{
    _parentPath = parentPath;
    _groupName = groupName;
}


void QGCSettingsGroup::loadGroup(){
    QSettings settings;
    settings.beginGroup(getGroupPath());
    deserialize(&settings);
}

void QGCSettingsGroup::saveGroup(){
    QSettings settings;
    QString groupPath = getGroupPath();
    settings.beginGroup(groupPath);
    serialize(&settings);
    qDebug() << "Saved settings group: " << groupPath;
}


void QGCSettingsGroup::setGroupName(QString groupName){
    _groupName = groupName;
}

QString QGCSettingsGroup::getGroupPath(){
    return _parentPath + "/" + getGroupName();
}

void QGCSettingsGroup::serialize(QSettings* psettings){

}

void QGCSettingsGroup::deserialize(QSettings* psettings){

}

QString QGCSettingsGroup::getGroupName(void){
    return _groupName;
}

