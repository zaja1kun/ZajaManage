#ifndef THREADINFO_H
#define THREADINFO_H


#include <dirent.h>
#include <list>
#include <ostream>
#include <sys/types.h>

class ThreadInfo
{
public:
    ThreadInfo() = default;
    ThreadInfo(dirent* thrDirEnt);
    ~ThreadInfo() = default;

    friend std::ostream& operator<<(std::ostream& strm, const ThreadInfo& thrInfo)
    {
        return strm << thrInfo._tid;
    }

//protected:
    pid_t _tid = 0;
};

#endif // THREADINFO_H
