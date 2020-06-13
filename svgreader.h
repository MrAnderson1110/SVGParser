#ifndef SVGREADER_H
#define SVGREADER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QXmlStreamReader>

#define svgReader SVGReader::instance()

class SVGReader : public QObject, public QXmlStreamReader
{
    Q_OBJECT
    Q_PROPERTY(QString svgText READ svgText WRITE setSvgText NOTIFY svgTextChanged)
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
public:

    static SVGReader *instance();

    QString getAttribute(const QString &value);

    QString svgText() const
    { return m_svgText; }
    void setSvgText(const QString svgText);

    QString path() const
    { return m_path; }
    void setPath(const QString &path);

    bool readAll();

    QXmlStreamReader::TokenType readNextComment();
    QXmlStreamReader::TokenType readNextElement();

    ~SVGReader();

signals:
    void svgTextChanged(QString svgText);
    void pathChanged(QString path);

private:
    explicit SVGReader(QObject *parent = nullptr);
    bool setInFile(QFile *inFile);

    static SVGReader *m_instance;
    QFile *m_inFile;
    QString m_svgText;
    QString m_path;
};


#endif // SVGREADER_H
