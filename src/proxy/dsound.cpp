#include "pch.h"

#include "proxy.h"
#include "util.h"

namespace pluginloader::proxy {

namespace {

HMODULE dsound_dll_handle = nullptr;

FARPROC direct_sound_create_ptr = nullptr;
FARPROC direct_sound_enumerate_a_ptr = nullptr;
FARPROC direct_sound_enumerate_w_ptr = nullptr;
FARPROC dll_can_unload_now_ptr = nullptr;
FARPROC dll_get_class_object_ptr = nullptr;
FARPROC direct_sound_capture_create_ptr = nullptr;
FARPROC direct_sound_capture_enumerate_a_ptr = nullptr;
FARPROC direct_sound_capture_enumerate_w_ptr = nullptr;
FARPROC get_device_id_ptr = nullptr;
FARPROC direct_sound_full_duplex_create_ptr = nullptr;
FARPROC direct_sound_create_8_ptr = nullptr;
FARPROC direct_sound_capture_create_8_ptr = nullptr;

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

DLL_EXPORT HRESULT WINAPI DirectSoundCreate(LPCGUID pcGuidDevice, void* ppDS, void* pUnkOuter) {
    return reinterpret_cast<decltype(&DirectSoundCreate)>(direct_sound_create_ptr)(pcGuidDevice,
                                                                                   ppDS, pUnkOuter);
}

DLL_EXPORT HRESULT WINAPI DirectSoundEnumerateA(void* pDSEnumCallback, LPVOID pContext) {
    return reinterpret_cast<decltype(&DirectSoundEnumerateA)>(direct_sound_enumerate_a_ptr)(
        pDSEnumCallback, pContext);
}

DLL_EXPORT HRESULT WINAPI DirectSoundEnumerateW(void* pDSEnumCallback, LPVOID pContext) {
    return reinterpret_cast<decltype(&DirectSoundEnumerateW)>(direct_sound_enumerate_w_ptr)(
        pDSEnumCallback, pContext);
}

DLL_EXPORT HRESULT WINAPI DllCanUnloadNow(void) {
    return reinterpret_cast<decltype(&DllCanUnloadNow)>(dll_can_unload_now_ptr)();
}

DLL_EXPORT HRESULT WINAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv) {
    return reinterpret_cast<decltype(&DllGetClassObject)>(dll_get_class_object_ptr)(rclsid, riid,
                                                                                    ppv);
}

DLL_EXPORT HRESULT WINAPI DirectSoundCaptureCreate(LPCGUID pcGuidDevice,
                                                   void** ppDSC,
                                                   void* pUnkOuter) {
    return reinterpret_cast<decltype(&DirectSoundCaptureCreate)>(direct_sound_capture_create_ptr)(
        pcGuidDevice, ppDSC, pUnkOuter);
}

DLL_EXPORT HRESULT WINAPI DirectSoundCaptureEnumerateA(void* pDSEnumCallback, LPVOID pContext) {
    return reinterpret_cast<decltype(&DirectSoundCaptureEnumerateA)>(
        direct_sound_capture_enumerate_a_ptr)(pDSEnumCallback, pContext);
}

DLL_EXPORT HRESULT WINAPI DirectSoundCaptureEnumerateW(void* pDSEnumCallback, LPVOID pContext) {
    return reinterpret_cast<decltype(&DirectSoundCaptureEnumerateW)>(
        direct_sound_capture_enumerate_w_ptr)(pDSEnumCallback, pContext);
}

DLL_EXPORT HRESULT WINAPI GetDeviceID(LPCGUID pGuidSrc, LPGUID pGuidDest) {
    return reinterpret_cast<decltype(&GetDeviceID)>(get_device_id_ptr)(pGuidSrc, pGuidDest);
}

DLL_EXPORT HRESULT WINAPI DirectSoundFullDuplexCreate(LPCGUID pcGuidCaptureDevice,
                                                      LPCGUID pcGuidRenderDevice,
                                                      void* pcDSCBufferDesc,
                                                      void* pcDSBufferDesc,
                                                      HWND hWnd,
                                                      DWORD dwLevel,
                                                      void** ppDSFD,
                                                      void** ppDSCBuffer8,
                                                      void** ppDSBuffer8,
                                                      void* pUnkOuter) {
    return reinterpret_cast<decltype(&DirectSoundFullDuplexCreate)>(
        direct_sound_full_duplex_create_ptr)(pcGuidCaptureDevice, pcGuidRenderDevice,
                                             pcDSCBufferDesc, pcDSBufferDesc, hWnd, dwLevel, ppDSFD,
                                             ppDSCBuffer8, ppDSBuffer8, pUnkOuter);
}

DLL_EXPORT HRESULT WINAPI DirectSoundCreate8(LPCGUID pcGuidDevice, void** ppDS8, void* pUnkOuter) {
    return reinterpret_cast<decltype(&DirectSoundCreate8)>(direct_sound_create_8_ptr)(
        pcGuidDevice, ppDS8, pUnkOuter);
}

DLL_EXPORT HRESULT WINAPI DirectSoundCaptureCreate8(LPCGUID pcGuidDevice,
                                                    void** ppDSC8,
                                                    void* pUnkOuter) {
    return reinterpret_cast<decltype(&DirectSoundCaptureCreate8)>(
        direct_sound_capture_create_8_ptr)(pcGuidDevice, ppDSC8, pUnkOuter);
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

    auto system_dsound = std::filesystem::path{static_cast<wchar_t*>(buf)} / "dsound.dll";
    dsound_dll_handle = LoadLibraryA(system_dsound.generic_string().c_str());
    if (dsound_dll_handle == nullptr) {
        std::cerr << "Unable to find system dsound.dll! We're probably about to crash.\n";
        return;
    }

    direct_sound_create_ptr = GetProcAddress(dsound_dll_handle, "DirectSoundCreate");
    direct_sound_enumerate_a_ptr = GetProcAddress(dsound_dll_handle, "DirectSoundEnumerateA");
    direct_sound_enumerate_w_ptr = GetProcAddress(dsound_dll_handle, "DirectSoundEnumerateW");
    dll_can_unload_now_ptr = GetProcAddress(dsound_dll_handle, "DllCanUnloadNow");
    dll_get_class_object_ptr = GetProcAddress(dsound_dll_handle, "DllGetClassObject");
    direct_sound_capture_create_ptr = GetProcAddress(dsound_dll_handle, "DirectSoundCaptureCreate");
    direct_sound_capture_enumerate_a_ptr =
        GetProcAddress(dsound_dll_handle, "DirectSoundCaptureEnumerateA");
    direct_sound_capture_enumerate_w_ptr =
        GetProcAddress(dsound_dll_handle, "DirectSoundCaptureEnumerateW");
    get_device_id_ptr = GetProcAddress(dsound_dll_handle, "GetDeviceID");
    direct_sound_full_duplex_create_ptr =
        GetProcAddress(dsound_dll_handle, "DirectSoundFullDuplexCreate");
    direct_sound_create_8_ptr = GetProcAddress(dsound_dll_handle, "DirectSoundCreate8");
    direct_sound_capture_create_8_ptr =
        GetProcAddress(dsound_dll_handle, "DirectSoundCaptureCreate8");
}

void free(void) {
    if (dsound_dll_handle != nullptr) {
        FreeLibrary(dsound_dll_handle);
        dsound_dll_handle = nullptr;
    }
}

}  // namespace pluginloader::proxy
