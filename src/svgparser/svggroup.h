#ifndef SVGGROUP_H
#define SVGGROUP_H

#include <QObject>
#include <QList>
#include "svgtype.h"

class SVGType;

class SVGGroup : public QObject
{
    Q_OBJECT

public:
    enum Group {
        Node,
        Edge,
        Invalid
    };
    explicit SVGGroup(QObject *parent = nullptr);

    SVGGroup::Group groupClass() const;
    QString groupClassToString() const;
    void setGroupClass(const QString &groupClass);

    QString groupId() const;
    void setGroupId(const QString &groupId);

    void push(SVGType *type) { m_types.push_back(type); }
    int length() const { return m_types.length(); }
    SVGType *at(int pos) const { return m_types.at(pos); }
    SVGType *last() const { return m_types.last(); }

    QString title() const;
    void setTitle(const QString &title);

signals:

private:
    QString m_title;
    QString m_groupId;
    Group m_groupClass;
    QList<SVGType *> m_types;
};

#endif // SVGGROUP_H
