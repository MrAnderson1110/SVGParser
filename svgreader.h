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

    SVGReader *instance();

    inline QTextStream *inStream() const {
        return m_inStream;
    }
    inline void setInStream(QTextStream *inStream) {
        if(inStream)
            m_inStream = inStream;
    }

    inline QString svgText() const {
        return m_svgText;
    }
    inline void setSvgText(const QString &svgText) {
        if(svgText != m_svgText) {
            m_svgText = svgText;
            svgTextChanged(m_svgText);
        }
    }

    inline QString getPath() const {
        return m_path;
    }
    inline void setPath(const QString &path) {
        if(path != m_path) {
            m_path = path;
            pathChanged(m_path);
        }
    }

    bool readAll();

    ~SVGReader();


signals:
    void svgTextChanged(QString m_svgText);
    void pathChanged(QString m_path);

private:
    explicit SVGReader(QObject *parent = nullptr);

    SVGReader *m_instance;
    QTextStream *m_inStream;
    QString m_svgText;
    QString m_path;
};

#endif // SVGREADER_H
