#include "threadinfo.h"

ThreadInfo::ThreadInfo(dirent* thrDirEnt)
{
    if(thrDirEnt)
    {
        _tid=atoi((thrDirEnt->d_name));
    }
}
