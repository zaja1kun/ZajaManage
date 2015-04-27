#ifndef PROCSINFO_H
#define PROCSINFO_H

#include "procinfo.h"

class ProcInfo;

class ProcsInfo
{
public:
    ProcsInfo();
    ProcsInfo(std::list<ProcInfo> procList, int threadAmount);

    const std::list<ProcInfo>& getProcList();
    int getProcAmount();
    int getThreadAmount();

protected:
    std::list<ProcInfo> _procList;
    int _procAmount = 0;
    int _threadAmount = 0;

};

#endif // PROCSINFO_H
