#pragma once
#include "pch.h"
#include "Network.h"

bool NetworkUtils::Initialize() {
    WSADATA wsaData;
    return WSAStartup(MAKEWORD(2, 2), &wsaData) == 0;
}

SOCKET NetworkUtils::CreateSocket() {
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Socket creation failed!" << std::endl;
    }
    return sock;
}

void NetworkUtils::SendPacket(SOCKET sock, const std::string& message) {
    send(sock, message.c_str(), message.length(), 0);
}

std::string NetworkUtils::ReceivePacket(SOCKET sock) {
    char buffer[BUF_SIZE];
    int bytesReceived = recv(sock, buffer, BUF_SIZE, 0);
    if (bytesReceived > 0) {
        return std::string(buffer, bytesReceived);
    }
    return {};
}
