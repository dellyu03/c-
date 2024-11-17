#include "pch.h"
#include "Server.h"

//command 처리 함수
/*
           else if (strcmp(buffer, "correct") == 0) {
               std::string response = "good";
               send(clientSocket, response.c_str(), response.length(), 0);
               std::cout << "Sent command message to client." << std::endl;
           }
*/
#include "NetworkUtils.h"

void ClientHandler::HandleClient(SOCKET clientSocket) {
    char buffer[BUF_SIZE];
    while (true) {
        int bytesReceived = recv(clientSocket, buffer, BUF_SIZE, 0);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';
            std::cout << "Received message from client: " << buffer << std::endl;

            if (strcmp(buffer, "exit") == 0) {
                std::cout << "Client requested exit." << std::endl;
                closesocket(clientSocket);
                break;
            }
            else {
                std::string unknownMessage = "Unknown command";
                send(clientSocket, unknownMessage.c_str(), unknownMessage.length(), 0);
            }
        }
        else {
            std::cerr << "Failed to receive data from client!" << std::endl;
            closesocket(clientSocket);
            break;
        }
    }
}
