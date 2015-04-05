#ifndef PROCINFO_H
#define PROCINFO_H

#include "threadinfo.h"
#include <dirent.h>
#include <list>
#include <ostream>
#include <sys/types.h>

class ProcInfo
{
public:
    ProcInfo() = default;
    ProcInfo(pid_t pid);
    ProcInfo(dirent* procDirEnt);
    ~ProcInfo() = default;

    friend std::ostream& operator<<(std::ostream& strm, const ProcInfo& procInfo)
    {
        return strm << procInfo._pid;
    }


//protected:
    pid_t _pid = 0;
    std::string _execName;
    std::list<ThreadInfo> _threads;
};

#endif // PROCINFO_H
