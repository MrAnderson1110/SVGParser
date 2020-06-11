#include "svgreader.h"
#include <QDebug>

SVGReader *SVGReader::m_instance = nullptr;

SVGReader::SVGReader(QObject *parent) : QObject(parent), QXmlStreamReader(), m_inStream(nullptr), m_inFile(nullptr) {}

SVGReader *SVGReader::instance()
{
    if(!m_instance) {
        SVGReader();
    }
    return m_instance;
}

void SVGReader::setSvgText(const QString &svgText)
{
    if(svgText != m_svgText) {
        m_svgText = svgText;
        svgTextChanged(m_svgText);
    }
}

void SVGReader::setPath(const QString &inPath)
{
    if(m_path != inPath) {
        m_path = inPath;
        pathChanged(m_path);
    }
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
