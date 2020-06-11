#include "svgreader.h"
#include <QDebug>

SVGReader *SVGReader::m_instance = nullptr;

SVGReader::SVGReader(QObject *parent) : QObject(parent), QXmlStreamReader(), m_inStream(new QTextStream()), m_inFile(nullptr) {}

SVGReader *SVGReader::instance()
{
    if(!m_instance) {
        m_instance  = new SVGReader();
    }
    return m_instance;
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
        pathChanged(m_path);
    }
}

bool SVGReader::setInFile(QFile *inFile)
{
    if(inFile && inFile != m_inFile) {
        m_inFile = inFile;
        if(!m_inFile->open(QIODevice::ReadOnly)) {
            qDebug() << "file " << m_inFile->fileName() << " did not opened!";
            return false;
        }
        return true;
    }
    return false;
}


bool SVGReader::readAll()
{
    if(!m_inFile) {
        setInFile(new QFile(m_path));
    }
    setDevice(m_inFile);
    while(!atEnd() || !hasError()) {
        readNext();
        m_svgText += text().toString() + "\n";
    }
    qDebug() << "svg text file is : " << m_svgText;
    return true;
}

SVGReader::~SVGReader()
{
    m_inFile->close();
    delete m_inFile;
    delete m_inStream;
}
