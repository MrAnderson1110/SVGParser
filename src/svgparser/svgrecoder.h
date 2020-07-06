#ifndef SVGRECODER_H
#define SVGRECODER_H

#include <QObject>
#include "svgparser_global.h"
#include "svgreader.h"
#include "svgtype.h"

#define svgRecoder SVGRecoder::instance()

class QQmlEngine;
class QJSEngine;

class SVGPARSER_EXPORT SVGRecoder : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(SVGRecoder)
    Q_PROPERTY(QStringList info READ info NOTIFY infoChanged)

public:

    static SVGRecoder *instance();
    static QObject *singletonTypeProvider(QQmlEngine *engine, QJSEngine *scriptEngine);

    void readAll();

    Q_INVOKABLE void parse();
    Q_INVOKABLE void record();

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

    QStringList info() const;
    void setInfo(const QString &info);

signals:
    void infoChanged();

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
    QStringList m_info;
};

#endif // SVGRECODER_H
