#include <iostream>
#include <windows.h>
#include <pdh.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>

#pragma comment(lib, "pdh.lib")

#ifndef PROCESSOR_ARCHITECTURE_ARM64
#define PROCESSOR_ARCHITECTURE_ARM64 12
#endif

using namespace std;

ofstream logFile; // Output file stream
bool logToFile = false; // Flag to control logging to file

// Function to initialize logging
void InitializeLogging(bool enableLogging) {
    logToFile = enableLogging;
    if (logToFile) {
        logFile.open("system_data.txt", ios::out | ios::trunc);
        if (!logFile.is_open()) {
            cerr << "Error opening file for writing." << endl;
            logToFile = false;
        }
    }
}

// Function to log output to both console and file
void LogOutput(const string& message) {
    cout << message;
    if (logToFile && logFile.is_open()) {
        logFile << message;
    }
}

// Function to set console font size
void SetConsoleFontSize(int fontSizeX, int fontSizeY) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        LogOutput("Error getting console handle.\n");
        return;
    }

    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    if (!GetCurrentConsoleFontEx(hConsole, false, &cfi)) {
        LogOutput("Error getting current console font info.\n");
        return;
    }

    cfi.dwFontSize.X = fontSizeX;
    cfi.dwFontSize.Y = fontSizeY;

    if (!SetCurrentConsoleFontEx(hConsole, false, &cfi)) {
        LogOutput("Error setting console font info.\n");
        return;
    }

    LogOutput("Console font size set to " + to_string(fontSizeX) + "x" + to_string(fontSizeY) + " pixels.\n");
}

// Function to set console text color
void SetConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Reset console text color to white
void ResetConsoleColor() {
    SetConsoleColor(15); // 15 is the default white color
}

// Function to print a border
void PrintBorder(int length) {
    for (int i = 0; i < length; ++i) {
        LogOutput("-");
    }
    LogOutput("\n");
}

// Function to print bordered text
void PrintBorderedText(const string& text, int width) {
    PrintBorder(width);
    LogOutput("| " + text);
    for (int i = text.length(); i < width - 3; ++i) {
        LogOutput(" ");
    }
    LogOutput("|\n");
    PrintBorder(width);
}

// Function to get CPU usage
string get_cpu_usage() {
    static FILETIME last_idle_time = {0}, last_kernel_time = {0}, last_user_time = {0};
    stringstream ss;

    FILETIME idle_time, kernel_time, user_time;
    if (GetSystemTimes(&idle_time, &kernel_time, &user_time)) {
        ULARGE_INTEGER idle, kernel, user;
        ULARGE_INTEGER last_idle, last_kernel, last_user;
        ULARGE_INTEGER total_time, total_diff, idle_diff;

        idle.LowPart = idle_time.dwLowDateTime;
        idle.HighPart = idle_time.dwHighDateTime;

        kernel.LowPart = kernel_time.dwLowDateTime;
        kernel.HighPart = kernel_time.dwHighDateTime;

        user.LowPart = user_time.dwLowDateTime;
        user.HighPart = user_time.dwHighDateTime;

        last_idle.LowPart = last_idle_time.dwLowDateTime;
        last_idle.HighPart = last_idle_time.dwHighDateTime;

        last_kernel.LowPart = last_kernel_time.dwLowDateTime;
        last_kernel.HighPart = last_kernel_time.dwHighDateTime;

        last_user.LowPart = last_user_time.dwLowDateTime;
        last_user.HighPart = last_user_time.dwHighDateTime;

        idle_diff.QuadPart = idle.QuadPart - last_idle.QuadPart;
        total_diff.QuadPart = (kernel.QuadPart - last_kernel.QuadPart) +
                              (user.QuadPart - last_user.QuadPart);
        idle_diff.QuadPart = total_diff.QuadPart - idle_diff.QuadPart;

        double cpu_usage = (total_diff.QuadPart == 0) ? 0.0 : ((double)idle_diff.QuadPart / (double)total_diff.QuadPart) * 100.0;

        if (cpu_usage > 75.0) {
            SetConsoleColor(12); // Red for high usage
        } else {
            SetConsoleColor(10); // Green for normal usage
        }
        PrintBorderedText("CPU Usage: " + to_string(cpu_usage) + "%", 50);
        ResetConsoleColor();
        ss << "CPU Usage: " << cpu_usage << "%\n";

        last_idle_time = idle_time;
        last_kernel_time = kernel_time;
        last_user_time = user_time;
    } else {
        SetConsoleColor(12); // Red for errors
        PrintBorderedText("Error getting system times.", 50);
        ResetConsoleColor();
        ss << "Error getting system times.\n";
    }
    return ss.str();
}

