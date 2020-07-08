#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QSettings>

#define appSettings AppSettings::instance()

class QQmlEngine;
class QJSEngine;

class AppSettings : public QSettings
{
    Q_OBJECT

public:

    static AppSettings *instance();
    static QObject *singletonTypeProvider(QQmlEngine *engine, QJSEngine *scriptEngine);
    static void init(const QString &fileName, QSettings::Format format);

    Q_INVOKABLE QVariant value(const QString &key, const QVariant &defaultValue);
    Q_INVOKABLE void setValue(const QString &key, const QVariant &value);

private:
    AppSettings(QObject *parent = nullptr) : QSettings(parent) {}
    AppSettings(const QString &fileName, QSettings::Format format);
    static AppSettings *m_instance;
};

#endif // APPSETTINGS_H
