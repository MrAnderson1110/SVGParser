#include "svgreader.h"
#include <QDebug>

SVGReader::SVGReader(QObject *parent) : QObject(parent), QXmlStreamReader(), m_inStream(nullptr) {}

SVGReader *SVGReader::instance()
{
    if(!m_instance) {
        QFile *inFile = new QFile(m_path);
        if(inFile->open(QIODevice::ReadOnly))
            m_inStream = new QTextStream(inFile);
        else
            qDebug() << "file " << m_path << " does not open!";
    }
    return m_instance;
}


bool SVGReader::readAll()
{
    while(!atEnd() || !hasError()) {
        readNext();
        m_svgText = text().toString();
    }
    return true;
}

SVGReader::~SVGReader()
{
    delete m_inStream;
}
