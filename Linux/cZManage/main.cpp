#include <logics.h>
#include <unistd.h>
#include <algorithm>
#include <iostream>
#include <iomanip>

using namespace std;

void printThreadInfo(ThreadInfo threadInfo)
{
    cout<<threadInfo<<' ';
}

void printProcInfo(ProcInfo procInfo)
{
    cout<<setw(6)<<setiosflags(ios::left)<<procInfo<<" | "<<setw(20)<<procInfo._execName<<"| ";
    for_each(procInfo._threads.begin()
             , procInfo._threads.end()
             , printThreadInfo
             );
    cout<<endl;
}

int main()
{
    for(int i=0; i<30; i++)
    {
        auto procList = getProcList();
        //for_each(procList.begin(), procList.end(), printProcInfo);
        cout<<procList.size()<<" processes total"<<endl;
        sleep(1);
    }
}
