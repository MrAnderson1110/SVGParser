#include "parser.h"
#include <QtQml>
#include "svgrecoder.h"

void ParserPlugin::registerTypes(const char *uri)
{
    qmlRegisterSingletonType<SVGRecoder>(uri, 1, 0, "Recoder", SVGRecoder::singletonTypeProvider);
}

