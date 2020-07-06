#ifndef SVGRECODER_H
#define SVGRECODER_H

#include <QObject>
#include "svgreader.h"
#include "svgtype.h"

#define svgRecoder SVGRecoder::instance()

class SVGRecoder : public QObject
{
    Q_OBJECT

public:

    static SVGRecoder *instance();

    void readAll();

    void parse();
    void record();

    QString nodesPath() const;
    void setNodesPath(const QString &nodesPath);

    QString edgesPath() const;
    void setEdgesPath(const QString &edgesPath);

    QString arrowsPath() const;
    void setArrowsPath(const QString &arrowsPath);

    QString textPath() const;
    void setTextPath(const QString &textPath);

    QString globalSettingsPath() const;
    void setGlobalSettingsPath(const QString &globalSettingsPath);

    ~SVGRecoder();

signals:

private:
    explicit SVGRecoder(QObject *parent = nullptr);
    bool setOutFile(QFile *file);

    static SVGRecoder *m_instance;
    QList<SVGGroup *> m_groups;
    QString m_globalSettingsPath;
    QString m_nodesPath;
    QString m_edgesPath;
    QString m_arrowsPath;
    QString m_textPath;
    QFile *m_outFile;
    QTextStream m_stream;
    QString m_globalWidth;
    QString m_globalHeight;
};

#endif // SVGRECODER_H
