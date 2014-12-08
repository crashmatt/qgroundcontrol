#ifndef QGCSETTING_H
#define QGCSETTING_H

#include <QObject>

class QGCSetting : public QObject
{
    Q_OBJECT
    QString _settingName;
    QObject *p_data;
public:
    explicit QGCSetting(QObject *parent = NULL, QString name = "default", QObject* pdata = NULL);

signals:

public slots:

};

#endif // QGCSETTING_H
