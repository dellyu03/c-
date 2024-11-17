#pragma once

#include "pch.h"
#include <winsock2.h>
#include <string>
#include <iostream>

class NetworkUtils {
public:
    static bool Initialize();
    static SOCKET CreateSocket();
    static void SendPacket(SOCKET sock, const std::string& message);
    static std::string ReceivePacket(SOCKET sock);
};
