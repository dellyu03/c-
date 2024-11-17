#pragma once
#include "pch.h"
#include <winsock2.h>
#include <string>

namespace NetworkUtils {
    bool SendMessageToClient(SOCKET clientSocket, const std::string& message);
}