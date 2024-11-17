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

    client.sendCommandToServer();

    // �����κ��� ���� �޽����� ó���ϴ� ������
    std::thread receiveThread([&client]() {
        client.ReceiveMessagesAsync();
        });

 

    // ���� �����尡 ����� ������ ���
    receiveThread.join();

    return 0;
}