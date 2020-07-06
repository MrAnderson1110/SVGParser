#include <QDebug>
#include <QFile>
#include "constractor.h"

const QString inNodesPath = "/home/adi/MyProj/Графы/БЧ-5_Графы_Агрегатов/Сеть_электрообогревателей/unique_nodes";
const QString inEdgesPath = "/home/adi/MyProj/Графы/БЧ-5_Графы_Агрегатов/Сеть_электрообогревателей/unique_edges";
const QString outPath = "/home/adi/MyProj/Графы/БЧ-5_Графы_Агрегатов/Сеть_электрообогревателей/preGraph.gv";
//const QString compairPath = "/home/adi/MyProj/Графы/системы_по_БЧ/%1/%1";

int main()
{    
    QString sys = "БК";

    QFile inNodesFile(inNodesPath);
    QFile inEdgesFile(inEdgesPath);
    QFile outFile(outPath);

    Constractor constractor(&inNodesFile, &inEdgesFile, &outFile);


//    constractor.makeCompairList(compairPath.arg(sys));

    constractor.makeNodes();
    constractor.makeEdges();

    constractor.writeOutput();

    return 0;
}
