#include "svgtype.h"
#include "QDebug"
#include <algorithm>
#include <cmath>

QString SVGType::stroke() const
{
    return m_stroke;
}

void SVGType::setStroke(const QString &stroke)
{
    m_stroke = stroke;
}

QString SVGType::fill() const
{
    return m_fill;
}

void SVGType::setFill(const QString &fill)
{
    m_fill = fill;
}

SVGType::Type SVGType::type() const
{
    return m_type;
}

void SVGType::setType(SVGType::Type type)
{
    m_type = type;
}

SVGType::childsType *SVGType::getChildType() const
{
    return m_childType;
}

void SVGType::setType(const QString &type, const int conerCount)
{
    if(type == "polygon" && conerCount == 4) {
        m_type = SVGType::Rectangle;
    }
    if(type == "polygon" && conerCount == 3) {
        m_type = SVGType::Triangle;
    }
    else if(type == "text") {
        m_type = SVGType::Text;
    }
    else if(type == "path") {
        m_type = SVGType::Path;
    }
    else
        m_type = SVGType::Invalid;
}

QString SVGPath::outgoingId() const
{
    return m_outgoingId;
}

void SVGPath::setInOutId(const QString &id)
{
    QStringList temp = id.split(QRegExp("->"));
    m_incomingId = temp[1];
    m_outgoingId = temp[0];
}

QString SVGPath::path() const
{
    return m_path;
}

void SVGPath::setPath(const QString &path)
{
    m_path = path;
    QStringList tempPoints = m_path.split(QRegExp("[ ,]"));
    tempPoints.removeAt(0);
    tempPoints.removeAt(2);
    QList<double> lineXPoints;
    QList<double> lineYPoints;
    bool firstLine = true;
    int linesCount = (tempPoints.length() - 2) / 6;
    for(int i = 0; i < linesCount; ++i) {
        double lastX = 0;
        double lastY = 0;
        SVGPath::line tempLine;
        if(firstLine) {
            lineXPoints.push_back(tempPoints[0].toDouble());
            tempPoints.removeAt(0);
            lineYPoints.push_back(tempPoints[0].toDouble());
            tempPoints.removeAt(0);
        }
        for(int j = 0; j < 3; ++j) {
            lineXPoints.push_back(tempPoints[j].toDouble());
            if(j == 2)
                lastX = tempPoints[j].toDouble();
            tempPoints.removeAt(j);
        }
        for(int j = 0; j < 3; ++j) {
            lineYPoints.push_back(tempPoints[0].toDouble());
            if(j == 2)
                lastY = tempPoints[0].toDouble();
            tempPoints.removeAt(0);
        }
        tempLine.xLine = *(std::min_element(lineXPoints.begin(), lineXPoints.end()));
        tempLine.yLine = *(std::min_element(lineYPoints.begin(), lineYPoints.end()));
        tempLine.width = *(std::max_element(lineXPoints.begin(), lineXPoints.end())) - tempLine.xLine == 0 ?
                    1 : *(std::max_element(lineXPoints.begin(), lineXPoints.end())) - tempLine.xLine;
        tempLine.height = *(std::max_element(lineYPoints.begin(), lineYPoints.end())) - tempLine.yLine == 0 ?
                    1 : *(std::max_element(lineYPoints.begin(), lineYPoints.end())) - tempLine.yLine;

        m_lines.push_back(tempLine);

        lineXPoints.clear();
        lineXPoints.push_back(lastX);
        lineYPoints.clear();
        lineYPoints.push_back(lastY);
        firstLine = false;
    }
}

QString SVGPath::parseLines()
{
    QString temp = "path:[";
    for(int i = 0; i < m_lines.length() - 1; ++i) {
        temp += "{ x:" + QString::number(m_lines[i].xLine) +
                ", y:" + QString::number(m_lines[i].yLine) +
                ", height:" + QString::number(m_lines[i].height) +
                ", width:" + QString::number(m_lines[i].width) + " }, ";
    }
    temp += "{ x:" + QString::number(m_lines.last().xLine) +
            ", y:" + QString::number(m_lines.last().yLine) +
            ", height:" + QString::number(m_lines.last().height) +
            ", width:" + QString::number(m_lines.last().width) + " }]";
    return temp;
}

QString SVGPath::incomingId() const
{
    return m_incomingId;
}

void SVGPolygon::setParametrs(QString str)
{
    QStringList temp = str.split(QRegExp("[ ,]"));
    temp.removeLast();
    m_conerCount = temp.length() / 2;
    QList<double> xParametrs;
    QList<double> yParametrs;
    for(int i = 0; i < temp.length(); i += 2)
        xParametrs.push_back(temp[i].toDouble());
    for(int i = 1; i < temp.length(); i += 2)
        yParametrs.push_back(temp[i].toDouble());
    if(m_conerCount == 4) {
        setRectParametrs(xParametrs, yParametrs);
    }
    else if(m_conerCount == 3) {
        setTriParametrs(xParametrs, yParametrs);
    }
}

