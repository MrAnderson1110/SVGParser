#ifndef UTILITY_PLUGIN_H
#define UTILITY_PLUGIN_H

#include <QQmlExtensionPlugin>

class UtilityPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri) override;
};

#endif // UTILITY_PLUGIN_H
