#include "pch.h"

#include "proxy.h"
#include "util.h"

// Based on https://github.com/FromDarkHell/BL3DX11Injection/

namespace pluginloader::proxy {

namespace {

HMODULE dx11_dll_handle = nullptr;

FARPROC d3d11_core_create_device_ptr = nullptr;
FARPROC d3d11_create_device_ptr = nullptr;
FARPROC d3d11_create_device_and_swap_chain_ptr = nullptr;
FARPROC d3d11_on_12_create_device_ptr = nullptr;

}  // namespace

// NOLINTBEGIN(readability-identifier-naming, readability-identifier-length)

#ifdef __MINGW32__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-function-type"
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcast-function-type-mismatch"
#endif

DLL_EXPORT HRESULT D3D11CoreCreateDevice(void* fact,
                                         void* adapt,
                                         UINT flag,
                                         void* fl,
                                         UINT featureLevels,
                                         void** ppDev) {
    return reinterpret_cast<decltype(&D3D11CoreCreateDevice)>(d3d11_core_create_device_ptr)(
        fact, adapt, flag, fl, featureLevels, ppDev);
}

DLL_EXPORT HRESULT D3D11CreateDevice(void* adapt,
                                     UINT dt,
                                     void* soft,
                                     UINT flags,
                                     int* ft,
                                     UINT fl,
                                     UINT ver,
                                     void** ppDevice,
                                     void* featureLevel,
                                     void** context) {
    return reinterpret_cast<decltype(&D3D11CreateDevice)>(d3d11_create_device_ptr)(
        adapt, dt, soft, flags, ft, fl, ver, ppDevice, featureLevel, context);
}

DLL_EXPORT HRESULT D3D11CreateDeviceAndSwapChain(void* adapt,
                                                 UINT dt,
                                                 void* soft,
                                                 UINT flags,
                                                 int* ft,
                                                 UINT fl,
                                                 UINT ver,
                                                 void* swapChainDesc,
                                                 void** swapChain,
                                                 void** ppDevice,
                                                 void* featureLevel,
                                                 void** context) {
    return reinterpret_cast<decltype(&D3D11CreateDeviceAndSwapChain)>(
        d3d11_create_device_and_swap_chain_ptr)(adapt, dt, soft, flags, ft, fl, ver, swapChainDesc,
                                                swapChain, ppDevice, featureLevel, context);
}

DLL_EXPORT HRESULT D3D11On12CreateDevice(void* pDevice,
                                         UINT Flags,
                                         void* pFeatureLevels,
                                         UINT FeatureLevels,
                                         void** ppCommandQueues,
                                         UINT NumQueues,
                                         UINT NodeMask,
                                         void** ppDevice,
                                         void** ppImmediateContext,
                                         void* pChosenFeatureLevel) {
    return reinterpret_cast<decltype(&D3D11On12CreateDevice)>(d3d11_on_12_create_device_ptr)(
        pDevice, Flags, pFeatureLevels, FeatureLevels, ppCommandQueues, NumQueues, NodeMask,
        ppDevice, ppImmediateContext, pChosenFeatureLevel);
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif
#ifdef __MINGW32__
#pragma GCC diagnostic pop
#endif

// NOLINTEND(readability-identifier-naming, readability-identifier-length)

void init(HMODULE /*this_dll*/) {
    // Suspend all other threads to prevent a giant race condition
    const util::ThreadSuspender suspender{};

    wchar_t buf[MAX_PATH];
    if (GetSystemDirectoryW(&buf[0], ARRAYSIZE(buf)) == 0) {
        std::cerr << "Unable to find system dll directory! We're probably about to crash.\n";
        return;
    }

    auto system_dx11 = std::filesystem::path{static_cast<wchar_t*>(buf)} / "d3d11.dll";
    dx11_dll_handle = LoadLibraryA(system_dx11.generic_string().c_str());
    if (dx11_dll_handle == nullptr) {
        std::cerr << "Unable to find system d3d11.dll! We're probably about to crash.\n";
        return;
    }

    d3d11_core_create_device_ptr = GetProcAddress(dx11_dll_handle, "D3D11CoreCreateDevice");
    d3d11_create_device_ptr = GetProcAddress(dx11_dll_handle, "D3D11CreateDevice");
    d3d11_create_device_and_swap_chain_ptr =
        GetProcAddress(dx11_dll_handle, "D3D11CreateDeviceAndSwapChain");
    d3d11_on_12_create_device_ptr = GetProcAddress(dx11_dll_handle, "D3D11On12CreateDevice");
}

void free(void) {
    if (dx11_dll_handle != nullptr) {
        FreeLibrary(dx11_dll_handle);
        dx11_dll_handle = nullptr;
    }
}

}  // namespace pluginloader::proxy
