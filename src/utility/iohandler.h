#ifndef IOHANDLER_H
#define IOHANDLER_H

#include "utility_global.h"
#include <QFile>
#include <QHash>
#include <QTextStream>

#define ioHandler IOHandler::instance()

//class QQmlEngine;
//class QJSEngine;

class UTILITY_EXPORT IOHandler : QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(IOHandler)

public:

    static IOHandler *instance();
//    static QObject *singletonTypeProvider(QQmlEngine *engine, QJSEngine *scriptEngine);

    bool addNewFileByPath(const QString &name, const QString &path);

    bool openFileToRead(const QString &name);
    bool openFileToWrite(const QString &name);
    void closeFile(const QString &name);

    QFile *currentFile() const;
    void setCurrentFile(const QString &name);

    ~IOHandler();

signals:
    void currentFileChanged();

private:
    IOHandler(QObject *parent = nullptr) : QObject(parent) {}

    QHash<QString, QFile *> m_existensFiles;
    QString m_currentFile;

    static IOHandler *m_instance;
};

#endif // IOHANDLER_H
