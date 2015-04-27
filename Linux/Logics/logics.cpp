#include "logics.h"
#include "procinfo.h"
#include "procsinfo.h"
#include <dirent.h>
#include <list>

using namespace std;

list<ProcInfo> getProcList()
{
    list<ProcInfo> procList;
    dirent *dirEnt;
    DIR *procDir = opendir("/proc");

    while((dirEnt = readdir(procDir)))
        if(dirEnt->d_name[0]>='0' && dirEnt->d_name[0]<='9')
            procList.emplace_back(dirEnt);

    closedir(procDir);
    return procList;
}

const ProcsInfo getProcsInfo()
{
    list<ProcInfo> procList;
    //ProcInfo tempProcInfo;
    unsigned int threadAmount=0;
    dirent *dirEnt;
    DIR *procDir = opendir("/proc");

    while((dirEnt = readdir(procDir)))
        if(dirEnt->d_name[0]>='0' && dirEnt->d_name[0]<='9')
        {
            //tempProcInfo = ProcInfo(dirEnt);
            procList.emplace_back(dirEnt);
            threadAmount += procList.back().getThreadAmount();
        }

    closedir(procDir);
    return ProcsInfo(procList, threadAmount);
}

double getRamBuisiness()
{
    int memTotal
        , memFree;
    FILE* fMeminfo = fopen("/proc/meminfo", "r");
    if(fMeminfo)
    {
        fscanf(fMeminfo, "MemTotal:%d kB\n", &memTotal);
        fscanf(fMeminfo, "MemFree:%d kB\n", &memFree);

        fclose(fMeminfo);
    }

    return ((double)(memTotal-memFree)) / (double)memTotal * 100;
}
