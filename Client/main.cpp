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

    // 서버로부터 받은 메시지를 처리하는 스레드
    std::thread receiveThread([&client]() {
        client.ReceiveMessagesAsync();
        });

 

    // 수신 스레드가 종료될 때까지 대기
    receiveThread.join();

    return 0;
}