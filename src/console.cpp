#include "pch.h"

#include "console.h"
#include "version.inl"

namespace pluginloader::console {

void create_if_needed(void) {
    const std::string args{GetCommandLineA()};
    if (args.find("--debug") == std::string::npos) {
        return;
    }

    // Taken from https://github.com/FromDarkHell/BL3DX11Injection/
    AllocConsole();
    SetConsoleTitleA("Plugin Loader Debug Console");

    // All of this is necessary so that way we can properly use the output of the console
    // NOLINTBEGIN(misc-const-correctness) - clang tidy 21.1.x false positive
    FILE* new_stdin = nullptr;
    FILE* new_stdout = nullptr;
    FILE* new_stderr = nullptr;
    // NOLINTEND(misc-const-correctness)
    freopen_s(&new_stdin, "CONIN$", "r", stdin);
    freopen_s(&new_stdout, "CONOUT$", "w", stdout);
    freopen_s(&new_stderr, "CONOUT$", "w", stderr);

    HANDLE stdout_handle =
        CreateFileA("CONOUT$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
                    nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    HANDLE stdin_handle =
        CreateFileA("CONIN$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
                    nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

    // Make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog point to the console as well
    std::ios::sync_with_stdio(true);

    SetStdHandle(STD_INPUT_HANDLE, stdin_handle);
    SetStdHandle(STD_OUTPUT_HANDLE, stdout_handle);  // Set our STD handles
    SetStdHandle(STD_ERROR_HANDLE, stdout_handle);   // stderr is going back to STDOUT

    // Clear the error states for all of the C++ stream objects.
    // Attempting to access the streams before they're valid causes them to enter an error state.
    std::wcout.clear();
    std::cout.clear();
    std::wcerr.clear();
    std::cerr.clear();
    std::wcin.clear();
    std::cin.clear();

    std::cout << "Pluginloader v" << PROJECT_VERSION_MAJOR << '.' << PROJECT_VERSION_MINOR << '.'
              << PROJECT_VERSION_PATCH << '\n'
              << std::flush;
}

}  // namespace pluginloader::console
