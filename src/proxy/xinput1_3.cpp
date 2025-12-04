#include "pch.h"

#include "proxy.h"
#include "util.h"

namespace pluginloader::proxy {

namespace {

HMODULE xinput_dll_handle = nullptr;

FARPROC xinput_enable_ptr = nullptr;
FARPROC xinput_get_battery_information_ptr = nullptr;
FARPROC xinput_get_capabilities_ptr = nullptr;
FARPROC xinput_get_dsound_audio_device_guids_ptr = nullptr;
FARPROC xinput_get_keystroke_ptr = nullptr;
FARPROC xinput_get_state_ptr = nullptr;
FARPROC xinput_set_state_ptr = nullptr;

const constexpr uintptr_t XINPUT_GET_STATE_EX_ORDINAL = 100;
FARPROC xinput_get_state_ex_ptr = nullptr;
const constexpr uintptr_t XINPUT_WAIT_FOR_GUIDE_BUTTON_ORDINAL = 101;
FARPROC xinput_wait_for_guide_button_ptr = nullptr;
const constexpr uintptr_t XINPUT_CANCEL_GUIDE_BUTTON_WAIT_ORDINAL = 102;
FARPROC xinput_cancel_guide_button_wait_ptr = nullptr;
const constexpr uintptr_t XINPUT_POWER_OFF_CONTROLLER_ORDINAL = 103;
FARPROC xinput_power_off_controller_ptr = nullptr;

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

DLL_EXPORT void XInputEnable(BOOL enable) {
    reinterpret_cast<decltype(&XInputEnable)>(xinput_enable_ptr)(enable);
}

DLL_EXPORT DWORD XInputGetBatteryInformation(DWORD dwUserIndex,
                                             BYTE devType,
                                             void* pBatteryInformation) {
    return reinterpret_cast<decltype(&XInputGetBatteryInformation)>(
        xinput_get_battery_information_ptr)(dwUserIndex, devType, pBatteryInformation);
}

DLL_EXPORT DWORD XInputGetCapabilities(DWORD dwUserIndex, DWORD dwFlags, void* pCapabilities) {
    return reinterpret_cast<decltype(&XInputGetCapabilities)>(xinput_get_capabilities_ptr)(
        dwUserIndex, dwFlags, pCapabilities);
}

DLL_EXPORT DWORD XInputGetDSoundAudioDeviceGuids(DWORD dwUserIndex,
                                                 GUID* pDSoundRenderGuid,
                                                 GUID* pDSoundCaptureGuid) {
    return reinterpret_cast<decltype(&XInputGetDSoundAudioDeviceGuids)>(
        xinput_get_dsound_audio_device_guids_ptr)(dwUserIndex, pDSoundRenderGuid,
                                                  pDSoundCaptureGuid);
}

DLL_EXPORT DWORD XInputGetKeystroke(DWORD dwUserIndex, DWORD dwReserved, void* pKeystroke) {
    return reinterpret_cast<decltype(&XInputGetKeystroke)>(xinput_get_keystroke_ptr)(
        dwUserIndex, dwReserved, pKeystroke);
}

DLL_EXPORT DWORD XInputGetState(DWORD dwUserIndex, void* pState) {
    return reinterpret_cast<decltype(&XInputGetState)>(xinput_get_state_ptr)(dwUserIndex, pState);
}

DLL_EXPORT DWORD XInputSetState(DWORD dwUserIndex, void* pVibration) {
    return reinterpret_cast<decltype(&XInputSetState)>(xinput_set_state_ptr)(dwUserIndex,
                                                                             pVibration);
}

DLL_EXPORT DWORD XInputGetStateEx(DWORD dwUserIndex, void* pState) {
    return reinterpret_cast<decltype(&XInputGetStateEx)>(xinput_get_state_ex_ptr)(dwUserIndex,
                                                                                  pState);
}

DLL_EXPORT DWORD XInputWaitForGuideButton(DWORD dwUserIndex, DWORD dwFlag, LPVOID pVoid) {
    return reinterpret_cast<decltype(&XInputWaitForGuideButton)>(xinput_wait_for_guide_button_ptr)(
        dwUserIndex, dwFlag, pVoid);
}

DLL_EXPORT DWORD XInputCancelGuideButtonWait(DWORD dwUserIndex) {
    return reinterpret_cast<decltype(&XInputCancelGuideButtonWait)>(
        xinput_cancel_guide_button_wait_ptr)(dwUserIndex);
}

DLL_EXPORT DWORD XInputPowerOffController(DWORD dwUserIndex) {
    return reinterpret_cast<decltype(&XInputPowerOffController)>(xinput_power_off_controller_ptr)(
        dwUserIndex);
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

    auto system_xinput = std::filesystem::path{static_cast<wchar_t*>(buf)} / "xinput1_3.dll";
    xinput_dll_handle = LoadLibraryA(system_xinput.generic_string().c_str());
    if (xinput_dll_handle == nullptr) {
        std::cerr << "Unable to find system xinput1_3.dll! We're probably about to crash.\n";
        return;
    }

    xinput_enable_ptr = GetProcAddress(xinput_dll_handle, "XInputEnable");
    xinput_get_battery_information_ptr =
        GetProcAddress(xinput_dll_handle, "XInputGetBatteryInformation");
    xinput_get_capabilities_ptr = GetProcAddress(xinput_dll_handle, "XInputGetCapabilities");
    xinput_get_dsound_audio_device_guids_ptr =
        GetProcAddress(xinput_dll_handle, "XInputGetDSoundAudioDeviceGuids");
    xinput_get_keystroke_ptr = GetProcAddress(xinput_dll_handle, "XInputGetKeystroke");
    xinput_get_state_ptr = GetProcAddress(xinput_dll_handle, "XInputGetState");
    xinput_set_state_ptr = GetProcAddress(xinput_dll_handle, "XInputSetState");

    xinput_get_state_ex_ptr =
        GetProcAddress(xinput_dll_handle, reinterpret_cast<LPCSTR>(XINPUT_GET_STATE_EX_ORDINAL));
    xinput_wait_for_guide_button_ptr = GetProcAddress(
        xinput_dll_handle, reinterpret_cast<LPCSTR>(XINPUT_WAIT_FOR_GUIDE_BUTTON_ORDINAL));
    xinput_cancel_guide_button_wait_ptr = GetProcAddress(
        xinput_dll_handle, reinterpret_cast<LPCSTR>(XINPUT_CANCEL_GUIDE_BUTTON_WAIT_ORDINAL));
    xinput_power_off_controller_ptr = GetProcAddress(
        xinput_dll_handle, reinterpret_cast<LPCSTR>(XINPUT_POWER_OFF_CONTROLLER_ORDINAL));
}

void free(void) {
    if (xinput_dll_handle != nullptr) {
        FreeLibrary(xinput_dll_handle);
        xinput_dll_handle = nullptr;
    }
}

}  // namespace pluginloader::proxy
