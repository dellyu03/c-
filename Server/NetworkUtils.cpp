// NetworkUtils.cpp
#include "pch.h"
#include "NetworkUtils.h"

namespace NetworkUtils {
    bool SendMessageToClient(SOCKET clientSocket, const std::string& message) {
        if (send(clientSocket, message.c_str(), message.length(), 0) == SOCKET_ERROR) {
            return false;
        }
        return true;
    }
}