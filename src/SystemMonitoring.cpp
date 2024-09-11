//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <windows.h>
#include <SysUtils.hpp> // For IntToStr
#include <Lmcons.h>      // For UNLEN constant
#include <Psapi.h> // For CPU usage functions
#include <Vcl.Graphics.hpp> // For TCanvas and drawing
#include <stdlib.h>  // For rand()

#pragma comment(lib, "Psapi.lib") // Link with Psapi library

#include "SystemMonitoring.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "perfgrap"
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------





__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
 Memo1->Lines->Text =
        "MIT License\n\n"
        "Copyright (c) 2024 Panagiotis Kotsorgios\n\n"
        "Permission is hereby granted, free of charge, to any person obtaining a copy\n"
        "of this software and associated documentation files (the \"Software\"), to deal\n"
        "in the Software without restriction, including without limitation the rights\n"
        "to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n"
        "copies of the Software, and to permit persons to whom the Software is\n"
        "furnished to do so, subject to the following conditions:\n\n"
        "The above copyright notice and this permission notice shall be included in all\n"
        "copies or substantial portions of the Software.\n\n"
        "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n"
        "IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n"
        "FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n"
        "AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n"
        "LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n"
        "OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n"
        "SOFTWARE.\n";



         // Creator information and GitHub details in Memo2
    Memo2->Lines->Text =
        "Creator Information\n\n"
        "Name: Panagiotis Kotsorgios\n"
		"Email: pkotsorgios654@gmail.com\n\n"
        "GitHub Repository:\n"
		"https://github.com/PanagiotisKots/System-Monitoring\n";





         SYSTEM_INFO siSysInfo;

    // Get system information
    GetSystemInfo(&siSysInfo);

    // Prepare a string with processor information
    String procInfo = "Processor Architecture: ";

    switch (siSysInfo.wProcessorArchitecture)
    {
        case PROCESSOR_ARCHITECTURE_AMD64:
            procInfo += "x64 (AMD or Intel)";
            break;
        case PROCESSOR_ARCHITECTURE_ARM:
            procInfo += "ARM";
            break;
        case PROCESSOR_ARCHITECTURE_IA64:
            procInfo += "Intel Itanium-based";
            break;
        case PROCESSOR_ARCHITECTURE_INTEL:
            procInfo += "x86";
            break;
        default:
            procInfo += "Unknown Architecture";
            break;
    }

    // Convert DWORD (unsigned long) to int explicitly for IntToStr
    procInfo += "\nNumber of Processors: " + IntToStr(static_cast<int>(siSysInfo.dwNumberOfProcessors));

    // Set the text in Edit1 at startup
	Edit1->Text = procInfo;









   // Retrieve the user name of the PC using wide characters
    WCHAR userName[256];
    DWORD userNameSize = sizeof(userName) / sizeof(WCHAR);  // Size in wide characters
    if (GetUserNameW(userName, &userNameSize))
    {
        // Set the user name in Edit2 at startup
        Edit2->Text = String("User Name: ") + UnicodeString(userName);
    }
    else
    {
        // If there was an error retrieving the username, display an error message
        Edit2->Text = "Unable to retrieve user name.";
    }







	// Retrieve total RAM memory
	MEMORYSTATUSEX memStatus;
	memStatus.dwLength = sizeof(MEMORYSTATUSEX);

	if (GlobalMemoryStatusEx(&memStatus))
	{
		// Convert total RAM from bytes to gigabytes and format it
		String totalRAM = "Total RAM: " + FloatToStrF(memStatus.ullTotalPhys / (1024.0 * 1024.0 * 1024.0), ffFixed, 1, 2) + " GB";
		Edit4->Text = totalRAM;
	}
	else
	{
		// If there was an error retrieving memory status, display an error message
		Edit4->Text = "Unable to retrieve RAM information.";
	}






  ProgressBar1->Min = 0;
    ProgressBar1->Max = 100;
    ProgressBar1->Position = 0;

    ProgressBar3->Min = 0;
    ProgressBar3->Max = 100;
    ProgressBar3->Position = 0;

    Timer1->Interval = 3000;
	Timer1->OnTimer = Timer1Timer;
	Timer1->Enabled = true;


	Timer1Timer(this);


   // Optionally set up initial properties for PerformanceGraph1


}




