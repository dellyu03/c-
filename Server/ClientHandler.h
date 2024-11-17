#pragma once
#include "pch.h"
#include <winsock2.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#define BUF_SIZE 512

class ClientHandler {
public:
    static void HandleClient(SOCKET clientSocket);
};