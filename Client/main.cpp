#include "pch.h"
#include "Client.h"
#include <thread>

int main() {
    CClient client;
    std::string command;

    if (!client.Initialize()) {
        return -1;
    }

    client.ConnectToServer("127.0.0.1");

   

    std::thread receiveThread([&client]() {
        client.ReceiveMessagesAsync();
        });

    client.sendCommandToServer();

    client.UserInput();
    receiveThread.join();

    return 0;
}
