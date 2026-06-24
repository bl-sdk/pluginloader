#include "pch.h"

#include "proxy.h"
#include "util.h"

namespace pluginloader::proxy {

namespace {

HMODULE dinput8_dll_handle = nullptr;

FARPROC direct_input8_create_ptr = nullptr;
FARPROC dll_can_unload_now_ptr = nullptr;
FARPROC dll_get_class_object_ptr = nullptr;
FARPROC dll_register_server_ptr = nullptr;
FARPROC dll_unregister_server_ptr = nullptr;
FARPROC get_df_di_joystick_ptr = nullptr;

}  // namespace

// NOLINTBEGIN(readability-identifier-naming)

#ifdef __MINGW32__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-function-type"
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcast-function-type-mismatch"
#endif

// #include "dsound.h"

DLL_EXPORT HRESULT WINAPI DirectInput8Create(HINSTANCE hinst,
                                             DWORD dwVersion,
                                             REFIID riidltf,
                                             LPVOID* ppvOut,
                                             void* punkOuter) {
    return reinterpret_cast<decltype(&DirectInput8Create)>(direct_input8_create_ptr)(
        hinst, dwVersion, riidltf, ppvOut, punkOuter);
}

DLL_EXPORT HRESULT WINAPI DllCanUnloadNow(void) {
    return reinterpret_cast<decltype(&DllCanUnloadNow)>(dll_can_unload_now_ptr)();
}

DLL_EXPORT HRESULT WINAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv) {
    return reinterpret_cast<decltype(&DllGetClassObject)>(dll_get_class_object_ptr)(rclsid, riid,
                                                                                    ppv);
}

DLL_EXPORT HRESULT STDAPICALLTYPE DllRegisterServer(void) {
    return reinterpret_cast<decltype(&DllRegisterServer)>(dll_register_server_ptr)();
}

DLL_EXPORT HRESULT STDAPICALLTYPE DllUnregisterServer(void) {
    return reinterpret_cast<decltype(&DllUnregisterServer)>(dll_unregister_server_ptr)();
}

DLL_EXPORT void* WINAPI GetdfDIJoystick(void) {
    return reinterpret_cast<decltype(&GetdfDIJoystick)>(get_df_di_joystick_ptr)();
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif
#ifdef __MINGW32__
#pragma GCC diagnostic pop
#endif

// NOLINTEND(readability-identifier-naming)

void init(HMODULE /*this_dll*/) {
    // Suspend all other threads to prevent a giant race condition
    const util::ThreadSuspender suspender{};

    wchar_t buf[MAX_PATH];
    if (GetSystemDirectoryW(&buf[0], ARRAYSIZE(buf)) == 0) {
        std::cerr << "Unable to find system dll directory! We're probably about to crash.\n";
        return;
    }

    auto system_dinput8 = std::filesystem::path{static_cast<wchar_t*>(buf)} / "dinput8.dll";
    dinput8_dll_handle = LoadLibraryA(system_dinput8.generic_string().c_str());
    if (dinput8_dll_handle == nullptr) {
        std::cerr << "Unable to find system dinput8.dll! We're probably about to crash.\n";
        return;
    }

    direct_input8_create_ptr = GetProcAddress(dinput8_dll_handle, "DirectInput8Create");
    dll_can_unload_now_ptr = GetProcAddress(dinput8_dll_handle, "DllCanUnloadNow");
    dll_get_class_object_ptr = GetProcAddress(dinput8_dll_handle, "DllGetClassObject");
    dll_register_server_ptr = GetProcAddress(dinput8_dll_handle, "DllRegisterServer");
    dll_unregister_server_ptr = GetProcAddress(dinput8_dll_handle, "DllUnregisterServer");
    get_df_di_joystick_ptr = GetProcAddress(dinput8_dll_handle, "GetdfDIJoystick");
}

void free(void) {
    if (dinput8_dll_handle != nullptr) {
        FreeLibrary(dinput8_dll_handle);
        dinput8_dll_handle = nullptr;
    }
}

}  // namespace pluginloader::proxy
