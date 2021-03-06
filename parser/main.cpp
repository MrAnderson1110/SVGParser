#include <QDebug>
#include <QTextStream>
#include <QVector>
#include <QFile>
#include <QString>

const QString inPath = "/home/adi/MyProj/Графы/БЧ-5_Графы_Агрегатов/Сеть_электрообогревателей/edges";
const QString outPath = "/home/adi/MyProj/Графы/БЧ-5_Графы_Агрегатов/Сеть_электрообогревателей/unique_edges";

int main()
{

    QFile inFile(inPath);
    QFile outFile(outPath);

    QTextStream out(&outFile);
    QTextStream in(&inFile);

    QVector<QString> inVector;
    QVector<QString> outVector;

    if(!inFile.open(QIODevice::ReadOnly)) {
        qDebug() << "file " << inPath << " did not opened!";
        return -1;
    }

    if(!outFile.open(QIODevice::ReadWrite)) {
        qDebug() << "file " << outPath << " parsed_text.txt did not opened!";
        return -1;
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

    return 0;
}
