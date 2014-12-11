#ifndef QGCSETTINGSGROUP_H
#define QGCSETTINGSGROUP_H

#include <QObject>
#include <QList>
#include <QSettings>
#include "QGCSetting.h"

class QGCSettingsGroup
{
    QString _parentPath;
    QString _groupName;

    QString getGroupPath();

protected:
    virtual void serialize(QSettings* psettings);
    virtual void deserialize(QSettings* psettings);
    virtual QString getGroupName(void);

public:
    explicit QGCSettingsGroup(QString parentPath, QString groupName = "default");

    void setGroupName(QString groupName);
    void loadGroup();
    void saveGroup();
signals:

public slots:

};

#endif // QGCSETTINGSGROUP_H
