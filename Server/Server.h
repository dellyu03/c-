// Server.h
#pragma once

#include <winsock2.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <thread>
#include <mutex>
#include "ClientHandler.h"

#pragma comment(lib, "ws2_32.lib")

#define SERVER_PORT 9000
#define BUF_SIZE 512

class CServer {
public:
    CServer();
    ~CServer();
    bool Initialize();
    void StartListening();

private:
    SOCKET m_listenSocket;
    std::vector<SOCKET> m_clientSockets;
    std::mutex m_clientMutex;
};