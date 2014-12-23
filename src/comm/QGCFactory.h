#ifndef QGCFACTORY_H
#define QGCFACTORY_H

class QGCFactory
{
public:
    template<typename T>
    void registerClass()
    {
        constructors().insert( T::staticMetaObject.className(), &constructorHelper<T> );
    }

    QObject* createObject( const QByteArray& className, QGCSettingsGroup* pparentGroup, QString name )
    {
        Constructor constructor = constructors().value( className );
        if ( constructor == NULL )
            return NULL;
        return (*constructor)( pparentGroup, name );
    }

private:
    typedef QObject* (*Constructor)( QGCSettingsGroup* pparentGroup, QString name );

    template<typename T>
    QObject* constructorHelper( QGCSettingsGroup* pparentGroup, QString name )
    {
        return new T( pparentGroup, name );
    }

    QMap<QByteArray, Constructor>& constructors()
    {
        static QMap<QByteArray, Constructor> instance;
        return instance;
    }
};

#endif // QGCFACTORY_H
