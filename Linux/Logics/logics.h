#ifndef LOGICS_H
#define LOGICS_H


#include <list>
#include <procinfo.h>

extern "C"{
    std::list<ProcInfo> getProcList();
}


#endif // LOGICS_H
