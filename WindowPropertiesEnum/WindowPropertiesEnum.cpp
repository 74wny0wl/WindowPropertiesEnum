// WindowsEnum.cpp : This file contains the 'main' function. Program execution begins and ends there.
//



#include <iostream>
#include <Windows.h>
#include <string>
#include <string_view>
#include <cstdlib> // For atoi
#include <strsafe.h>
#include "Menu.h"
#include "ArgumentParser.h"

#define BUFFER 4096 
#define VALUELENGTH 256 


bool memory_readable(void* ptr, size_t byteCount)
{
	MEMORY_BASIC_INFORMATION mbi;
	if (VirtualQuery(ptr, &mbi, sizeof(MEMORY_BASIC_INFORMATION)) == 0)
		return false;

	if (mbi.State != MEM_COMMIT)
		return false;

	if (mbi.Protect == PAGE_NOACCESS || mbi.Protect == PAGE_EXECUTE)
		return false;

	// This checks that the start of memory block is in the same "region" as the
	// end. If it isn't you "simplify" the problem into checking that the rest of 
	// the memory is readable.
	size_t blockOffset = (size_t)((char*)ptr - (char*)mbi.AllocationBase);
	size_t blockBytesPostPtr = mbi.RegionSize - blockOffset;

	if (blockBytesPostPtr < byteCount)
		return memory_readable((char*)ptr + blockBytesPostPtr,
			byteCount - blockBytesPostPtr);

	return true;
}

BOOL CALLBACK WinPropProc(
	HWND hwndSubclass,  // handle of window with property 
	LPWSTR lpszString,  // property string or atom 
	HANDLE hData,       // data handle 
	ULONG_PTR unused)
{

	static int nProp = 1;    // property counter 
	TCHAR tchBuffer[BUFFER]; // expanded-string buffer 
	size_t nSize; // size of string in buffer 
	HDC hdc;                 // device-context handle
	HRESULT hResult;
	HGLOBAL hMemProp;
	char* value;



	hdc = GetDC(hwndSubclass);

	BOOL CONTINUE_ENUM = FALSE;

	if (memory_readable(lpszString, sizeof(lpszString))) {

		// Display window property string in client area.
		hResult = StringCchPrintf(tchBuffer, BUFFER, L"WinProp % d: % s", nProp++, lpszString);
		if (FAILED(hResult))
		{
			std::cout << "[1]: write error handler if function fails." << std::endl;
		}
		hResult = StringCchLength(tchBuffer, BUFFER, &nSize);
		if (FAILED(hResult))
		{
			std::cout << "[2]: write error handler if function fails." << std::endl;
		}

		std::wstring winProp_wstr(tchBuffer);
		std::string winProp_str;
		winProp_str = std::string(winProp_wstr.begin(), winProp_wstr.end());


		hMemProp = (HGLOBAL)GetProp(hwndSubclass, winProp_wstr.c_str());
		value = (char*)GlobalLock(hMemProp);
		hResult = StringCchPrintf(tchBuffer, VALUELENGTH, L"%s", value);
		GlobalUnlock(hMemProp);

		std::wstring winPropValue_wstr(tchBuffer);
		std::string winPropValue_str;
		winPropValue_str = std::string(winPropValue_wstr.begin(), winPropValue_wstr.end());

		std::cout << winProp_str << ": " << winPropValue_str << std::endl;

		CONTINUE_ENUM = TRUE;
	}

	ReleaseDC(hwndSubclass, hdc);

	return CONTINUE_ENUM;
}

void processByHandle(const HWND windowHandle, int arrow_counter) {
	auto a = EnumPropsExW(windowHandle, WinPropProc, NULL);


	for (int i = 0; i < 64000; i++) {
		HWND dialogItem = GetDlgItem(windowHandle, i);
		if (dialogItem != NULL) {
			std::cout << std::endl;
			for (int a = 0; a < arrow_counter; a++) { std::cout << "-"; };
			std::cout << "DialogItem[" << i << "]: " << std::dec << dialogItem << std::endl;
			processByHandle(dialogItem, arrow_counter + 1);
		}
	}
}

void processByHandle(const HWND windowHandle) {
	processByHandle(windowHandle, 0);
}

void processByName(const std::string_view& name) {
	std::cout << "Selected properties by process name: " << name << std::endl << std::endl;
	auto windowName = name.data();
	HWND windowHandle = FindWindowExA(NULL, NULL, windowName, NULL);
	std::cout << "WindowHandle: " << std::dec << windowHandle << std::endl;
	processByHandle(windowHandle);
}


int main(int argc, char** argv)
{
	Menu menu;
	menu.showBanner();

	ArgumentParser parser(argc, argv);

	if (!parser.validateOptions()) {
		std::cout << "Invalid combination of arguments or missing mandatory argument." << std::endl;
		menu.showUsage();
		return 1;
	}

	if (parser.hasArg("-w")) {
		std::string_view windowName = parser.getArg("-w");
		processByName(windowName);
	}

	return 0;
};