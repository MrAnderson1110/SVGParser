#ifndef SVGREADER_H
#define SVGREADER_H

#include <QObject>
#include <QXmlStreamReader>
#include "svgparser_global.h"

class IOHandler;

#define svgReader SVGReader::instance()

class SVGPARSER_EXPORT SVGReader : public QObject, public QXmlStreamReader
{
    Q_OBJECT
    Q_PROPERTY(QString svgText READ svgText WRITE setSvgText NOTIFY svgTextChanged)
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
public:

    static SVGReader *instance();

    QString getAttribute(const QString &value);

    QString svgText() const;
    void setSvgText(const QString svgText);

    QString path() const;
    void setPath(const QString &path);

    bool readAll();

    QXmlStreamReader::TokenType readNextComment();
    QXmlStreamReader::TokenType readNextElement();

signals:
    void svgTextChanged(QString svgText);
    void pathChanged(QString path);

private:
    explicit SVGReader(QObject *parent = nullptr);

    static SVGReader *m_instance;
    QString m_svgText;
    QString m_path;
};


#endif // SVGREADER_H
