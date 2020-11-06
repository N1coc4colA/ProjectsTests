#include "ios.h"

#include <stdio.h>
#include <string.h>

namespace ios {
IOS::IOS()
{
}

IOS::~IOS()
{
    if (this->streaming.is_open()) {
        streaming.close();
    }
}

IOS *IOS::instance()
{
    static IOS *ios = new IOS;
    return ios;
}

void IOS::output(const char *c)
{
    IOS::instance()->streaming << c;
    IOS::instance()->streaming.flush();
}

void IOS::output(void *ptr)
{
    IOS::instance()->streaming << ptr;
    IOS::instance()->streaming.flush();
}


void IOS::setOutputFile(const char *file)
{
    if (IOS::instance()->streaming.is_open()) {
        IOS::instance()->streaming.close();
    }
    IOS::instance()->streaming.open(file);
}
}
