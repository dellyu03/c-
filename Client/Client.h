#pragma once

#include <winsock2.h>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include "Network.h"

#define SERVER_PORT 9000
#define BUF_SIZE 512

class CClient {
public:
    CClient();
    ~CClient();

    bool Initialize();
    void ConnectToServer(const std::string& serverIp);
    void SendMessage(const std::string& message);
    void ReceiveMessagesAsync();
    void sendCommandToServer();
    void sendGameCommandToServer();
    void Disconnect();  

private:
    SOCKET m_socket;
    sockaddr_in m_serverAddr;
    bool m_isConnected;
};
