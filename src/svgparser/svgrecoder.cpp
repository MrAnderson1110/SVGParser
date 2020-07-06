#include "svgrecoder.h"
#include <QDebug>

SVGRecoder *SVGRecoder::m_instance = nullptr;

SVGRecoder::SVGRecoder(QObject *parent) : QObject(parent)
{
    m_outFile = new QFile();
}

SVGRecoder *SVGRecoder::instance()
{
    if(!m_instance) {
        m_instance = new SVGRecoder();
    }
    return m_instance;
}

QObject *SVGRecoder::singletonTypeProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    return instance();
}

void SVGRecoder::readAll()
{
    //TO DO: метод для отображения на экране
}

bool SVGRecoder::setOutFile(QFile *file)
{
    if(m_outFile) {
        if(m_outFile->isOpen())
            m_outFile->close();
        delete m_outFile;
    }
    m_outFile = file;
    if(!m_outFile->open(QIODevice::WriteOnly)) {
        setInfo("file " + m_outFile->fileName() + " did not open: " + m_outFile->errorString());
        return false;
    }
    return true;
}

QStringList SVGRecoder::info() const
{
    return m_info;
}

void SVGRecoder::setInfo(const QString &info)
{
    m_info.append(info);
    emit infoChanged();
}

QString SVGRecoder::globalSettingsPath() const
{
    return m_globalSettingsPath;
}

void SVGRecoder::setGlobalSettingsPath(const QString &globalSettingsPath)
{
    m_globalSettingsPath = globalSettingsPath;
}

QString SVGRecoder::textPath() const
{
    return m_textPath;
}

void SVGRecoder::setTextPath(const QString &textPath)
{
    m_textPath = textPath;
}

QString SVGRecoder::arrowsPath() const
{
    return m_arrowsPath;
}

void SVGRecoder::setArrowsPath(const QString &arrowsPath)
{
    m_arrowsPath = arrowsPath;
}

QString SVGRecoder::edgesPath() const
{
    return m_edgesPath;
}

void SVGRecoder::setEdgesPath(const QString &edgesPath)
{
    m_edgesPath = edgesPath;
}

QString SVGRecoder::nodesPath() const
{
    return m_nodesPath;
}

void SVGRecoder::setNodesPath(const QString &nodesPath)
{
    m_nodesPath = nodesPath;
}

