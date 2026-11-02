#include "pch.h"

#include "proxy.h"
#include "util.h"

namespace pluginloader::proxy {

namespace {

HMODULE wsock32_dll_handle = nullptr;

FARPROC accept_ptr = nullptr;
FARPROC bind_ptr = nullptr;
FARPROC close_socket_ptr = nullptr;
FARPROC connect_ptr = nullptr;
FARPROC get_peer_name_ptr = nullptr;
FARPROC get_sock_name_ptr = nullptr;
FARPROC get_sock_opt_ptr = nullptr;
FARPROC htonl_ptr = nullptr;
FARPROC htons_ptr = nullptr;
FARPROC inet_addr_ptr = nullptr;
FARPROC inet_ntoa_ptr = nullptr;
FARPROC ioctl_socket_ptr = nullptr;
FARPROC listen_ptr = nullptr;
FARPROC ntohl_ptr = nullptr;
FARPROC ntohs_ptr = nullptr;
FARPROC recv_ptr = nullptr;
FARPROC recv_from_ptr = nullptr;
FARPROC select_ptr = nullptr;
FARPROC send_ptr = nullptr;
FARPROC send_to_ptr = nullptr;
FARPROC set_sock_opt_ptr = nullptr;
FARPROC shutdown_ptr = nullptr;
FARPROC socket_ptr = nullptr;
FARPROC migrate_winsock_configuration_ptr = nullptr;
FARPROC get_host_by_addr_ptr = nullptr;
FARPROC get_host_by_name_ptr = nullptr;
FARPROC get_proto_by_name_ptr = nullptr;
FARPROC get_proto_by_number_ptr = nullptr;
FARPROC get_serv_by_name_ptr = nullptr;
FARPROC get_serv_by_port_ptr = nullptr;
FARPROC get_host_name_ptr = nullptr;
FARPROC wsa_async_select_ptr = nullptr;
FARPROC wsa_async_get_host_by_addr_ptr = nullptr;
FARPROC wsa_async_get_host_by_name_ptr = nullptr;
FARPROC wsa_async_get_proto_by_number_ptr = nullptr;
FARPROC wsa_async_get_proto_by_name_ptr = nullptr;
FARPROC wsa_async_get_serv_by_port_ptr = nullptr;
FARPROC wsa_async_get_serv_by_name_ptr = nullptr;
FARPROC wsa_cancel_async_request_ptr = nullptr;
FARPROC wsa_set_blocking_hook_ptr = nullptr;
FARPROC wsa_unhook_blocking_hook_ptr = nullptr;
FARPROC wsa_get_last_error_ptr = nullptr;
FARPROC wsa_set_last_error_ptr = nullptr;
FARPROC wsa_cancel_blocking_call_ptr = nullptr;
FARPROC wsa_is_blocking_ptr = nullptr;
FARPROC wsa_startup_ptr = nullptr;
FARPROC wsa_cleanup_ptr = nullptr;
FARPROC wsa_fd_is_set_ptr = nullptr;
FARPROC wep_ptr = nullptr;
FARPROC wsa_p_set_post_routine_ptr = nullptr;
FARPROC inet_network_ptr = nullptr;
FARPROC get_net_by_name_ptr = nullptr;
FARPROC rcmd_ptr = nullptr;
FARPROC rexec_ptr = nullptr;
FARPROC rresvport_ptr = nullptr;
FARPROC set_host_name_ptr = nullptr;
FARPROC dn_expand_ptr = nullptr;
FARPROC wsa_recv_ex_ptr = nullptr;
FARPROC s_perror_ptr = nullptr;
FARPROC get_address_by_name_a_ptr = nullptr;
FARPROC get_address_by_name_w_ptr = nullptr;
FARPROC enum_protocols_a_ptr = nullptr;
FARPROC enum_protocols_w_ptr = nullptr;
FARPROC get_type_by_name_a_ptr = nullptr;
FARPROC get_type_by_name_w_ptr = nullptr;
FARPROC get_name_by_type_a_ptr = nullptr;
FARPROC get_name_by_type_w_ptr = nullptr;
FARPROC set_service_a_ptr = nullptr;
FARPROC set_service_w_ptr = nullptr;
FARPROC get_service_a_ptr = nullptr;
FARPROC get_service_w_ptr = nullptr;
FARPROC np_load_name_spaces_ptr = nullptr;
FARPROC transmit_file_ptr = nullptr;
FARPROC accept_ex_ptr = nullptr;
FARPROC get_accept_ex_sockaddrs_ptr = nullptr;

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

typedef UINT_PTR SOCKET;
struct in_addr {
    unsigned long s_addr;
};

DLL_EXPORT SOCKET WINAPI accept(SOCKET s, void* addr, int* addrlen) {
    return reinterpret_cast<decltype(&accept)>(accept_ptr)(s, addr, addrlen);
}
DLL_EXPORT int WINAPI bind(SOCKET s, const void* name, int namelen) {
    return reinterpret_cast<decltype(&bind)>(bind_ptr)(s, name, namelen);
}
DLL_EXPORT int WINAPI closesocket(SOCKET s) {
    return reinterpret_cast<decltype(&closesocket)>(close_socket_ptr)(s);
}
DLL_EXPORT int WINAPI connect(SOCKET s, const void* name, int namelen) {
    return reinterpret_cast<decltype(&connect)>(connect_ptr)(s, name, namelen);
}
DLL_EXPORT int WINAPI getpeername(SOCKET s, void* name, int* namelen) {
    return reinterpret_cast<decltype(&getpeername)>(get_peer_name_ptr)(s, name, namelen);
}
DLL_EXPORT int WINAPI getsockname(SOCKET s, void* name, int* namelen) {
    return reinterpret_cast<decltype(&getsockname)>(get_sock_name_ptr)(s, name, namelen);
}
DLL_EXPORT int WINAPI getsockopt(SOCKET s, int level, int optname, char* optval, int* optlen) {
    return reinterpret_cast<decltype(&getsockopt)>(get_sock_opt_ptr)(s, level, optname, optval,
                                                                     optlen);
}
DLL_EXPORT unsigned long WINAPI htonl(unsigned long hostlong) {
    return reinterpret_cast<decltype(&htonl)>(htonl_ptr)(hostlong);
}
DLL_EXPORT unsigned short WINAPI htons(unsigned short hostshort) {
    return reinterpret_cast<decltype(&htons)>(htons_ptr)(hostshort);
}
DLL_EXPORT unsigned long WINAPI inet_addr(const char* cp) {
    return reinterpret_cast<decltype(&inet_addr)>(inet_addr_ptr)(cp);
}
DLL_EXPORT char* WINAPI inet_ntoa(in_addr in) {
    return reinterpret_cast<decltype(&inet_ntoa)>(inet_ntoa_ptr)(in);
}
DLL_EXPORT int WINAPI ioctlsocket(SOCKET s, long cmd, unsigned long* argp) {
    return reinterpret_cast<decltype(&ioctlsocket)>(ioctl_socket_ptr)(s, cmd, argp);
}
DLL_EXPORT int WINAPI listen(SOCKET s, int backlog) {
    return reinterpret_cast<decltype(&listen)>(listen_ptr)(s, backlog);
}
DLL_EXPORT unsigned long WINAPI ntohl(unsigned long netlong) {
    return reinterpret_cast<decltype(&ntohl)>(ntohl_ptr)(netlong);
}
DLL_EXPORT unsigned short WINAPI ntohs(unsigned short netshort) {
    return reinterpret_cast<decltype(&ntohs)>(ntohs_ptr)(netshort);
}
DLL_EXPORT int WINAPI recv(SOCKET s, char* buf, int len, int flags) {
    return reinterpret_cast<decltype(&recv)>(recv_ptr)(s, buf, len, flags);
}
DLL_EXPORT int WINAPI recvfrom(SOCKET s, char* buf, int len, int flags, void* from, int* fromlen) {
    return reinterpret_cast<decltype(&recvfrom)>(recv_from_ptr)(s, buf, len, flags, from, fromlen);
}
DLL_EXPORT int WINAPI
select(int nfds, void* readfds, void* writefds, void* exceptfds, const void* timeout) {
    return reinterpret_cast<decltype(&select)>(select_ptr)(nfds, readfds, writefds, exceptfds,
                                                           timeout);
}
DLL_EXPORT int WINAPI send(SOCKET s, const char* buf, int len, int flags) {
    return reinterpret_cast<decltype(&send)>(send_ptr)(s, buf, len, flags);
}
DLL_EXPORT int WINAPI
sendto(SOCKET s, const char* buf, int len, int flags, const void* to, int tolen) {
    return reinterpret_cast<decltype(&sendto)>(send_to_ptr)(s, buf, len, flags, to, tolen);
}
DLL_EXPORT int WINAPI setsockopt(SOCKET s, int level, int optname, const char* optval, int optlen) {
    return reinterpret_cast<decltype(&setsockopt)>(set_sock_opt_ptr)(s, level, optname, optval,
                                                                     optlen);
}
DLL_EXPORT int WINAPI shutdown(SOCKET s, int how) {
    return reinterpret_cast<decltype(&shutdown)>(shutdown_ptr)(s, how);
}
DLL_EXPORT SOCKET WINAPI socket(int af, int type, int protocol) {
    return reinterpret_cast<decltype(&socket)>(socket_ptr)(af, type, protocol);
}
DLL_EXPORT void* WINAPI gethostbyaddr(const char* addr, int len, int type) {
    return reinterpret_cast<decltype(&gethostbyaddr)>(get_host_by_addr_ptr)(addr, len, type);
}
DLL_EXPORT void* WINAPI gethostbyname(const char* name) {
    return reinterpret_cast<decltype(&gethostbyname)>(get_host_by_name_ptr)(name);
}
DLL_EXPORT void* WINAPI getprotobyname(const char* name) {
    return reinterpret_cast<decltype(&getprotobyname)>(get_proto_by_name_ptr)(name);
}
DLL_EXPORT void* WINAPI getprotobynumber(int number) {
    return reinterpret_cast<decltype(&getprotobynumber)>(get_proto_by_number_ptr)(number);
}
DLL_EXPORT void* WINAPI getservbyname(const char* name, const char* proto) {
    return reinterpret_cast<decltype(&getservbyname)>(get_serv_by_name_ptr)(name, proto);
}
DLL_EXPORT void* WINAPI getservbyport(int port, const char* proto) {
    return reinterpret_cast<decltype(&getservbyport)>(get_serv_by_port_ptr)(port, proto);
}
DLL_EXPORT int WINAPI gethostname(char* name, int namelen) {
    return reinterpret_cast<decltype(&gethostname)>(get_host_name_ptr)(name, namelen);
}
DLL_EXPORT int WINAPI WSAAsyncSelect(SOCKET s, void* hWnd, unsigned int wMsg, long lEvent) {
    return reinterpret_cast<decltype(&WSAAsyncSelect)>(wsa_async_select_ptr)(s, hWnd, wMsg, lEvent);
}
DLL_EXPORT void* WINAPI WSAAsyncGetHostByAddr(void* hWnd,
                                              unsigned int wMsg,
                                              const char* addr,
                                              int len,
                                              int type,
                                              char* buf,
                                              int buflen) {
    return reinterpret_cast<decltype(&WSAAsyncGetHostByAddr)>(wsa_async_get_host_by_addr_ptr)(
        hWnd, wMsg, addr, len, type, buf, buflen);
}
DLL_EXPORT void* WINAPI
WSAAsyncGetHostByName(void* hWnd, unsigned int wMsg, const char* name, char* buf, int buflen) {
    return reinterpret_cast<decltype(&WSAAsyncGetHostByName)>(wsa_async_get_host_by_name_ptr)(
        hWnd, wMsg, name, buf, buflen);
}
DLL_EXPORT void* WINAPI
WSAAsyncGetProtoByNumber(void* hWnd, unsigned int wMsg, int number, char* buf, int buflen) {
    return reinterpret_cast<decltype(&WSAAsyncGetProtoByNumber)>(wsa_async_get_proto_by_number_ptr)(
        hWnd, wMsg, number, buf, buflen);
}
DLL_EXPORT void* WINAPI
WSAAsyncGetProtoByName(void* hWnd, unsigned int wMsg, const char* name, char* buf, int buflen) {
    return reinterpret_cast<decltype(&WSAAsyncGetProtoByName)>(wsa_async_get_proto_by_name_ptr)(
        hWnd, wMsg, name, buf, buflen);
}
DLL_EXPORT void* WINAPI WSAAsyncGetServByPort(void* hWnd,
                                              unsigned int wMsg,
                                              int port,
                                              const char* proto,
                                              char* buf,
                                              int buflen) {
    return reinterpret_cast<decltype(&WSAAsyncGetServByPort)>(wsa_async_get_serv_by_port_ptr)(
        hWnd, wMsg, port, proto, buf, buflen);
}
DLL_EXPORT void* WINAPI WSAAsyncGetServByName(void* hWnd,
                                              unsigned int wMsg,
                                              const char* name,
                                              const char* proto,
                                              char* buf,
                                              int buflen) {
    return reinterpret_cast<decltype(&WSAAsyncGetServByName)>(wsa_async_get_serv_by_name_ptr)(
        hWnd, wMsg, name, proto, buf, buflen);
}
DLL_EXPORT int WINAPI WSACancelAsyncRequest(void* hAsyncTaskHandle) {
    return reinterpret_cast<decltype(&WSACancelAsyncRequest)>(wsa_cancel_async_request_ptr)(
        hAsyncTaskHandle);
}
DLL_EXPORT void* WINAPI WSASetBlockingHook(void* lpBlockFunc) {
    return reinterpret_cast<decltype(&WSASetBlockingHook)>(wsa_set_blocking_hook_ptr)(lpBlockFunc);
}
DLL_EXPORT int WINAPI WSAUnhookBlockingHook(void) {
    return reinterpret_cast<decltype(&WSAUnhookBlockingHook)>(wsa_unhook_blocking_hook_ptr)();
}
DLL_EXPORT int WINAPI WSAGetLastError(void) {
    return reinterpret_cast<decltype(&WSAGetLastError)>(wsa_get_last_error_ptr)();
}
DLL_EXPORT void WINAPI WSASetLastError(int iError) {
    reinterpret_cast<decltype(&WSASetLastError)>(wsa_set_last_error_ptr)(iError);
}
DLL_EXPORT int WINAPI WSACancelBlockingCall(void) {
    return reinterpret_cast<decltype(&WSACancelBlockingCall)>(wsa_cancel_blocking_call_ptr)();
}
DLL_EXPORT int WINAPI WSAIsBlocking(void) {
    return reinterpret_cast<decltype(&WSAIsBlocking)>(wsa_is_blocking_ptr)();
}
DLL_EXPORT int WINAPI WSAStartup(unsigned short wVersionRequested, void* lpWSAData) {
    return reinterpret_cast<decltype(&WSAStartup)>(wsa_startup_ptr)(wVersionRequested, lpWSAData);
}
DLL_EXPORT int WINAPI WSACleanup(void) {
    return reinterpret_cast<decltype(&WSACleanup)>(wsa_cleanup_ptr)();
}
DLL_EXPORT int WINAPI __WSAFDIsSet(SOCKET fd, void* set) {
    return reinterpret_cast<decltype(&__WSAFDIsSet)>(wsa_fd_is_set_ptr)(fd, set);
}
DLL_EXPORT int WINAPI WSARecvEx(SOCKET s, char* buf, int len, int* flags) {
    return reinterpret_cast<decltype(&WSARecvEx)>(wsa_recv_ex_ptr)(s, buf, len, flags);
}
DLL_EXPORT int WINAPI TransmitFile(SOCKET hSocket,
                                   void* hFile,
                                   unsigned long nBytes,
                                   unsigned long nBytesPerSend,
                                   void* lpOverlapped,
                                   void* lpTransmitBuffers,
                                   unsigned long dwFlags) {
    return reinterpret_cast<decltype(&TransmitFile)>(transmit_file_ptr)(
        hSocket, hFile, nBytes, nBytesPerSend, lpOverlapped, lpTransmitBuffers, dwFlags);
}
DLL_EXPORT int WINAPI AcceptEx(SOCKET sListen,
                               SOCKET sAccept,
                               void* lpOutputBuffer,
                               unsigned long dwRecvLen,
                               unsigned long dwLocalLen,
                               unsigned long dwRemoteLen,
                               unsigned long* lpdwBytesReceived,
                               void* lpOverlapped) {
    return reinterpret_cast<decltype(&AcceptEx)>(accept_ex_ptr)(sListen, sAccept, lpOutputBuffer,
                                                                dwRecvLen, dwLocalLen, dwRemoteLen,
                                                                lpdwBytesReceived, lpOverlapped);
}
DLL_EXPORT void WINAPI GetAcceptExSockaddrs(void* lpOutputBuffer,
                                            unsigned long dwRecvLen,
                                            unsigned long dwLocalLen,
                                            unsigned long dwRemoteLen,
                                            void** LocalSockaddr,
                                            int* LocalLen,
                                            void** RemoteSockaddr,
                                            int* RemoteLen) {
    reinterpret_cast<decltype(&GetAcceptExSockaddrs)>(get_accept_ex_sockaddrs_ptr)(
        lpOutputBuffer, dwRecvLen, dwLocalLen, dwRemoteLen, LocalSockaddr, LocalLen, RemoteSockaddr,
        RemoteLen);
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

    auto system_wsock32 = std::filesystem::path{static_cast<wchar_t*>(buf)} / "wsock32.dll";
    wsock32_dll_handle = LoadLibraryA(system_wsock32.generic_string().c_str());
    if (wsock32_dll_handle == nullptr) {
        std::cerr << "Unable to find system wsock32.dll! We're probably about to crash.\n";
        return;
    }

    accept_ptr = GetProcAddress(wsock32_dll_handle, "accept");
    bind_ptr = GetProcAddress(wsock32_dll_handle, "bind");
    close_socket_ptr = GetProcAddress(wsock32_dll_handle, "closesocket");
    connect_ptr = GetProcAddress(wsock32_dll_handle, "connect");
    get_peer_name_ptr = GetProcAddress(wsock32_dll_handle, "getpeername");
    get_sock_name_ptr = GetProcAddress(wsock32_dll_handle, "getsockname");
    get_sock_opt_ptr = GetProcAddress(wsock32_dll_handle, "getsockopt");
    htonl_ptr = GetProcAddress(wsock32_dll_handle, "htonl");
    htons_ptr = GetProcAddress(wsock32_dll_handle, "htons");
    inet_addr_ptr = GetProcAddress(wsock32_dll_handle, "inet_addr");
    inet_ntoa_ptr = GetProcAddress(wsock32_dll_handle, "inet_ntoa");
    ioctl_socket_ptr = GetProcAddress(wsock32_dll_handle, "ioctlsocket");
    listen_ptr = GetProcAddress(wsock32_dll_handle, "listen");
    ntohl_ptr = GetProcAddress(wsock32_dll_handle, "ntohl");
    ntohs_ptr = GetProcAddress(wsock32_dll_handle, "ntohs");
    recv_ptr = GetProcAddress(wsock32_dll_handle, "recv");
    recv_from_ptr = GetProcAddress(wsock32_dll_handle, "recvfrom");
    select_ptr = GetProcAddress(wsock32_dll_handle, "select");
    send_ptr = GetProcAddress(wsock32_dll_handle, "send");
    send_to_ptr = GetProcAddress(wsock32_dll_handle, "sendto");
    set_sock_opt_ptr = GetProcAddress(wsock32_dll_handle, "setsockopt");
    shutdown_ptr = GetProcAddress(wsock32_dll_handle, "shutdown");
    socket_ptr = GetProcAddress(wsock32_dll_handle, "socket");
    migrate_winsock_configuration_ptr =
        GetProcAddress(wsock32_dll_handle, "MigrateWinsockConfiguration");
    get_host_by_addr_ptr = GetProcAddress(wsock32_dll_handle, "gethostbyaddr");
    get_host_by_name_ptr = GetProcAddress(wsock32_dll_handle, "gethostbyname");
    get_proto_by_name_ptr = GetProcAddress(wsock32_dll_handle, "getprotobyname");
    get_proto_by_number_ptr = GetProcAddress(wsock32_dll_handle, "getprotobynumber");
    get_serv_by_name_ptr = GetProcAddress(wsock32_dll_handle, "getservbyname");
    get_serv_by_port_ptr = GetProcAddress(wsock32_dll_handle, "getservbyport");
    get_host_name_ptr = GetProcAddress(wsock32_dll_handle, "gethostname");
    wsa_async_select_ptr = GetProcAddress(wsock32_dll_handle, "WSAAsyncSelect");
    wsa_async_get_host_by_addr_ptr = GetProcAddress(wsock32_dll_handle, "WSAAsyncGetHostByAddr");
    wsa_async_get_host_by_name_ptr = GetProcAddress(wsock32_dll_handle, "WSAAsyncGetHostByName");
    wsa_async_get_proto_by_number_ptr =
        GetProcAddress(wsock32_dll_handle, "WSAAsyncGetProtoByNumber");
    wsa_async_get_proto_by_name_ptr = GetProcAddress(wsock32_dll_handle, "WSAAsyncGetProtoByName");
    wsa_async_get_serv_by_port_ptr = GetProcAddress(wsock32_dll_handle, "WSAAsyncGetServByPort");
    wsa_async_get_serv_by_name_ptr = GetProcAddress(wsock32_dll_handle, "WSAAsyncGetServByName");
    wsa_cancel_async_request_ptr = GetProcAddress(wsock32_dll_handle, "WSACancelAsyncRequest");
    wsa_set_blocking_hook_ptr = GetProcAddress(wsock32_dll_handle, "WSASetBlockingHook");
    wsa_unhook_blocking_hook_ptr = GetProcAddress(wsock32_dll_handle, "WSAUnhookBlockingHook");
    wsa_get_last_error_ptr = GetProcAddress(wsock32_dll_handle, "WSAGetLastError");
    wsa_set_last_error_ptr = GetProcAddress(wsock32_dll_handle, "WSASetLastError");
    wsa_cancel_blocking_call_ptr = GetProcAddress(wsock32_dll_handle, "WSACancelBlockingCall");
    wsa_is_blocking_ptr = GetProcAddress(wsock32_dll_handle, "WSAIsBlocking");
    wsa_startup_ptr = GetProcAddress(wsock32_dll_handle, "WSAStartup");
    wsa_cleanup_ptr = GetProcAddress(wsock32_dll_handle, "WSACleanup");
    wsa_fd_is_set_ptr = GetProcAddress(wsock32_dll_handle, "__WSAFDIsSet");
    wep_ptr = GetProcAddress(wsock32_dll_handle, "WEP");
    wsa_p_set_post_routine_ptr = GetProcAddress(wsock32_dll_handle, "WSApSetPostRoutine");
    inet_network_ptr = GetProcAddress(wsock32_dll_handle, "inet_network");
    get_net_by_name_ptr = GetProcAddress(wsock32_dll_handle, "getnetbyname");
    rcmd_ptr = GetProcAddress(wsock32_dll_handle, "rcmd");
    rexec_ptr = GetProcAddress(wsock32_dll_handle, "rexec");
    rresvport_ptr = GetProcAddress(wsock32_dll_handle, "rresvport");
    set_host_name_ptr = GetProcAddress(wsock32_dll_handle, "sethostname");
    dn_expand_ptr = GetProcAddress(wsock32_dll_handle, "dn_expand");
    wsa_recv_ex_ptr = GetProcAddress(wsock32_dll_handle, "WSARecvEx");
    s_perror_ptr = GetProcAddress(wsock32_dll_handle, "s_perror");
    get_address_by_name_a_ptr = GetProcAddress(wsock32_dll_handle, "GetAddressByNameA");
    get_address_by_name_w_ptr = GetProcAddress(wsock32_dll_handle, "GetAddressByNameW");
    enum_protocols_a_ptr = GetProcAddress(wsock32_dll_handle, "EnumProtocolsA");
    enum_protocols_w_ptr = GetProcAddress(wsock32_dll_handle, "EnumProtocolsW");
    get_type_by_name_a_ptr = GetProcAddress(wsock32_dll_handle, "GetTypeByNameA");
    get_type_by_name_w_ptr = GetProcAddress(wsock32_dll_handle, "GetTypeByNameW");
    get_name_by_type_a_ptr = GetProcAddress(wsock32_dll_handle, "GetNameByTypeA");
    get_name_by_type_w_ptr = GetProcAddress(wsock32_dll_handle, "GetNameByTypeW");
    set_service_a_ptr = GetProcAddress(wsock32_dll_handle, "SetServiceA");
    set_service_w_ptr = GetProcAddress(wsock32_dll_handle, "SetServiceW");
    get_service_a_ptr = GetProcAddress(wsock32_dll_handle, "GetServiceA");
    get_service_w_ptr = GetProcAddress(wsock32_dll_handle, "GetServiceW");
    np_load_name_spaces_ptr = GetProcAddress(wsock32_dll_handle, "NPLoadNameSpaces");
    transmit_file_ptr = GetProcAddress(wsock32_dll_handle, "TransmitFile");
    accept_ex_ptr = GetProcAddress(wsock32_dll_handle, "AcceptEx");
    get_accept_ex_sockaddrs_ptr = GetProcAddress(wsock32_dll_handle, "GetAcceptExSockaddrs");
}

void free(void) {
    if (wsock32_dll_handle != nullptr) {
        FreeLibrary(wsock32_dll_handle);
        wsock32_dll_handle = nullptr;
    }
}

}  // namespace pluginloader::proxy
