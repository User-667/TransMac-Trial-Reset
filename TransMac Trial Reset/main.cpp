#define UNICODE
#define _UNICODE

#include <windows.h>
#include <shlwapi.h>
#include <shellapi.h>

#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "Shell32.lib")

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{

    const wchar_t* subkey =
        L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Shell Extensions\\Approved";

    LONG del = SHDeleteKeyW(HKEY_CURRENT_USER, subkey);

    HKEY h;
    if (RegOpenKeyExW(HKEY_CURRENT_USER, subkey, 0, KEY_READ, &h) == ERROR_SUCCESS) {
        RegFlushKey(h);
        RegCloseKey(h);
    }

    Sleep(2000);

    wchar_t exePath[MAX_PATH];
    GetModuleFileNameW(NULL, exePath, MAX_PATH);
    PathRemoveFileSpecW(exePath);

    wchar_t transmacPath[MAX_PATH];
    wsprintfW(transmacPath, L"%s\\TransMac.exe", exePath);

    if (PathFileExistsW(transmacPath))
    {
        ShellExecuteW(NULL, L"open", transmacPath, NULL, exePath, SW_SHOWNORMAL);
    }

    return 0;
}