#include <QDebug>
#include <QFile>
#include "constractor.h"

const QString inNodesPath = "/home/mranderson/Work/Графы/Агрегаты/unique_nodes";
const QString inEdgesPath = "/home/mranderson/Work/Графы/Агрегаты/unique_edges";
const QString outPath = "/home/mranderson/Work/Графы/Агрегаты/preGraph.gv";

int main()
{

    QFile inNodesFile(inNodesPath);
    QFile inEdgesFile(inEdgesPath);
    QFile outFile(outPath);

    Constractor constractor(&inNodesFile, &inEdgesFile, &outFile);

    constractor.makeNodes();
    constractor.makeEdges();

    constractor.writeOutput();

    return 0;
}
