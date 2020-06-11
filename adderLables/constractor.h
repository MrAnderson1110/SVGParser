#ifndef CONSTRACTOR_H
#define CONSTRACTOR_H

#include <QHash>
#include <QFile>
#include <QTextStream>

class Constractor
{
public:
    Constractor(): m_outFile(nullptr), m_nodeFile(nullptr), m_edgeFile(nullptr) {}
    Constractor(QFile *inNodeFile, QFile *inEdgeFile, QFile *outFile)
        : m_outFile(outFile),
          m_nodeFile(inNodeFile),
          m_edgeFile(inEdgeFile),
          m_stream(new QTextStream()) {}

    bool makeNodes();
    bool makeEdges();

    int findSpacePos(QString str);
    bool isEmptyString(QString str);

    bool writeOutput();

    QString nodeElements() const { return m_nodeElements; }

    QString edgeElements() const { return m_edgeElements; }

private:
    QString m_nodeElements;
    QString m_edgeElements;
    QFile *m_outFile;
    QFile *m_nodeFile;
    QFile *m_edgeFile;
    QTextStream *m_stream;
    QHash<int, QString> m_hashId;
};

#endif // CONSTRACTOR_H