// Function to get memory usage
string get_memory_usage() {
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    stringstream ss;

    if (GlobalMemoryStatusEx(&statex)) {
        double totalMemory = statex.ullTotalPhys / (1024.0 * 1024.0);
        double freeMemory = statex.ullAvailPhys / (1024.0 * 1024.0);
        double usedMemory = totalMemory - freeMemory;
        double usedMemoryPercentage = (usedMemory / totalMemory) * 100.0;

        SetConsoleColor(15); // White for general text
        PrintBorderedText("Total Memory: " + to_string((int)totalMemory) + " MB", 50);
        ResetConsoleColor();
        ss << "Total Memory: " << totalMemory << " MB\n";

        SetConsoleColor(15); // White for general text
        LogOutput("| Used Memory: ");
        ResetConsoleColor();
        if (usedMemoryPercentage > 75.0) {
            SetConsoleColor(12); // Red for high usage
        } else {
            SetConsoleColor(10); // Green for normal usage
        }
        LogOutput(to_string(usedMemory) + " MB\n");
        ResetConsoleColor();
        PrintBorder(50);
        ss << "Used Memory: " << usedMemory << " MB\n";

        SetConsoleColor(15); // White for general text
        PrintBorderedText("Free Memory: " + to_string((int)freeMemory) + " MB", 50);
        ResetConsoleColor();
        ss << "Free Memory: " << freeMemory << " MB\n";
    } else {
        SetConsoleColor(12); // Red for errors
        PrintBorderedText("Error retrieving memory status.", 50);
        ResetConsoleColor();
        ss << "Error retrieving memory status.\n";
    }
    return ss.str();
}

// Function to get disk usage
string get_disk_usage(const std::wstring& drive) {
    ULARGE_INTEGER free_bytes_available, total_number_of_bytes, total_number_of_free_bytes;
    stringstream ss;

    if (GetDiskFreeSpaceExW(drive.c_str(), &free_bytes_available, &total_number_of_bytes, &total_number_of_free_bytes)) {
        SetConsoleColor(15); // White for general text
        PrintBorderedText("Total Size: " + to_string(total_number_of_bytes.QuadPart / (1024 * 1024 * 1024)) + " GB", 50);
        ResetConsoleColor();
        ss << "Total Size: " << total_number_of_bytes.QuadPart / (1024 * 1024 * 1024) << " GB\n";

        SetConsoleColor(15); // White for general text
        LogOutput("| Free Space: ");
        ResetConsoleColor();
        SetConsoleColor(10); // Green for values
        LogOutput(to_string(total_number_of_free_bytes.QuadPart / (1024 * 1024 * 1024)) + " GB\n");
        ResetConsoleColor();
        ss << "Free Space: " << total_number_of_free_bytes.QuadPart / (1024 * 1024 * 1024) << " GB\n";

        SetConsoleColor(15); // White for general text
        LogOutput("| Used Space: ");
        ResetConsoleColor();
        SetConsoleColor(10); // Green for values
        LogOutput(to_string((total_number_of_bytes.QuadPart - total_number_of_free_bytes.QuadPart) / (1024 * 1024 * 1024)) + " GB\n");
        ResetConsoleColor();
        ss << "Used Space: " << (total_number_of_bytes.QuadPart - total_number_of_free_bytes.QuadPart) / (1024 * 1024 * 1024) << " GB\n";
    } else {
        SetConsoleColor(12); // Red for errors
        PrintBorderedText("Error retrieving disk usage.", 50);
        ResetConsoleColor();
        ss << "Error retrieving disk usage.\n";
    }
    return ss.str();
}

// Function to get network usage
string get_network_usage() {
    PDH_HQUERY query;
    PDH_HCOUNTER counter;
    PDH_FMT_COUNTERVALUE value;
    stringstream ss;

    PdhOpenQuery(NULL, NULL, &query);
    PdhAddCounterW(query, L"\\Network Interface(*)\\Bytes Total/sec", NULL, &counter);

    PdhCollectQueryData(query);
    PdhCollectQueryData(query);
    PdhGetFormattedCounterValue(counter, PDH_FMT_LARGE, NULL, &value);

    SetConsoleColor(15); // White for general text
    PrintBorderedText("Network Usage: " + to_string(value.largeValue) + " bytes/sec", 50);
    ResetConsoleColor();
    ss << "Network Usage: " << value.largeValue << " bytes/sec\n\n\n\n";

    PdhCloseQuery(query);
    return ss.str();
}

