#ifndef PARSERPLUGINS_PLUGIN_H
#define PARSERPLUGINS_PLUGIN_H

#include <QQmlExtensionPlugin>

class ParserPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri) override;
};

#endif // PARSERPLUGINS_PLUGIN_H
