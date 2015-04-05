#include "logics.h"
#include "procinfo.h"
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
