#ifndef SVGTYPE_H
#define SVGTYPE_H

#include <QObject>
#include "svggroup.h"

class SVGGroup;
class SVGText;
class SVGPolygon;
class SVGPath;

class SVGType : public QObject
{
    Q_OBJECT
public:

    struct childsType {
    public:
        SVGText *m_svgText;
        SVGPolygon *m_svgPolygon;
        SVGPath *m_svgPath;
    };

    enum Type {
        Path,
        Rectangle,
        Triangle,
        Ellipse,
        Text,
        Invalid
    };
    explicit SVGType(QObject *parent = nullptr) : QObject(parent), m_childType(new childsType()) {}

    QString stroke() const;
    void setStroke(const QString &stroke);

    QString fill() const;
    void setFill(const QString &fill);

    Type type() const;
    void setType(const QString &type, const int conerCount = 0);
    void setType(SVGType::Type type);

    childsType *getChildType() const;

signals:

private:
    Type m_type;
    QString m_fill;
    QString m_stroke;
    childsType *m_childType;
};

class SVGText : public SVGType
{
public:
    SVGText() : SVGType() {}

    double x() const;
    void setX(double x);

    double y() const;
    void setY(double y);

    QString textAnchors() const;
    void setTextAnchors(const QString &textAnchors);

    QString fontFamily() const;
    void setFontFamily(const QString &fontFamily);

    double fontSize() const;
    void setFontSize(double fontSize);

    QString text() const;
    void setText(const QString &text);

    int getId() const;
    void setId(int value);

private:
    double m_x;
    double m_y;
    QString m_textAnchors;
    QString m_fontFamily;
    double m_fontSize;
    QString m_text;
    int id;
};

class SVGPolygon : public SVGType
{
public:
    SVGPolygon(): SVGType() {}

    enum Direction {
        Down = 0,
        Left = 90,
        Up = 180,
        Right = 270,
        Invalid
    };

    void setParametrs(QString str);
    void setTranslate(const QString &translate);

    double translateX() const;
    double translateY() const;
    double x() const;
    double y() const;
    double height() const;
    double width() const;
    SVGPolygon::Direction triDirection() const;
    int conerCount() const;

    int getId() const;
    void setId(int value);

private:
    void setRectParametrs(QList<double> &xParams, QList<double> &yParams);
    void setTriParametrs(QList<double> &xParams, QList<double> &yParams);

    double m_translateX;
    double m_translateY;
    double m_x;
    double m_y;
    double m_height;
    double m_width;
    SVGPolygon::Direction m_triDirection;
    int m_conerCount = 0;
    int id;
};

class SVGPath : public SVGType
{
public:
    SVGPath() : SVGType() {}

    struct line {
        double xLine = 0.0;
        double yLine = 0.0;
        double width = 0.0;
        double height = 0.0;
    };

    QString incomingId() const;
    QString outgoingId() const;

    void setInOutId(const QString &id);

    QString path() const;
    void setPath(const QString &path);

    QString parseLines();

private:
    QString m_path;
    QList<line> m_lines;
    QString m_incomingId;
    QString m_outgoingId;
};


#endif // SVGTYPE_H
