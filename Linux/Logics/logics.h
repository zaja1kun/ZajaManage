#ifndef LOGICS_H
#define LOGICS_H


#include <list>
#include "procsinfo.h"

extern "C"{
    std::list<ProcInfo> getProcList();
    const ProcsInfo getProcsInfo();
    double getRamBuisiness();
}


#endif // LOGICS_H
