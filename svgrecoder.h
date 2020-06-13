#ifndef SVGRECODER_H
#define SVGRECODER_H

#include <QObject>
#include "svgreader.h"
#include "svgtype.h"

#define svgRecoder SVGRecoder::instance()

class SVGRecoder : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)

public:

    static SVGRecoder *instance();

    QString path() const { return m_path; }
    void setPath(const QString &path);

    void readAll();

    void parse();
    void record();

    ~SVGRecoder();
signals:
    void pathChanged(QString path);

private:
    explicit SVGRecoder(QObject *parent = nullptr);
    bool setOutFile(QFile *file);

    static SVGRecoder *m_instance;
    QList<SVGGroup *> m_groups;
    QString m_path;
    QFile *m_outFile;
    QTextStream m_stream;
    QString m_globalWidth;
    QString m_globalHeight;
};

#endif // SVGRECODER_H
