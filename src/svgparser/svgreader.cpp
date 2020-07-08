#include "svgreader.h"
#include <QDebug>
#include "iohandler.h"

SVGReader *SVGReader::m_instance = nullptr;

SVGReader::SVGReader(QObject *parent) : QObject(parent), QXmlStreamReader()
{
    connect(this, &SVGReader::pathChanged, IOHandler::instance(), &IOHandler::addNewFileByPath);
}

SVGReader *SVGReader::instance()
{
    if(!m_instance) {
        m_instance  = new SVGReader();
    }
    return m_instance;
}

QString SVGReader::getAttribute(const QString &value)
{
    return attributes().value(value).toString();
}

QString SVGReader::svgText() const
{
    return m_svgText;
}

void SVGReader::setSvgText(const QString svgText)
{
    if(svgText != m_svgText) {
        m_svgText = svgText;
        svgTextChanged(m_svgText);
    }
}

QString SVGReader::path() const
{
    return m_path;
}

void SVGReader::setPath(const QString &path)
{
    if(m_path != path) {
        m_path = path;
        emit pathChanged(m_path);
    }
}

bool SVGReader::readAll()
{
    //ToDo Метод для чтения всего SVGфайла для отображания на экране
    qDebug() << "svg text file is : " << m_svgText;
    return true;
}

QXmlStreamReader::TokenType SVGReader::readNextComment()
{
    if(!device())
        setDevice(ioHandler->openFileToRead(m_path));
    readNext();
    while (tokenType() != QXmlStreamReader::Comment) {
        readNext();
    }
    return  QXmlStreamReader::tokenType();
}

QXmlStreamReader::TokenType SVGReader::readNextElement()
{
    if(!device())
        setDevice(ioHandler->openFileToRead(m_path));
    readNext();
    while(tokenType() != QXmlStreamReader::StartElement &&
          tokenType() != QXmlStreamReader::Comment &&
          tokenType() != QXmlStreamReader::EndElement &&
          tokenType() != QXmlStreamReader::EndDocument) {
        readNext();
    }
    return QXmlStreamReader::tokenType();
}