void SVGRecoder::parse()
{
    //    QString comment;
    SVGGroup *tempGroup = nullptr;
    while(!svgReader->atEnd() && !svgReader->hasError()) {
        svgReader->readNextElement();
        //        if(svgReader->tokenType() == QXmlStreamReader::Comment) {
        //            comment = svgReader->text().toString();
        //            qDebug() << "create comment element: " << svgReader->text();
        //        }
        if(svgReader->tokenType() == QXmlStreamReader::StartElement && svgReader->name() == "svg") {
            m_globalWidth = svgReader->getAttribute("width").split("pt")[0];
            m_globalHeight = svgReader->getAttribute("height").split("pt")[0];
            setInfo("create main svg element");
        }
        else if(svgReader->tokenType() == QXmlStreamReader::StartElement && svgReader->name() == "g") {
            if(svgReader->getAttribute("class") != "graph") {
                tempGroup = new SVGGroup();
                tempGroup->setGroupClass(svgReader->getAttribute("class"));
                tempGroup->setGroupId(svgReader->getAttribute("id"));
               setInfo("create group element: " + svgReader->getAttribute("id"));
            }
        }
        else if(svgReader->tokenType() == QXmlStreamReader::EndElement && svgReader->name() == "g") {
            if(tempGroup) {
                m_groups.push_back(tempGroup);
                tempGroup = nullptr;
                setInfo("end of group element");
            }
        }
        else if(svgReader->tokenType() == QXmlStreamReader::StartElement && svgReader->name() == "title") {
            if(tempGroup) {
                tempGroup->setTitle(svgReader->readElementText());
                setInfo("create title element: " + svgReader->readElementText());
            }
        }
        //        else if(svgReader->tokenType() == QXmlStreamReader::EndElement && svgReader->name() == "title") {
        //            qDebug() << "end of title element";
        //        }
        else if(svgReader->tokenType() == QXmlStreamReader::StartElement && svgReader->name() == "polygon") {
            if(tempGroup) {
                SVGPolygon *tempPolygon = new SVGPolygon();
                //методы установки значений;
                tempPolygon->setTranslate(svgReader->getAttribute("transform"));
                tempPolygon->setParametrs(svgReader->getAttribute("points"));
                tempPolygon->setFill(svgReader->getAttribute("fill"));
                tempPolygon->setStroke(svgReader->getAttribute("stroke"));
                tempPolygon->getChildType()->m_svgPolygon = tempPolygon;
                tempPolygon->setId(tempGroup->title().toInt());
                tempGroup->push(tempPolygon);
                setInfo("create polygon element");
            }
        }
        //        else if(svgReader->tokenType() == QXmlStreamReader::EndElement && svgReader->name() == "polygon") {
        //            qDebug() << "end of polygon element";
        //        }
        else if(svgReader->tokenType() == QXmlStreamReader::StartElement && svgReader->name() == "text") {
            if(tempGroup) {
                SVGText *tempText = new SVGText();
                //методы утановки значений
                tempText->setX(svgReader->getAttribute("x").toDouble());
                tempText->setY(svgReader->getAttribute("y").toDouble());
                tempText->setFontSize(svgReader->getAttribute("font-size").toDouble());
                tempText->setFontFamily(svgReader->getAttribute("font-family").split(",")[0]);
                tempText->setTextAnchors(svgReader->getAttribute("text-anchor"));
                tempText->setType(svgReader->name().toString());
                tempText->setFill(svgReader->getAttribute("fill"));
                tempText->setStroke(svgReader->getAttribute("stroke"));
                tempText->setText(svgReader->readElementText());
                tempText->getChildType()->m_svgText = tempText;
                tempText->setId(tempGroup->title().toInt());
                tempGroup->push(tempText);
                setInfo("create text element " + svgReader->readElementText());
            }
        }
        //        else if(svgReader->tokenType() == QXmlStreamReader::EndElement && svgReader->name() == "text") {
        //            qDebug() << "end of text element";
        //        }
        else if(svgReader->tokenType() == QXmlStreamReader::StartElement && svgReader->name() == "path") {
            if(tempGroup) {
                SVGPath *tempPath = new SVGPath();
                //методы установки значений
                tempPath->setType(svgReader->name().toString());
                tempPath->setPath(svgReader->getAttribute("d"));
                tempPath->setInOutId(tempGroup->title());
                tempPath->setFill(svgReader->getAttribute("fill"));
                tempPath->setStroke(svgReader->getAttribute("stroke"));
                tempPath->getChildType()->m_svgPath = tempPath;
                tempGroup->push(tempPath);
                setInfo("create path element");
            }
        }
        //        else if(svgReader->tokenType() == QXmlStreamReader::EndElement && svgReader->name() == "path") {
        //            qDebug() << "end of path element";
        //        }

    }
}