//---------------------------------------------------------------------------
void __fastcall TForm3::Button2Click(TObject *Sender)
{
Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button1Click(TObject *Sender)
{
	MessageBox(0, L"OK button was pressed.", L"Info", MB_OK);
}
//---------------------------------------------------------------------------


void __fastcall TForm3::Edit1Change(TObject *Sender)
{
SYSTEM_INFO siSysInfo;

    // Get system information
    GetSystemInfo(&siSysInfo);

    // Prepare a string with processor information
    String procInfo = "Processor Architecture: ";

    switch (siSysInfo.wProcessorArchitecture)
    {
        case PROCESSOR_ARCHITECTURE_AMD64:
            procInfo += "x64 (AMD or Intel)";
            break;
        case PROCESSOR_ARCHITECTURE_ARM:
            procInfo += "ARM";
            break;
        case PROCESSOR_ARCHITECTURE_IA64:
            procInfo += "Intel Itanium-based";
            break;
        case PROCESSOR_ARCHITECTURE_INTEL:
            procInfo += "x86";
            break;
        default:
            procInfo += "Unknown Architecture";
            break;
    }

    // Convert DWORD (unsigned long) to int explicitly for IntToStr
    procInfo += "\nNumber of Processors: " + IntToStr(static_cast<int>(siSysInfo.dwNumberOfProcessors));

    // Print the processor information into Edit1
	Edit1->Text = procInfo;
}
//---------------------------------------------------------------------------




void __fastcall TForm3::Edit2Change(TObject *Sender)
{



   // Retrieve the user name of the PC using wide characters
    WCHAR userName[256];
    DWORD userNameSize = sizeof(userName) / sizeof(WCHAR);  // Size in wide characters
    if (GetUserNameW(userName, &userNameSize))
    {
        // Set the user name in Edit2 at startup
        Edit2->Text = String("User Name: ") + UnicodeString(userName);
    }
    else
    {
        // If there was an error retrieving the username, display an error message
        Edit2->Text = "Unable to retrieve user name.";
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Edit4Change(TObject *Sender)
{
              // Retrieve total RAM memory
	MEMORYSTATUSEX memStatus;
	memStatus.dwLength = sizeof(MEMORYSTATUSEX);

	if (GlobalMemoryStatusEx(&memStatus))
	{
		// Convert total RAM from bytes to gigabytes and format it
		String totalRAM = "Total RAM: " + FloatToStrF(memStatus.ullTotalPhys / (1024.0 * 1024.0 * 1024.0), ffFixed, 1, 2) + " GB";
		Edit4->Text = totalRAM;
	}
	else
	{
		// If there was an error retrieving memory status, display an error message
		Edit4->Text = "Unable to retrieve RAM information.";
	}

}
//---------------------------------------------------------------------------


void __fastcall TForm3::Timer1Timer(TObject *Sender)
{
    static ULARGE_INTEGER prevIdleTime = {0};
    static ULARGE_INTEGER prevKernelTime = {0};
    static ULARGE_INTEGER prevUserTime = {0};
    // Calculate CPU usage
    FILETIME idleTime, kernelTime, userTime;
    GetSystemTimes(&idleTime, &kernelTime, &userTime);
    ULARGE_INTEGER currentIdleTime, currentKernelTime, currentUserTime;
    currentIdleTime.LowPart = idleTime.dwLowDateTime;
    currentIdleTime.HighPart = idleTime.dwHighDateTime;
    currentKernelTime.LowPart = kernelTime.dwLowDateTime;
    currentKernelTime.HighPart = kernelTime.dwHighDateTime;
    currentUserTime.LowPart = userTime.dwLowDateTime;
    currentUserTime.HighPart = userTime.dwHighDateTime;
    ULONGLONG idleTicks = currentIdleTime.QuadPart - prevIdleTime.QuadPart;
    ULONGLONG kernelTicks = currentKernelTime.QuadPart - prevKernelTime.QuadPart;
    ULONGLONG userTicks = currentUserTime.QuadPart - prevUserTime.QuadPart;
    ULONGLONG totalTicks = kernelTicks + userTicks;
    double cpuUsage = 0.0;
    if (totalTicks > 0)
    {
        cpuUsage = 100.0 * (totalTicks - idleTicks) / totalTicks;
    }
    // Update CPU usage UI
    ProgressBar1->Position = static_cast<int>(cpuUsage);
    Edit3->Text = FloatToStrF(cpuUsage, ffFixed, 1, 2) + " %";
    // Calculate RAM usage
    MEMORYSTATUSEX memStatus;
    memStatus.dwLength = sizeof(MEMORYSTATUSEX);
    if (GlobalMemoryStatusEx(&memStatus))
    {
        // Calculate RAM usage percentage
        double ramUsage = 100.0 - (100.0 * memStatus.ullAvailPhys / memStatus.ullTotalPhys);
        // Update RAM usage UI
        ProgressBar3->Position = static_cast<int>(ramUsage);
        Edit5->Text = FloatToStrF(ramUsage, ffFixed, 1, 2) + " %";
    }
    else
    {
        // Error handling
        ProgressBar3->Position = 0;
        Edit5->Text = "Error retrieving RAM info";
    }

    // Save current times for the next calculation
    prevIdleTime = currentIdleTime;
    prevKernelTime = currentKernelTime;
    prevUserTime = currentUserTime;
}






//---------------------------------------------------------------------------



