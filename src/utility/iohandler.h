#ifndef IOHANDLER_H
#define IOHANDLER_H

#include "utility_global.h"
#include <QFile>
#include <QHash>
#include <QTextStream>

#define ioHandler IOHandler::instance()

//class QQmlEngine;
//class QJSEngine;

class UTILITY_EXPORT IOHandler : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(IOHandler)

public:

    static IOHandler *instance();
//    static QObject *singletonTypeProvider(QQmlEngine *engine, QJSEngine *scriptEngine);

    QFile *openFileToRead(const QString &name);
    QFile *openFileToWrite(const QString &name);
    void closeFile(const QString &name);

    QFile *currentFile() const;
    void setCurrentFile(const QString &name, QIODevice::OpenModeFlag mode);

    bool isOpen() const;

    QString errorString() const;

    ~IOHandler();

signals:
    void currentFileChanged();

public slots:

    void addNewFileByPath(QString path);

private:
    IOHandler(QObject *parent = nullptr);

    QHash<QString, QFile *> m_existensFiles;
    QString m_currentFile;

    static IOHandler *m_instance;
};

#endif // IOHANDLER_H