void SVGRecoder::record()
{
    setInfo("start recording global settings");

    if(QFile::exists(m_globalSettingsPath))
        QFile::remove(m_globalSettingsPath);
    m_outFile->setFileName(m_globalSettingsPath);
    if(!m_outFile->open(QIODevice::WriteOnly)) {
        setInfo("can not open file" + m_outFile->fileName() + ":" + m_outFile->errorString());
        return;
    }
    m_stream.setDevice(m_outFile);
    m_stream << "[ { id: \"main_window\", width:" << m_globalWidth << ", height: " << m_globalHeight << " } ]";
    m_stream.flush();

    setInfo("start recording nodes");

    if(QFile::exists(m_nodesPath))
        QFile::remove(m_nodesPath);
    m_outFile->setFileName(m_nodesPath);
    if(!m_outFile->open(QIODevice::WriteOnly)) {
        setInfo("can not open file" + m_outFile->fileName() + ":" + m_outFile->errorString());
        return;
    }
    m_stream << " [ \n";
    for(int i = 0; i < m_groups.length(); ++i) {
        if(m_groups[i]->groupClass() == SVGGroup::Node) {
            for(int j = 0; j < m_groups[i]->length(); ++j) {
                if(m_groups[i]->at(j)->type() == SVGType::Rectangle) {
                    SVGPolygon *rectangle = m_groups[i]->at(j)->getChildType()->m_svgPolygon;
                    setInfo(QString::number(i) + ": " + "recording rectangle ref: " + m_groups[i]->groupId());
                    if(rectangle->fill().isEmpty() && rectangle->stroke().isEmpty())
                        m_stream << "{ type:\"polygon\", id:" << rectangle->getId() << ", ref:\"" << m_groups[i]->groupId() << "\", x:" << rectangle->x() << ", y:" << rectangle->y() <<
                                    ", height:" << rectangle->height() << ", width:" << rectangle->width() << ", edges_num:" << rectangle->conerCount() << " },\n";
                    if(rectangle->fill().isEmpty() && !rectangle->stroke().isEmpty())
                        m_stream << "{ type:\"polygon\", id:" << rectangle->getId() << ", ref:\"" << m_groups[i]->groupId() << "\", stroke:\"" << rectangle->stroke() << "\", x:" << rectangle->x() << ", y:" << rectangle->y() <<
                                    ", height:" << rectangle->height() << ", width:" << rectangle->width() << ", edges_num:" << rectangle->conerCount() << " },\n";
                    if(!rectangle->fill().isEmpty() && rectangle->stroke().isEmpty())
                        m_stream << "{ type:\"polygon\", id:" << rectangle->getId() << ", ref:\"" << m_groups[i]->groupId() << "\", fill:\"" << rectangle->fill() << "\", x:" << rectangle->x() << ", y:" << rectangle->y() <<
                                    ", height:" << rectangle->height() << ", width:" << rectangle->width() << ", edges_num:" << rectangle->conerCount() << " },\n";
                    if(!rectangle->fill().isEmpty() && !rectangle->stroke().isEmpty())
                        m_stream << "{ type:\"polygon\", id:" << rectangle->getId() << ", ref:\"" << m_groups[i]->groupId() << "\", fill:\"" << rectangle->fill() << "\", stroke:\"" << rectangle->stroke()
                                 << "\", x:" << rectangle->x() << ", y:" << rectangle->y() << ", height:" << rectangle->height()
                                 << ", width:" << rectangle->width() << ", edges_num:" << rectangle->conerCount() << " },\n";
                    m_stream.flush();
                }
            }
        }
    }
    m_stream << " ]";
    m_stream.flush();

    setInfo("start recording text");

    if(QFile::exists(m_textPath))
        QFile::remove(m_textPath);
    m_outFile->setFileName(m_textPath);
    if(!m_outFile->open(QIODevice::WriteOnly)) {
        setInfo("can not open file" + m_outFile->fileName() + ":" + m_outFile->errorString());
        return;
    }
    m_stream << " [ \n";
    for(int i = 0; i < m_groups.length(); ++i) {
        if(m_groups[i]->groupClass() == SVGGroup::Node) {
            for(int j = 0; j < m_groups[i]->length(); ++j) {
                if(m_groups[i]->at(j)->type() == SVGType::Text) {
                    SVGText *text = m_groups[i]->at(j)->getChildType()->m_svgText;
                    setInfo(QString::number(i) + ": " + "recording text id: " + m_groups[i]->groupId());
                    if(text->fill().isEmpty() && text->stroke().isEmpty())
                        m_stream << "{ type:\"text\", id:" << text->getId() << ", ref:\"" << m_groups[i]->groupId() << "\", x:" << text->x() << ", y:" << text->y() <<
                                    ", fontFlamily:\"" << text->fontFamily() << "\", fontSize:" << text->fontSize() << ", position:\"" << text->textAnchors() <<
                                    "\", text:\"" << text->text() << "\" },\n";
                    if(text->fill().isEmpty() && !text->stroke().isEmpty())
                        m_stream << "{ type:\"text\", id:" << text->getId() << ", ref:\"" << m_groups[i]->groupId() << "\", stroke:\"" << text->stroke() << "\", x:" << text->x() << ", y:" << text->y() <<
                                    ", fontFlamily:\"" << text->fontFamily() << "\", fontSize:" << text->fontSize() << ", position:\"" << text->textAnchors() <<
                                    "\", text:\"" << text->text() << "\" },\n";
                    if(!text->fill().isEmpty() && text->stroke().isEmpty())
                        m_stream << "{ type:\"text\", id:" << text->getId() << ", ref:\"" << m_groups[i]->groupId() << "\", fill:\"" << text->fill() << "\", x:" << text->x() << ", y:" << text->y() <<
                                    ", fontFlamily:\"" << text->fontFamily() << "\", fontSize:" << text->fontSize() << ", position:\"" << text->textAnchors() <<
                                    "\", text:\"" << text->text() << "\" },\n";
                    if(!text->fill().isEmpty() && !text->stroke().isEmpty())
                        m_stream << "{ type:\"text\", id:" << text->getId() << ", ref:\"" << m_groups[i]->groupId() << "\", fill:\"" << text->fill() << "\", stroke:\"" << text->stroke() << "\", x:" << text->x() << ", y:" << text->y() <<
                                    ", fontFlamily:\"" << text->fontFamily() << "\", fontSize:" << text->fontSize() << ", position:\"" << text->textAnchors() <<
                                    "\", text:\"" << text->text() << "\" },\n";
                    m_stream.flush();
                }
            }
        }
    }
    m_stream << " ]";
    m_stream.flush();

    setInfo("start recording edges");

    if(QFile::exists(m_edgesPath))
        QFile::remove(m_edgesPath);
    m_outFile->setFileName(m_edgesPath);
    if(!m_outFile->open(QIODevice::WriteOnly)) {
        setInfo("can not open file" + m_outFile->fileName() + ":" + m_outFile->errorString());
        return;
    }
    m_stream << " [ \n";
    for(int i = 0; i < m_groups.length(); ++i) {
        if(m_groups[i]->groupClass() == SVGGroup::Edge) {
            for(int j = 0; j < m_groups[i]->length(); ++j) {
                if(m_groups[i]->at(j)->type() == SVGType::Path) {
                    SVGPath *path = m_groups[i]->at(j)->getChildType()->m_svgPath;
                    setInfo(QString::number(i) + ": " + "recording path id: " + m_groups[i]->groupId());
                    if(path->fill().isEmpty() && path->stroke().isEmpty())
                        m_stream << "{ type:\"path\", id:\"" << m_groups[i]->groupId() << "\", " << path->parseLines() << ", incomingId:" << path->incomingId() << ", outgoingId:" << path->outgoingId() << " },\n";
                    if(path->fill().isEmpty() && !path->stroke().isEmpty())
                        m_stream << "{ type:\"path\", id:\"" << m_groups[i]->groupId() << "\", " << path->parseLines() << ", incomingId:" << path->incomingId() << ", outgoingId:" << path->outgoingId() <<
                                    ", stroke:\"" << path->stroke() << "\" },\n";
                    if(!path->fill().isEmpty() && path->stroke().isEmpty())
                        m_stream << "{ type:\"path\", id:\"" << m_groups[i]->groupId() << "\", " << path->parseLines() << ", incomingId:" << path->incomingId() << ", outgoingId:" << path->outgoingId() <<
                                    ", fill:\"" << path->fill() << "\" },\n";
                    if(!path->fill().isEmpty() && !path->stroke().isEmpty())
                        m_stream << "{ type:\"path\", id:\"" << m_groups[i]->groupId() << "\", " << path->parseLines() << ", incomingId:" << path->incomingId() << ", outgoingId:" << path->outgoingId() <<
                                    ", fill:\"" << path->fill() << "\", stroke:\"" << path->stroke() << "\" },\n";
                    m_stream.flush();
                }
            }
        }
    }
    m_stream << " ]";
    m_stream.flush();

    setInfo("start recording arrows");

    if(QFile::exists(m_arrowsPath))
        QFile::remove(m_arrowsPath);
    m_outFile->setFileName(m_arrowsPath);
    if(!m_outFile->open(QIODevice::WriteOnly)) {
        setInfo("can not open file" + m_outFile->fileName() + ":" + m_outFile->errorString());
        return;
    }
    m_stream << " [ \n";
    for(int i = 0; i < m_groups.length(); ++i) {
        if(m_groups[i]->groupClass() == SVGGroup::Edge) {
            for(int j = 0; j < m_groups[i]->length(); ++j) {
                if(m_groups[i]->at(j)->type() == SVGType::Triangle) {
                    SVGPolygon *triengle = m_groups[i]->at(j)->getChildType()->m_svgPolygon;
                    setInfo(QString::number(i) + ": " + "recording triengle id: " + m_groups[i]->groupId());
                    if(triengle->fill().isEmpty() && triengle->stroke().isEmpty())
                        m_stream << "{ type:\"polygon\", id:\"" << m_groups[i]->groupId() << "\", x:" << triengle->x() << ", y:" << triengle->y() << ", rotation:" << triengle->triDirection() <<
                                    ", height:" << triengle->height() << ", width:" << triengle->width() << ", edges_num:" << triengle->conerCount() << " },\n";
                    if(triengle->fill().isEmpty() && !triengle->stroke().isEmpty())
                        m_stream << "{ type:\"polygon\", id:\"" << m_groups[i]->groupId() << "\", stroke:\"" << triengle->stroke() << "\", x:" << triengle->x() << ", y:" << triengle->y() << ", rotation:" << triengle->triDirection() <<
                                    ", height:" << triengle->height() << ", width:" << triengle->width() << ", edges_num:" << triengle->conerCount() << " },\n";
                    if(!triengle->fill().isEmpty() && triengle->stroke().isEmpty())
                        m_stream << "{ type:\"polygon\", id:\"" << m_groups[i]->groupId() << "\", fill:\"" << triengle->fill() << "\", x:" << triengle->x() << ", y:" << triengle->y() << ", rotation:" << triengle->triDirection() <<
                                    ", height:" << triengle->height() << ", width:" << triengle->width() << ", edges_num:" << triengle->conerCount() << " },\n";
                    if(!triengle->fill().isEmpty() && !triengle->stroke().isEmpty())
                        m_stream << "{ type:\"polygon\", id:\"" << m_groups[i]->groupId() << "\", fill:\"" << triengle->fill() << "\", stroke:\"" << triengle->stroke() << "\", rotation:" << triengle->triDirection()
                                 << ", x:" << triengle->x() << ", y:" << triengle->y() << ", height:" << triengle->height()
                                 << ", width:" << triengle->width() << ", edges_num:" << triengle->conerCount() << " },\n";
                    m_stream.flush();
                }
            }
        }
    }

//    for(int i = 0; i < m_groups.length(); ++i) {
//        switch (m_groups[i]->groupClass()) {
//        case SVGGroup::Node: {
//            for(int j = 0; j < m_groups[i]->length(); ++j) {
//                switch (m_groups[i]->at(j)->type()) {
//                case SVGType::Rectangle: {
//                    m_outFile->close();
//                    if(QFile::exists(m_nodesPath))
//                        QFile::remove(m_nodesPath);
//                    m_outFile->setFileName(m_nodesPath);
//                    if(!m_outFile->open(QIODevice::WriteOnly)) {
//                        qDebug() << "can not open file" << m_outFile->fileName() << ":" << m_outFile->errorString();
//                        return;
//                    }
//                    SVGPolygon *rectangle = m_groups[i]->at(j)->getChildType()->m_svgPolygon;
//                    qDebug() << i << ": " << "recording rectangle ref: " << m_groups[i]->groupId();
//                    if(rectangle->fill().isEmpty() && rectangle->stroke().isEmpty())
//                        m_stream << "{ type:\"polygon\", id:" << rectangle->getId() << ", ref:\"" << m_groups[i]->groupId() << "\", x:" << rectangle->x() << ", y:" << rectangle->y() <<
//                                    ", height:" << rectangle->height() << ", width:" << rectangle->width() << ", edges_num:" << rectangle->conerCount() << " },\n";
//                    if(rectangle->fill().isEmpty() && !rectangle->stroke().isEmpty())
//                        m_stream << "{ type:\"polygon\", id:" << rectangle->getId() << ", ref:\"" << m_groups[i]->groupId() << "\", stroke:\"" << rectangle->stroke() << "\", x:" << rectangle->x() << ", y:" << rectangle->y() <<
//                                    ", height:" << rectangle->height() << ", width:" << rectangle->width() << ", edges_num:" << rectangle->conerCount() << " },\n";
//                    if(!rectangle->fill().isEmpty() && rectangle->stroke().isEmpty())
//                        m_stream << "{ type:\"polygon\", id:" << rectangle->getId() << ", ref:\"" << m_groups[i]->groupId() << "\", fill:\"" << rectangle->fill() << "\", x:" << rectangle->x() << ", y:" << rectangle->y() <<
//                                    ", height:" << rectangle->height() << ", width:" << rectangle->width() << ", edges_num:" << rectangle->conerCount() << " },\n";
//                    if(!rectangle->fill().isEmpty() && !rectangle->stroke().isEmpty())
//                        m_stream << "{ type:\"polygon\", id:" << rectangle->getId() << ", ref:\"" << m_groups[i]->groupId() << "\", fill:\"" << rectangle->fill() << "\", stroke:\"" << rectangle->stroke()
//                                 << "\", x:" << rectangle->x() << ", y:" << rectangle->y() << ", height:" << rectangle->height()
//                                 << ", width:" << rectangle->width() << ", edges_num:" << rectangle->conerCount() << " },\n";
//                    m_stream.flush();
//                    break;
//                }
//                case SVGType::Text: {
//                    m_outFile->close();
//                    if(QFile::exists(m_textPath))
//                        QFile::remove(m_textPath);
//                    m_outFile->setFileName(m_textPath);
//                    if(!m_outFile->open(QIODevice::WriteOnly)) {
//                        qDebug() << "can not open file" << m_outFile->fileName() << ":" << m_outFile->errorString();
//                        return;
//                    }
//                    SVGText *text = m_groups[i]->at(j)->getChildType()->m_svgText;
//                    qDebug() << i << ": " << "recording text id: " << m_groups[i]->groupId();
//                    if(text->fill().isEmpty() && text->stroke().isEmpty())
//                        m_stream << "{ type:\"text\", id:" << text->getId() << ", ref:\"" << m_groups[i]->groupId() << "\", x:" << text->x() << ", y:" << text->y() <<
//                                    ", fontFlamily:\"" << text->fontFamily() << "\", fontSize:" << text->fontSize() << ", position:\"" << text->textAnchors() <<
//                                    "\", text:\"" << text->text() << "\" },\n";
//                    if(text->fill().isEmpty() && !text->stroke().isEmpty())
//                        m_stream << "{ type:\"text\", id:" << text->getId() << ", ref:\"" << m_groups[i]->groupId() << "\", stroke:\"" << text->stroke() << "\", x:" << text->x() << ", y:" << text->y() <<
//                                    ", fontFlamily:\"" << text->fontFamily() << "\", fontSize:" << text->fontSize() << ", position:\"" << text->textAnchors() <<
//                                    "\", text:\"" << text->text() << "\" },\n";
//                    if(!text->fill().isEmpty() && text->stroke().isEmpty())
//                        m_stream << "{ type:\"text\", id:" << text->getId() << ", ref:\"" << m_groups[i]->groupId() << "\", fill:\"" << text->fill() << "\", x:" << text->x() << ", y:" << text->y() <<
//                                    ", fontFlamily:\"" << text->fontFamily() << "\", fontSize:" << text->fontSize() << ", position:\"" << text->textAnchors() <<
//                                    "\", text:\"" << text->text() << "\" },\n";
//                    if(!text->fill().isEmpty() && !text->stroke().isEmpty())
//                        m_stream << "{ type:\"text\", id:" << text->getId() << ", ref:\"" << m_groups[i]->groupId() << "\", fill:\"" << text->fill() << "\", stroke:\"" << text->stroke() << "\", x:" << text->x() << ", y:" << text->y() <<
//                                    ", fontFlamily:\"" << text->fontFamily() << "\", fontSize:" << text->fontSize() << ", position:\"" << text->textAnchors() <<
//                                    "\", text:\"" << text->text() << "\" },\n";
//                    m_stream.flush();
//                    break;
//                }
//                default:
//                    break;
//                }
//            }
//            break;
//        }
//        case SVGGroup::Edge: {
//            for(int j = 0; j < m_groups[i]->length(); ++j) {
//                switch (m_groups[i]->at(j)->type()) {
//                case SVGType::Triangle: {
//                    m_outFile->close();
//                    if(QFile::exists(m_arrowsPath))
//                        QFile::remove(m_arrowsPath);
//                    m_outFile->setFileName(m_arrowsPath);
//                    if(!m_outFile->open(QIODevice::WriteOnly)) {
//                        qDebug() << "can not open file" << m_outFile->fileName() << ":" << m_outFile->errorString();
//                        return;
//                    }
//                    SVGPolygon *triengle = m_groups[i]->at(j)->getChildType()->m_svgPolygon;
//                    qDebug() << i << ": " << "recording triengle id: " << m_groups[i]->groupId();
//                    if(triengle->fill().isEmpty() && triengle->stroke().isEmpty())
//                        m_stream << "{ type:\"polygon\", id:\"" << m_groups[i]->groupId() << "\", x:" << triengle->x() << ", y:" << triengle->y() << ", rotation:" << triengle->triDirection() <<
//                                    ", height:" << triengle->height() << ", width:" << triengle->width() << ", edges_num:" << triengle->conerCount() << " },\n";
//                    if(triengle->fill().isEmpty() && !triengle->stroke().isEmpty())
//                        m_stream << "{ type:\"polygon\", id:\"" << m_groups[i]->groupId() << "\", stroke:\"" << triengle->stroke() << "\", x:" << triengle->x() << ", y:" << triengle->y() << ", rotation:" << triengle->triDirection() <<
//                                    ", height:" << triengle->height() << ", width:" << triengle->width() << ", edges_num:" << triengle->conerCount() << " },\n";
//                    if(!triengle->fill().isEmpty() && triengle->stroke().isEmpty())
//                        m_stream << "{ type:\"polygon\", id:\"" << m_groups[i]->groupId() << "\", fill:\"" << triengle->fill() << "\", x:" << triengle->x() << ", y:" << triengle->y() << ", rotation:" << triengle->triDirection() <<
//                                    ", height:" << triengle->height() << ", width:" << triengle->width() << ", edges_num:" << triengle->conerCount() << " },\n";
//                    if(!triengle->fill().isEmpty() && !triengle->stroke().isEmpty())
//                        m_stream << "{ type:\"polygon\", id:\"" << m_groups[i]->groupId() << "\", fill:\"" << triengle->fill() << "\", stroke:\"" << triengle->stroke() << "\", rotation:" << triengle->triDirection()
//                                 << ", x:" << triengle->x() << ", y:" << triengle->y() << ", height:" << triengle->height()
//                                 << ", width:" << triengle->width() << ", edges_num:" << triengle->conerCount() << " },\n";
//                    m_stream.flush();
//                    break;
//                }
//                case SVGType::Path: {
//                    m_outFile->close();
//                    if(QFile::exists(m_edgesPath))
//                        QFile::remove(m_edgesPath);
//                    m_outFile->setFileName(m_edgesPath);
//                    if(!m_outFile->open(QIODevice::WriteOnly)) {
//                        qDebug() << "can not open file" << m_outFile->fileName() << ":" << m_outFile->errorString();
//                        return;
//                    }
//                    SVGPath *path = m_groups[i]->at(j)->getChildType()->m_svgPath;
//                    qDebug() << i << ": " << "recording path id: " << m_groups[i]->groupId();
//                    if(path->fill().isEmpty() && path->stroke().isEmpty())
//                        m_stream << "{ type:\"path\", id:\"" << m_groups[i]->groupId() << "\", " << path->parseLines() << ", incomingId:" << path->incomingId() << ", outgoingId:" << path->outgoingId() << " },\n";
//                    if(path->fill().isEmpty() && !path->stroke().isEmpty())
//                        m_stream << "{ type:\"path\", id:\"" << m_groups[i]->groupId() << "\", " << path->parseLines() << ", incomingId:" << path->incomingId() << ", outgoingId:" << path->outgoingId() <<
//                                    ", stroke:\"" << path->stroke() << "\" },\n";
//                    if(!path->fill().isEmpty() && path->stroke().isEmpty())
//                        m_stream << "{ type:\"path\", id:\"" << m_groups[i]->groupId() << "\", " << path->parseLines() << ", incomingId:" << path->incomingId() << ", outgoingId:" << path->outgoingId() <<
//                                    ", fill:\"" << path->fill() << "\" },\n";
//                    if(!path->fill().isEmpty() && !path->stroke().isEmpty())
//                        m_stream << "{ type:\"path\", id:\"" << m_groups[i]->groupId() << "\", " << path->parseLines() << ", incomingId:" << path->incomingId() << ", outgoingId:" << path->outgoingId() <<
//                                    ", fill:\"" << path->fill() << "\", stroke:\"" << path->stroke() << "\" },\n";
//                    m_stream.flush();
//                    break;
//                }
//                default:
//                    break;
//                }
//            }
//            break;

//            break;
//        }
//        default:
//            break;
//        }
//    }
    m_stream << " ]";
    m_stream.flush();
    setInfo("record finished");
}

SVGRecoder::~SVGRecoder()
{
    m_outFile->close();
    delete m_outFile;
}


