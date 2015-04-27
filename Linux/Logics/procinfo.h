#ifndef PROCINFO_H
#define PROCINFO_H

#include "threadinfo.h"

class ProcInfo
{
public:
    ProcInfo() = default;
    ProcInfo(pid_t pid);
    ProcInfo(dirent* procDirEnt);
    ~ProcInfo() = default;

    int getThreadAmount();
    const std::list<ThreadInfo>& getThreadList();

    friend std::ostream& operator<<(std::ostream& strm, const ProcInfo& procInfo)
    {
        return strm << procInfo._pid;
    }


//protected:
    pid_t _pid = 0;
    std::string _execName;
    std::list<ThreadInfo> _threads;
protected:
    int _threadAmount = 0;
};

#endif // PROCINFO_H