double SVGPolygon::x() const
{
    return m_x;
}

double SVGPolygon::y() const
{
    return m_y;
}

double SVGPolygon::height() const
{
    return m_height;
}

double SVGPolygon::width() const
{
    return m_width;
}

void SVGPolygon::setTranslate(const QString &translate)
{
    QStringList temp = translate.split(QRegExp("[),(]"));
    m_translateX = temp[1].toDouble();
    m_translateY = temp[2].toDouble();
}

int SVGPolygon::conerCount() const
{
    return m_conerCount;
}

void SVGPolygon::setRectParametrs(QList<double> &xParams, QList<double> &yParams)
{
    setType(SVGType::Rectangle);
    m_x = *(std::min_element(xParams.begin(), xParams.end())) + m_translateX;
    m_y = *(std::min_element(yParams.begin(), yParams.end())) + m_translateY;
    m_width = *(std::max_element(xParams.begin(), xParams.end())) + m_translateX - m_x;
    m_height = *(std::max_element(yParams.begin(), yParams.end())) + m_translateY - m_y;
}

void SVGPolygon::setTriParametrs(QList<double> &xParams, QList<double> &yParams)
{
    setType(SVGType::Triangle);
    m_x = *(std::min_element(xParams.begin(), xParams.end())) + m_translateX;
    m_y = *(std::min_element(yParams.begin(), yParams.end())) + m_translateY;
    m_width = *(std::max_element(xParams.begin(), xParams.end())) + m_translateX - m_x;
    m_height = *(std::max_element(yParams.begin(), yParams.end())) + m_translateY - m_y;
    if(m_height < m_width) {
        //стрелка указывает вверх или вниз
        if(std::round(xParams[0]) == std::round(xParams[1])) {
            if(xParams [2] > xParams[0])
                m_triDirection = SVGPolygon::Right;
            else
                m_triDirection = SVGPolygon::Left;
        }
        if(std::round(xParams[0]) == std::round(xParams[2])) {
            if(xParams[1] > xParams[0])
                m_triDirection = SVGPolygon::Right;
            else
                m_triDirection = SVGPolygon::Left;
        }
        if(std::round(xParams[1]) == std::round(xParams[2])) {
            if(xParams[0] > xParams[1])
                m_triDirection = SVGPolygon::Right;
            else
                m_triDirection = SVGPolygon::Left;
        }
    }
    else if(m_height > m_width) {
        //стрелка показывает вправо или влево
        if(std::round(yParams[0]) == std::round(yParams[1])) {
            if(yParams[2] > yParams[0])
                m_triDirection = SVGPolygon::Down;
            else
                m_triDirection = SVGPolygon::Up;
        }
        if(std::round(yParams[0]) == std::round(yParams[2])) {
            if(yParams[1] > yParams[0])
                m_triDirection = SVGPolygon::Down;
            else
                m_triDirection = SVGPolygon::Up;
        }
        if(std::round(yParams[1]) == std::round(yParams[2])) {
            if(yParams[0] > yParams[1])
                m_triDirection = SVGPolygon::Down;
            else
                m_triDirection = SVGPolygon::Up;
        }
    }
    else
        m_triDirection = SVGPolygon::Invalid;
}

int SVGPolygon::getId() const
{
    return id;
}

void SVGPolygon::setId(int value)
{
    id = value;
}

double SVGPolygon::translateY() const
{
    return m_translateY;
}

double SVGPolygon::translateX() const
{
    return m_translateX;
}

SVGPolygon::Direction SVGPolygon::triDirection() const
{
    return m_triDirection;
}

double SVGText::x() const
{
    return m_x;
}

void SVGText::setX(double x)
{
    m_x = x;
}

double SVGText::y() const
{
    return m_y;
}

void SVGText::setY(double y)
{
    m_y = y;
}

QString SVGText::textAnchors() const
{
    return m_textAnchors;
}

void SVGText::setTextAnchors(const QString &textAnchors)
{
    m_textAnchors = textAnchors;
}

QString SVGText::fontFamily() const
{
    return m_fontFamily;
}

void SVGText::setFontFamily(const QString &fontFamily)
{
    m_fontFamily = fontFamily;
}

double SVGText::fontSize() const
{
    return m_fontSize;
}

void SVGText::setFontSize(double fontSize)
{
    m_fontSize = fontSize;
}

QString SVGText::text() const
{
    return m_text;
}

void SVGText::setText(const QString &text)
{
    m_text = text;
}

int SVGText::getId() const
{
    return id;
}

void SVGText::setId(int value)
{
    id = value;
}
