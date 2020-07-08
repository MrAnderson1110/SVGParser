#include "appsettings.h"

AppSettings *AppSettings::m_instance = nullptr;

AppSettings *AppSettings::instance()
{
    Q_ASSERT_X(m_instance != nullptr,
               "AppSettings::instance()",
               "to uset AppSettings, you must init it before");
    return m_instance;
}

QObject *AppSettings::singletonTypeProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    return instance();
}

void AppSettings::init(const QString &fileName, QSettings::Format format)
{
    m_instance = new AppSettings(fileName, format);
}

QVariant AppSettings::value(const QString &key, const QVariant &defaultValue)
{
    return QSettings::value(key, defaultValue);
}

void AppSettings::setValue(const QString &key, const QVariant &value)
{
    QSettings::setValue(key, value);
}

AppSettings::AppSettings(const QString &fileName, QSettings::Format format) : QSettings(fileName, format)
{

}




