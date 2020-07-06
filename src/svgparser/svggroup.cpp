#include "svggroup.h"

SVGGroup::SVGGroup(QObject *parent) : QObject(parent)
{

}

SVGGroup::Group SVGGroup::groupClass() const
{
    return m_groupClass;
}

QString SVGGroup::groupClassToString() const
{
    switch (m_groupClass) {
    case SVGGroup::Node:
        return "node";
    case SVGGroup::Edge:
        return "edge";
    case SVGGroup::Invalid:
        return QString();
    default:
        return QString();
    }
    return QString();
}

void SVGGroup::setGroupClass(const QString &groupClass)
{
    if(groupClass == "node")
        m_groupClass = SVGGroup::Node;
    else if(groupClass == "edge")
        m_groupClass = SVGGroup::Edge;
    else
        m_groupClass = SVGGroup::Invalid;
}

QString SVGGroup::groupId() const
{
    return m_groupId;
}

void SVGGroup::setGroupId(const QString &groupId)
{
    m_groupId = groupId;
}

QString SVGGroup::title() const
{
    return m_title;
}

void SVGGroup::setTitle(const QString &title)
{
    m_title = title;
}

