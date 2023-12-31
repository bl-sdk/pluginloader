#ifndef PROXY_PROXY_H
#define PROXY_PROXY_H

#include "pch.h"

namespace pluginloader::proxy {

/**
 * @brief Initialize the dll hijack proxy.
 *
 * @param this_dll Handle to this dll's module.
 */
void init(HMODULE this_dll);

/**
 * @brief Frees the dll hijack proxy.
 */
void free(void);

}  // namespace pluginloader::proxy

#endif /* PROXY_PROXY_H */
