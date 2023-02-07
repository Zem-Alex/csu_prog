#include <Windows.h>
#include <TlHelp32.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    STARTUPINFO si = { 0 };
    PROCESS_INFORMATION pi = { 0 };
    if (!CreateProcess(L"C:\\Users\\79507\\Dropbox\\ой\\Desktop\\Folders\\ProgrammingLanguages\\C\\lesson\\Course01_Sem02\\Solution4(WinAPI)\\findProcesses.exe", NULL,  NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi))
    {
        wprintf(L"Can't create process!\n");
    }

    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (!hSnap)
    {
        wprintf(L"Can't get handle of snapshot process!\n");
        return 1;
    }

    PROCESSENTRY32 pe = { 0 };
    pe.dwSize = sizeof(PROCESSENTRY32);

    HANDLE process = { 0 };

    int count = 0;

    Process32First(hSnap, &pe);
    do
    {
        wprintf(L"%s\n", pe.szExeFile, pe.th32ProcessID, pe.cntThreads);
        if (!wcscmp(pe.szExeFile, L"findProcesses.exe"))
        {
            process = OpenProcess(PROCESS_ALL_ACCESS, TRUE, pe.th32ProcessID);
            count++;
            if (count > 1)
            {
                return 404;
                system("pause");
            }
            system("pause");
        }

        if (count > 1)
        {
            return 404;
            system("pause");
        }


    } while (Process32Next(hSnap, &pe));
    CloseHandle(hSnap);

    if (process)
    {
        TerminateProcess(process, 0);
        CloseHandle(process);
    }

    wprintf(L"^^%d^^\n", count);
    system("pause");

    return 0;
}