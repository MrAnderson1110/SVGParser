#include "iohandler.h"

IOHandler *IOHandler::m_instance = nullptr;

IOHandler *IOHandler::instance()
{
    if(!m_instance)
        m_instance = new IOHandler();
    return m_instance;
}

void IOHandler::addNewFileByPath(QString path)
{
    if(path.isEmpty() || path.isNull()) {
        qFatal("IOHandler::addNewFileByPath(): can not add file by empty path");
    }
    QFile *tempFile = new QFile(path);
    m_existensFiles[path] = tempFile;
}

IOHandler::IOHandler(QObject *parent) : QObject(parent) { }

QFile *IOHandler::openFileToRead(const QString &path)
{
    if(!m_existensFiles[path])
        qFatal("SVGReader::readNextComment(): file must be added to ioHandler before using");
    if(path == m_currentFile)
        return currentFile();
    setCurrentFile(path, QIODevice::ReadOnly);
    return currentFile()->open(QIODevice::ReadOnly) ? currentFile() : nullptr;
}

QFile *IOHandler::openFileToWrite(const QString &path)
{
    if(!m_existensFiles[path])
        qFatal("SVGReader::readNextComment(): file must be added to ioHandler before using");
    if(path == m_currentFile)
        return currentFile();
    setCurrentFile(path, QIODevice::WriteOnly);
    return currentFile()->open(QIODevice::WriteOnly) ? currentFile() : nullptr;
}

QFile *IOHandler::currentFile() const
{
    if(m_currentFile.isEmpty())
        return nullptr;
    return m_existensFiles[m_currentFile];
}

void IOHandler::setCurrentFile(const QString &path, QIODevice::OpenModeFlag mode)
{
    if(isOpen())
        currentFile()->close();
    if(mode == QIODevice::WriteOnly && QFile::exists(path))
        QFile::remove(path);
    m_currentFile = path;
    emit currentFileChanged();
}

bool IOHandler::isOpen() const
{
    if(currentFile() && currentFile()->isOpen())
        return true;
    else return false;
}

QString IOHandler::errorString() const
{
    return currentFile()->errorString();
}

IOHandler::~IOHandler()
{
    if(isOpen())
        currentFile()->close();
    for(QFile * file : m_existensFiles) {
        delete file;
    }
}
