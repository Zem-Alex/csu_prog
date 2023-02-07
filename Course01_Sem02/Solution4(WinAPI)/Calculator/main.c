#ifndef UNICODE
#define UNICODE
#endif
#pragma comment(lib, "netapi32.lib")

#include <stdio.h>
#include <assert.h>
#include <windows.h> 
#include <wchar.h>
#include <lm.h>
#include <locale.h>
#include <initguid.h>
#include <KnownFolders.h>
#include <ShlObj.h>
#include <string.h>
#include <time.h>

#define BUFSIZE MAX_PATH

int wmain(int argc, wchar_t* argv[])
{
    setlocale(LC_ALL, "Rus");
    LPUSER_INFO_0 pBuf = NULL;
    LPUSER_INFO_0 pTmpBuf;
    DWORD dwLevel = 0;
    DWORD dwPrefMaxLen = MAX_PREFERRED_LENGTH;
    DWORD dwEntriesRead = 0;
    DWORD dwTotalEntries = 0;
    DWORD dwResumeHandle = 0;
    DWORD i;
    DWORD dwTotalCount = 0;
    NET_API_STATUS nStatus;
    LPTSTR pszServerName = NULL;

    if (argc > 2)
    {
        fwprintf(stderr, L"Usage: %s [\\\\ServerName]\n", argv[0]);
        exit(1);
    }
    // The server is not the default local computer.
    //
    if (argc == 2)
        pszServerName = (LPTSTR)argv[1];
    wprintf(L"\nUser account on %s: \n", pszServerName);
    //
    // Call the NetUserEnum function, specifying level 0; 
    //   enumerate global user account types only.
    //
    do // begin do
    {
        nStatus = NetUserEnum((LPCWSTR)pszServerName,
            dwLevel,
            FILTER_NORMAL_ACCOUNT, // global users
            (LPBYTE*)&pBuf,
            dwPrefMaxLen,
            &dwEntriesRead,
            &dwTotalEntries,
            &dwResumeHandle);
        //
        // If the call succeeds,
        //
        if ((nStatus == NERR_Success) || (nStatus == ERROR_MORE_DATA))
        {
            if ((pTmpBuf = pBuf) != NULL)
            {
                //
                // Loop through the entries.
                //
                for (i = 0; (i < dwEntriesRead); i++)
                {
                    assert(pTmpBuf != NULL);

                    if (pTmpBuf == NULL)
                    {
                        fprintf(stderr, "An access violation has occurred\n");
                        break;
                    }
                    //
                    //  Print the name of the user account.
                    //
                    wprintf(L"\t-- %s\n", pTmpBuf->usri0_name);

                    pTmpBuf++;
                    dwTotalCount++;
                }
            }
        }
        //
        // Otherwise, print the system error.
        //
        else
            fprintf(stderr, "A system error has occurred: %d\n", nStatus);
        //
        // Free the allocated buffer.
        //
        if (pBuf != NULL)
        {
            NetApiBufferFree(pBuf);
            pBuf = NULL;
        }
    }
    // Continue to call NetUserEnum while 
    //  there are more entries. 
    // 
    while (nStatus == ERROR_MORE_DATA); // end do
    //
    // Check again for allocated memory.
    //
    if (pBuf != NULL)
        NetApiBufferFree(pBuf);
    //
    // Print the final count of users enumerated.
    //
    fprintf(stderr, "\nTotal of %d entries enumerated\n", dwTotalCount);

    wchar_t computerName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(computerName) / sizeof(computerName[0]);

    int r = GetComputerNameW(computerName, &size);

    if (r == 0) {
        wprintf(L"Failed to get computer name %ld", GetLastError());
        return 1;
    }

    wprintf(L"\nComputer name: %ls\n", computerName);

    wchar_t username[UNLEN + 1];
    DWORD len = sizeof(username) / sizeof(wchar_t);

    r = GetUserNameW(username, &len);

    if (r == 0) {
        wprintf(L"Failed to get username %ld", GetLastError());
        return 1;
    }

    wprintf(L"\nUser name: %ls\n", username);

    wchar_t buf[BUFSIZE];

    if (argc != 2) {

        wprintf(L"\nUsage: %ls <dir>\n", argv[0]);
    }

    MEMORYSTATUSEX mem = { 0 };

    mem.dwLength = sizeof(mem);

    r = GlobalMemoryStatusEx(&mem);

    if (r == 0) {
        wprintf(L"Failed to memory status %ld", GetLastError());
        return 1;
    }

    wprintf(L"\nMemory in use: %ld percent\n", mem.dwMemoryLoad);
    wprintf(L"Total physical memory: %lld\n", mem.ullTotalPhys);
    wprintf(L"Free physical memory: %lld\n", mem.ullAvailPhys);
    wprintf(L"Total virtual memory: %lld\n", mem.ullTotalVirtual);
    wprintf(L"Free virtual memory: %lld\n", mem.ullAvailVirtual);

    PWSTR path = NULL;

    HRESULT hr = SHGetKnownFolderPath(&FOLDERID_Documents, 0, NULL, &path);

    if (SUCCEEDED(hr)) {
        wprintf(L"\n%ls\n", path);
    }

    CoTaskMemFree(path);

    unsigned __int64 freeCall,
        total,
        free;

    r = GetDiskFreeSpaceExW(L"C:\\", (PULARGE_INTEGER)&freeCall,
        (PULARGE_INTEGER)&total, (PULARGE_INTEGER)&free);

    if (r == 0) {

        wprintf(L"Failed to get free disk space %ld", GetLastError());
        return 1;
    }

    wprintf(L"\nAvailable space to caller: %I64u MB\n", freeCall / (1024 * 1024));
    wprintf(L"Total space: %I64u MB\n", total / (1024 * 1024));
    wprintf(L"Free space on drive: %I64u MB\n", free / (1024 * 1024));

    DWORD BufSize = MAX_PATH;
    DWORD mhz = MAX_PATH;
    HKEY key;

     r = RegOpenKeyExW(HKEY_LOCAL_MACHINE,
        L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &key);

    if (r != ERROR_SUCCESS) {

        wprintf(L"RegOpenKeyExW() failed %ld", GetLastError());
        return 1;
    }

    r = RegQueryValueExW(key, L"~MHz", NULL, NULL, (LPBYTE)&mhz, &BufSize);

    if (r != ERROR_SUCCESS) {

        wprintf(L"RegQueryValueExW() failed %ld", GetLastError());
        return 1;
    }

    wprintf(L"\nCPU speed: %lu MHz\n", mhz);


    int cpubrand[4 * 3];

    __cpuid(&cpubrand[0], 0x80000002);
    __cpuid(&cpubrand[4], 0x80000003);
    __cpuid(&cpubrand[8], 0x80000004);

    char str[48];
    memset(str, 0, sizeof str);
    memcpy(str, cpubrand, sizeof cpubrand);
    printf("CPU brand: %s\n", str);

    r = RegCloseKey(key);

    if (r != ERROR_SUCCESS) {

        wprintf(L"Failed to close registry handle %ld", GetLastError());
        return 1;
    }

    struct tm newtime;
    char am_pm[] = "AM";
    __time64_t long_time;
    char timebuf[26];
    errno_t err;

    // Get time as 64-bit integer.
    _time64(&long_time);
    // Convert to local time.
    err = _localtime64_s(&newtime, &long_time);
    if (err)
    {
        printf("Invalid argument to _localtime64_s.");
        exit(1);
    }
    if (newtime.tm_hour > 12)        // Set up extension.
        strcpy_s(am_pm, sizeof(am_pm), "PM");
    if (newtime.tm_hour > 12)        // Convert from 24-hour
        newtime.tm_hour -= 12;        // to 12-hour clock.
    if (newtime.tm_hour == 0)        // Set hour to 12 if midnight.
        newtime.tm_hour = 12;

    // Convert to an ASCII representation.
    err = asctime_s(timebuf, 26, &newtime);
    if (err)
    {
        printf("Invalid argument to asctime_s.");
        exit(1);
    }
    printf("\n%.19s %s\n", timebuf, am_pm);

    //r = LockWorkStation();
    //if (r == 0) 
    //{
    //    wprintf(L"LockWorkStation() failed %d\n", GetLastError());
    //    return 1;
    //}

    return 0;
}