#include "svgreader.h"
#include <QDebug>

SVGReader *SVGReader::m_instance = nullptr;

SVGReader::SVGReader(QObject *parent) : QObject(parent), QXmlStreamReader(), m_inFile(nullptr) {}

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

void SVGReader::setSvgText(const QString svgText)
{
    if(svgText != m_svgText) {
        m_svgText = svgText;
        svgTextChanged(m_svgText);
    }
}

void SVGReader::setPath(const QString &path)
{
    if(m_path != path) {
        m_path = path;
        emit pathChanged(m_path);
    }
}

bool SVGReader::setInFile(QFile *inFile)
{
    if(m_inFile) {
        if(m_inFile->isOpen())
            m_inFile->close();
        delete m_inFile;
    }
    m_inFile = inFile;
    if(!m_inFile->open(QIODevice::ReadOnly)) {
        qDebug() << "file " << m_inFile->fileName() << " did not opened: " << m_inFile->errorString();
        return false;
    }
    return true;
}


bool SVGReader::readAll()
{
    if(!m_inFile) {
        setInFile(new QFile(m_path));
        setDevice(m_inFile);
    }
    if(!device()) {
        setDevice(m_inFile);
    }
    //ToDo Метод для чтения всего SVGфайла для отображания на экране
    qDebug() << "svg text file is : " << m_svgText;
    return true;
}

QXmlStreamReader::TokenType SVGReader::readNextComment()
{
    if(!m_inFile) {
        setInFile(new QFile(m_path));
        setDevice(m_inFile);
    }
    if(!device()) {
        setDevice(m_inFile);
    }
    readNext();
    while (tokenType() != QXmlStreamReader::Comment) {
        readNext();
    }
    return  QXmlStreamReader::tokenType();
}

QXmlStreamReader::TokenType SVGReader::readNextElement()
{
    if(!m_inFile) {
        setInFile(new QFile(m_path));
        setDevice(m_inFile);
    }
    if(!device()) {
        setDevice(m_inFile);
    }
    readNext();
    while(tokenType() != QXmlStreamReader::StartElement &&
          tokenType() != QXmlStreamReader::Comment &&
          tokenType() != QXmlStreamReader::EndElement &&
          tokenType() != QXmlStreamReader::EndDocument) {
        readNext();
    }
    return QXmlStreamReader::tokenType();
}


SVGReader::~SVGReader()
{
    m_inFile->close();
    delete m_inFile;
}
