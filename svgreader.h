#ifndef SVGREADER_H
#define SVGREADER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QXmlStreamReader>



class SVGReader : public QObject, public QXmlStreamReader
{
    Q_OBJECT
    Q_PROPERTY(QString svgText READ svgText WRITE setSvgText NOTIFY svgTextChanged)
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
public:

    static SVGReader *instance();

    QString svgText() const
    { return m_svgText; }
    void setSvgText(const QString svgText);

    QString path() const
    { return m_path; }
    void setPath(const QString &path);

    bool setInFile(QFile *inFile);

    bool readAll();

    ~SVGReader();

signals:
    void svgTextChanged(QString svgText);
    void pathChanged(QString path);

private:
    explicit SVGReader(QObject *parent = nullptr);

    static SVGReader *m_instance;
    QTextStream *m_inStream;
    QFile *m_inFile;
    QString m_svgText;
    QString m_path;
};

#endif // SVGREADER_H
