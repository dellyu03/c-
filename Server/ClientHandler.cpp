#include "pch.h"
#include "Server.h"

//command Ã³¸® ÇÔ¼ö
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

            // 각 명령을 처리하고 즉시 응답을 전송
            std::string response;  // 메시지를 저장할 변수

            if (strcmp(buffer, "exit") == 0) {
                std::cout << "Client requested exit." << std::endl;
                closesocket(clientSocket);
                break;
            }
            else if (strcmp(buffer, "game_start") == 0) {
                std::cout << "Start Game" << std::endl;
                response = "Game Start";  // 전송할 메시지
            }
            else if (strcmp(buffer, "turn_end") == 0) {
                std::cout << "Turn end" << std::endl;
                response = "Turn End";  // 전송할 메시지
            }
            else if (strcmp(buffer, "game_end") == 0) {
                std::cout << "Game Over" << std::endl;
                response = "Game Over";  // 전송할 메시지
            }
            else {
                response = "Unknown command";  // 전송할 메시지
            }

            // 클라이언트에게 메시지 전송
            send(clientSocket, response.c_str(), response.length(), 0);

            // 전송한 메시지를 로그로 출력
            std::cout << "Sent message to client: " << response << std::endl;
        }
        else {
            std::cerr << "Failed to receive data from client!" << std::endl;
            closesocket(clientSocket);
            break;
        }
    }
}
