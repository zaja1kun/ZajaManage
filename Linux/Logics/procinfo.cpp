#include "procinfo.h"
#include <dirent.h>
#include <ostream>
#include <sys/types.h>
#include <iostream>
using namespace std;

ProcInfo::ProcInfo(pid_t pid)
    : _pid(pid)
{

}

ProcInfo::ProcInfo(dirent* procDirEnt)
{
    if(procDirEnt)
    {
        _pid=atoi((procDirEnt->d_name));

        string taskPath = string("/proc/") + string(procDirEnt->d_name) + string("/task");

        dirent *dirEnt;
        DIR *procDir = opendir(taskPath.data());

        if(procDir)
        {
            while((dirEnt = readdir(procDir)))
                if(dirEnt->d_name[0]>='0' && dirEnt->d_name[0]<='9' /*&& atoi(dirEnt->d_name)!=_pid*/)
                {
                    _threads.emplace_back(dirEnt);
                }

            closedir(procDir);
        }

        char name[20];
        string statusPath = string("/proc/") + string(procDirEnt->d_name) + string("/status");
        FILE* fStatus = fopen(statusPath.data(), "r");
        if(fStatus)
        {
            fscanf(fStatus, "Name:\t%s", name);
            _execName=name;

            fclose(fStatus);
        }
    }
}
