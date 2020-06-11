#ifndef ELEMENT_H
#define ELEMENT_H

#include <QHash>
#include <QString>

class Element
{
public:
    QHash<int, QString> m_idHash;
    Element();
};

#endif // ELEMENT_H
