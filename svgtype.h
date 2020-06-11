#ifndef SVGTYPE_H
#define SVGTYPE_H

#include <QObject>

class SVGType : public QObject
{
    Q_OBJECT

    enum Type {
        Path,
        Rectangle,
        Triangle,
        Ellipse,
        Text
    };

public:
    explicit SVGType(QObject *parent = nullptr);

signals:

private:
    QString m_id;
    Type m_type;
};

#endif // SVGTYPE_H
