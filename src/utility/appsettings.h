#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QSettings>

#define appSettings AppSettings::instance()

class AppSettings : public QSettings
{
    Q_OBJECT

public:

    static AppSettings *instance();

    void setFormat(const QString &path);

    void init(const QString &fileName, QSettings::Scope scope, const QString &org, const QString &app);

private:
    AppSettings(QObject *parent = nullptr) : QSettings(parent) {}
    static AppSettings *m_instance;
};

#endif // APPSETTINGS_H
