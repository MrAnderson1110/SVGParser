#include <QCoreApplication>
#include <QFile>
#include <QTextStream>

const QString inPath = "/home/adi/MyProj/Графы/системы_по_БЧ/systems_BCH";

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile inFile(inPath);

    if(!inFile.open(QIODevice::ReadOnly)) {
        qFatal("can not read file");
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

    QString outPath = QString("/home/adi/MyProj/Графы/системы_по_БЧ/%1/%1");
    QList<QString> uniqueKeys = systemMap.uniqueKeys();

    QFile outFile;
    QTextStream outStream(&outFile);

    for(int i = 0; i < uniqueKeys.size(); ++i) {
        outFile.setFileName(outPath.arg(uniqueKeys[i]));
        if(!outFile.open(QIODevice::WriteOnly))
            qFatal("can not write file");
        QList<QString> values = systemMap.values(uniqueKeys[i]);
        for(int i = 0; i < values.size(); ++i) {
            outStream << values[i] << "\n";
        }

        outFile.close();
    }


    return a.exec();
}
