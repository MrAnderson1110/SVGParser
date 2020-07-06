#include "iohandler.h"

IOHandler *IOHandler::instance()
{
    if(!m_instance)
        m_instance = new IOHandler();
    return m_instance;
}

bool IOHandler::addNewFileByPath(const QString &name, const QString &path)
{
    if(m_existensFiles[name])
        return false;
    QFile *tempFile = new QFile(path);
    m_existensFiles[name] = tempFile;
    return true;
}

bool IOHandler::openFileToRead(const QString &name)
{
    if(!m_existensFiles[name] || name == m_currentFile)
        return false;
    setCurrentFile(name);
    return currentFile()->open(QIODevice::ReadOnly);
}

bool IOHandler::openFileToWrite(const QString &name)
{
    if(!m_existensFiles[name] || name == m_currentFile)
        return false;
    m_currentFile = name;
    return currentFile()->open(QIODevice::WriteOnly);
}

QFile *IOHandler::currentFile() const
{
    if(m_currentFile.isEmpty())
        return nullptr;
    return m_existensFiles[m_currentFile];
}

void IOHandler::setCurrentFile(const QString &name)
{
    if(currentFile()->isOpen())
        currentFile()->close();
    m_currentFile = name;
    emit currentFileChanged();
}

IOHandler::~IOHandler()
{
    if(currentFile()->isOpen())
        currentFile()->close();
    for(QFile * file : m_existensFiles) {
        delete file;
    }
}
