#ifndef SVGREADER_H
#define SVGREADER_H

#include <QObject>
#include <QString>
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

    inline QTextStream *inStream() const
    { return m_inStream; }
    inline void setInStream(QTextStream *inStream)
    { if(inStream) m_inStream = inStream; }

    inline QString svgText() const
    { return m_svgText; }
    void setSvgText(const QString &svgText);

    inline QString path() const
    { return m_path; }
    void setPath(const QString &inPath);

    inline QFile *inFile() const
    { return m_inFile; }
    inline void setInFile(QFile *inFile) {
        if(inFile && inFile != m_inFile) {
            m_inFile = inFile;
        }
    }

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