// Function to get processor information
void get_processor_info() {
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);

    SetConsoleColor(15); // White for general text
    PrintBorderedText("Processor Architecture: ", 50);
    ResetConsoleColor();
    SetConsoleColor(10); // Green for values
    switch (sysInfo.wProcessorArchitecture) {
        case PROCESSOR_ARCHITECTURE_AMD64: LogOutput("x64 (AMD or Intel)"); break;
        case PROCESSOR_ARCHITECTURE_ARM: LogOutput("ARM"); break;
        case PROCESSOR_ARCHITECTURE_ARM64: LogOutput("ARM64"); break;
        case PROCESSOR_ARCHITECTURE_IA64: LogOutput("Intel Itanium"); break;
        case PROCESSOR_ARCHITECTURE_INTEL: LogOutput("x86"); break;
        default: LogOutput("Unknown"); break;
    }
    LogOutput("\n");
    ResetConsoleColor();

    SetConsoleColor(15); // White for general text
    PrintBorderedText("Number of Processors: " + to_string(sysInfo.dwNumberOfProcessors), 50);
    ResetConsoleColor();
}

// Function to get physical memory information
void get_physical_memory_info() {
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    if (GlobalMemoryStatusEx(&statex)) {
        SetConsoleColor(15); // White for general text
        PrintBorderedText("Physical Memory:", 50);
        ResetConsoleColor();

        SetConsoleColor(15); // White for general text
        LogOutput("| Total Physical Memory: ");
        ResetConsoleColor();
        SetConsoleColor(10); // Green for values
        LogOutput(to_string(statex.ullTotalPhys / (1024 * 1024)) + " MB\n");
        ResetConsoleColor();

        SetConsoleColor(15); // White for general text
        LogOutput("| Available Physical Memory: ");
        ResetConsoleColor();
        SetConsoleColor(10); // Green for values
        LogOutput(to_string(statex.ullAvailPhys / (1024 * 1024)) + " MB\n");
        ResetConsoleColor();
        PrintBorder(50);
    } else {
        SetConsoleColor(12); // Red for errors
        PrintBorderedText("Error retrieving physical memory status.", 50);
        ResetConsoleColor();
    }
}

// Function to list logical drives
void list_logical_drives() {
    DWORD drive_mask = GetLogicalDrives();
    if (drive_mask == 0) {
        SetConsoleColor(12); // Red for errors
        PrintBorderedText("Error getting logical drives.", 50);
        ResetConsoleColor();
        return;
    }

    SetConsoleColor(15); // White for general text
    PrintBorderedText("Logical Drives:", 50);
    ResetConsoleColor();
    for (char drive = 'A'; drive <= 'Z'; ++drive) {
        if (drive_mask & (1 << (drive - 'A'))) {
            LogOutput("| " + string(1, drive) + ":\\\\" + "\n");
        }
    }
    PrintBorder(50);
}

// Main menu display function
void Main_Menu_Display() {
    system("cls");

    SetConsoleColor(11); // Light cyan for menu text
    PrintBorderedText("[+] Press <Sys> to open live system Monitoring", 50);
    PrintBorderedText("[+] Press <Info> to display hardware information", 50);
    ResetConsoleColor();

    string choice;
    cout << "\n>";
    cin >> choice;

    if (choice == "Sys") {
        InitializeLogging(true); // Enable logging to file
        while (true) {
            system("cls"); // Clear the console
            SetConsoleColor(11); // Light cyan for section headers
            
            PrintBorderedText("System Monitoring:", 50);
            ResetConsoleColor();
            string cpu_data = get_cpu_usage();
            string memory_data = get_memory_usage();
            string disk_data = get_disk_usage(L"C:\\");
            string network_data = get_network_usage();
            Sleep(1000); // Wait for 1 second before the next update
        }
    
    } else if (choice == "Info") {
        InitializeLogging(true); // Enable logging to file
        get_processor_info();
        get_physical_memory_info();
        list_logical_drives();
        LogOutput("\n\n\n");
        system("systeminfo");
    } else {
        SetConsoleColor(12); // Red for errors
        PrintBorderedText("Invalid choice.", 50);
        ResetConsoleColor();
    }

    if (logToFile) {
        logFile.close();
    }
}

// Main function to run the monitoring
int main() {
    SetConsoleFontSize(24, 24);
    Main_Menu_Display();
    return 0;
}





//add colors red and green in temperatures, threads they use, disk , ram and more,.....,
//add external library to add temperatures and more , also add historyb  of metricks and save to file option



