#define DLLFUNC extern "C" __declspec(dllexport)

#include "f4se/PluginAPI.h"
using namespace std;

BOOL ConsolePrint(HANDLE hOut, const char *format, ...) {
	va_list args;
	va_start(args, format);

	size_t len = _vscprintf(format, args);
	char *buffer = new char[len + 1];

	DWORD bytes_written;
	vsprintf_s(buffer, len + 1, format, args);
	BOOL bRet = WriteFile(hOut, buffer, len, &bytes_written, NULL);

	delete[] buffer;
	va_end(args);

	return bRet;
}

void ServiceThread() {
	const static DWORD buffer_length = 128;
	char buffer[buffer_length];
	HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD bytes_read;

	ConsolePrint(hStdOut, "Ready!\n");
	BOOL bRet = ReadFile(hStdIn, buffer, buffer_length - 1, &bytes_read, NULL);
	if (bRet) {
		buffer[bytes_read] = 0;
		ConsolePrint(hStdOut, "I think you said [%s]\n", buffer);
	} else {
		ConsolePrint(hStdOut, "I didn't get that\n");
	}
}

DWORD WINAPI ServiceThreadWrapper(LPVOID) {
	ServiceThread();
	return 0;
}

DLLFUNC bool F4SEPlugin_Query(const F4SEInterface * f4se, PluginInfo * info) {
	info->infoVersion = PluginInfo::kInfoVersion;
	info->name = "Terabyte Test Plugin Bravo";
	info->version = 1;
	return true;
}

DLLFUNC bool F4SEPlugin_Load(const F4SEInterface * f4se) {
	DWORD thread_id;
	AllocConsole();
	HANDLE hThread= CreateThread(NULL, 0, ServiceThreadWrapper, NULL, 0, &thread_id);
	return hThread != 0;
}