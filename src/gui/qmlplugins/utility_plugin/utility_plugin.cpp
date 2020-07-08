#include "utility_plugin.h"
#include <QtQml>
#include "appsettings.h"

void UtilityPlugin::registerTypes(const char *uri)
{
    qmlRegisterSingletonType<AppSettings>(uri, 1, 0, "AppSettings", AppSettings::singletonTypeProvider);
}

