#include "appsettings.h"

AppSettings *AppSettings::instance()
{
    if(!m_instance)
        m_instance = new AppSettings();
    return m_instance;
}

