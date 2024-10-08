#include "pch.h"

#include "console.h"
#include "loader.h"
#include "proxy/proxy.h"

/**
 * @brief Main entry point.
 *
 * @param h_module Handle to module for this dll.
 * @param ul_reason_for_call Reason this is being called.
 * @return True if loaded successfully, false otherwise.
 */
// NOLINTNEXTLINE(misc-use-internal-linkage, readability-identifier-naming)  - for `DllMain`
BOOL APIENTRY DllMain(HMODULE h_module, DWORD ul_reason_for_call, LPVOID /*unused*/) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(h_module);

            pluginloader::console::create_if_needed();
            pluginloader::proxy::init(h_module);
            pluginloader::loader::load(h_module);

            break;
        case DLL_PROCESS_DETACH:
            pluginloader::loader::free();
            pluginloader::proxy::free();
            break;
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
            break;
    }
    return TRUE;
}
