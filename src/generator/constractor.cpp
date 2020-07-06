#include "constractor.h"
#include <QDebug>


bool Constractor::makeNodes()
{
    int count = 1;
    int spacePos = 0;
    QString temp = "";
    if(!m_nodeFile->open(QIODevice::ReadOnly)) {
        qDebug() << "file " << m_nodeFile->fileName() << " did not opened";
        return false;
    }
    m_stream->setDevice(m_nodeFile);
    while(!m_stream->atEnd()) {
        temp = m_stream->readLine() + '\n';
        if(isEmptyString(temp)) {
            m_nodeElements += '\n';
            continue;
        }
        spacePos = findSpacePos(temp);
        QString notDidgChar;
        int stringLength = 0;
        for (int j = 0; j < spacePos; ++j) {
            if(temp[j] == '\"') {
                notDidgChar += "\\\"";
                continue;
            }
            notDidgChar += temp[j];
            ++stringLength;
        }
//        if(!compare(notDidgChar))
//            continue;
        m_hashId.insert(count, notDidgChar);
        notDidgChar.clear();
        for (int j = spacePos + 1; j < temp.size(); ++j) {
            if(temp[j] == '\"') {
                notDidgChar += "\\\"";
                continue;
            }
            if(temp[j] != '\n') {
                notDidgChar += temp[j];
            }
        }
        int length = stringLength / 7 + 1;
        if(length != 0)
            m_nodeElements += QString::number(count) + " [id=\"" + notDidgChar + "\", label=\"" + m_hashId.value(count) + "\", width=" + QString::number(length) + "]\n";
        else
            notDidgChar = QString::number(count) + " [id=\"" + notDidgChar + "\", label=\"" + m_hashId.value(count) + "\"]\n";
        ++count;
    }
    return true;
}

bool Constractor::makeEdges()
{
    int spacePos = 0;
    QString temp = "";
    if(!m_edgeFile->open(QIODevice::ReadOnly)) {
        qDebug() << "file " << m_nodeFile->fileName() << " did not opened";
        return false;
    }
    m_stream->setDevice(m_edgeFile);
    while(!m_stream->atEnd()) {
        temp = m_stream->readLine() + '\n';
        if(isEmptyString(temp)){
            m_edgeElements += '\n';
            continue;
        }
        spacePos = findSpacePos(temp);
        QString didgChar;
        for(int i = 0; i < spacePos; ++i) {
            if(temp[i] == '\"') {
                didgChar += "\\\"";
                continue;
            }
            didgChar += temp[i];
        }
        if(!m_hashId.key(didgChar)) {
            didgChar.clear();
            continue;
        }
        QString secDidgChar;
        for(int i = spacePos + 1; i < temp.size(); ++i) {
            if(temp[i] == '\"') {
                secDidgChar += "\\\"";
                continue;
            }
            if(temp[i] != '\n')
                secDidgChar += temp[i];
        }
        if(!m_hashId.key(secDidgChar)) {
            secDidgChar.clear();
            continue;
        }
        m_edgeElements += QString::number(m_hashId.key(didgChar)) + " -> " + QString::number(m_hashId.key(secDidgChar)) + '\n';
    }
    return true;
}

int Constractor::findSpacePos(QString str)
{
    int spacePos = 0;
    for (int i = 0; i < str.size(); ++i) {
        if(str[i] == '\t') {
            spacePos = i;
            return spacePos;
        }
    }
    return 0;
}

bool Constractor::isEmptyString(QString str)
{
    if(str == '\n'){
        return true;
    }
    return false;
}

void Constractor::makeCompairList(const QString &path)
{
    QFile devider(path);
    if(!devider.open(QIODevice::ReadOnly))
        qFatal("can not open comparatorList file");
    QTextStream devStream(&devider);
    QString dev = devStream.readAll();
    m_compareList = dev.split('\n');
    m_compareList.removeLast();
    devider.close();
}

bool Constractor::compare(const QString &str)
{
    return m_compareList.contains(str);
}

bool Constractor::writeOutput()
{
    QString start = "digraph { \nnode [shape=\"rectangle\"]\n#concentrate=true;\nsplines=ortho;\n";
    QString end = "}";
    if(!m_outFile->open(QIODevice::WriteOnly)) {
        qDebug() << "file " << m_nodeFile->fileName() << " did not opened";
        return false;
    }
    m_stream->setDevice(m_outFile);
    (*m_stream) << start << nodeElements() << edgeElements() << end;
    return true;
}


bool makeUnique(const QString &inPath, const QString &outPath)
{
    QFile inFile(inPath);
    QFile outFile(outPath);

    QTextStream out(&outFile);
    QTextStream in(&inFile);

    QVector<QString> inVector;
    QVector<QString> outVector;

    if(!inFile.open(QIODevice::ReadOnly)) {
        qDebug() << "file " << inPath << " did not opened!";
        return false;
    }

    if(!outFile.open(QIODevice::ReadWrite)) {
        qDebug() << "file " << outPath << " parsed_text.txt did not opened!";
        return false;
    }

    int count = 0;
    QString temp;
    while(!in.atEnd()) {
        temp = in.readLine() + '\n';
        bool unique = true;

        for(auto i = inVector.begin(); i != inVector.end(); ++i) {
            unique = *i == temp ? false : true;
            if(!unique)
                break;
        }
        if(unique)
            inVector.push_back(temp);
        else
            ++count;
    }

//    auto iter = std::unique(inVector.begin(), inVector.end());

    for(auto i = inVector.begin(); i != inVector.end(); ++i) {
        out << *i;
    }

    qDebug() << "Founded " << count << " same elements!/n";


    return true;
}

bool devide(const QString &inPath, QString outPath)
{
    QFile inFile(inPath);

    if(!inFile.open(QIODevice::ReadOnly)) {
        qDebug() << "file " << inPath << " did not opened!";
        return false;
    }

    QTextStream inStream(&inFile);

    QMultiMap<QString, QString> systemMap;
    QStringList outString;

    while(!inStream.atEnd()) {
        QString temp = inStream.readLine();
        if(temp == '\n')
            continue;
        outString = temp.split("\t");
        systemMap.insert(outString[0], outString[1]);
    }

    QString path = QString(outPath + "/%1/%1");
    QList<QString> uniqueKeys = systemMap.uniqueKeys();

    QFile outFile;
    QTextStream outStream(&outFile);

    for(int i = 0; i < uniqueKeys.size(); ++i) {
        outFile.setFileName(outPath.arg(uniqueKeys[i]));
        if(!outFile.open(QIODevice::WriteOnly)) {
            qDebug() << "file " << inPath << " did not opened!";
            return false;
        }
        QList<QString> values = systemMap.values(uniqueKeys[i]);
        for(int i = 0; i < values.size(); ++i)
            outStream << values[i] << "\n";

        outFile.close();
    }

    return true;
}
