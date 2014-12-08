#ifndef QGCSETTINGS_H
#define QGCSETTINGS_H

#include <QSettings>

class QGCSettings : public QSettings
{
    Q_OBJECT
public:
    explicit QGCSettings(QObject *parent = 0);

signals:

public slots:

};

#endif // QGCSETTINGS_H
