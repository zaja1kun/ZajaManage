#include "procsinfo.h"

ProcsInfo::ProcsInfo()
{
}

ProcsInfo::ProcsInfo(std::list<ProcInfo> procList, int threadAmount)
    : _procList(procList)
    , _threadAmount(threadAmount)
{
    _procAmount = _procList.size();
}

const std::list<ProcInfo>& ProcsInfo::getProcList()
{
    return _procList;
}

int ProcsInfo::getProcAmount()
{
    return _procAmount;
}

int ProcsInfo::getThreadAmount()
{
    return _threadAmount;
}
