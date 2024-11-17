#include "pch.h"
#include "Client.h"

CClient::CClient() : m_socket(INVALID_SOCKET) {}

CClient::~CClient() {
    Disconnect();  // 소멸자에서 호출
}

bool CClient::Initialize() {
    return NetworkUtils::Initialize();
}

void CClient::ConnectToServer(const std::string& serverIp) {
    m_socket = NetworkUtils::CreateSocket();
    if (m_socket == INVALID_SOCKET) {
        return;
    }

    m_serverAddr.sin_family = AF_INET;
    m_serverAddr.sin_port = htons(SERVER_PORT);

    if (inet_pton(AF_INET, serverIp.c_str(), &m_serverAddr.sin_addr) <= 0) {
        std::cerr << "Invalid IP address" << std::endl;
        return;
    }

    int result = connect(m_socket, (SOCKADDR*)&m_serverAddr, sizeof(m_serverAddr));
    if (result == SOCKET_ERROR) {
        std::cerr << "Connection failed with error code: " << WSAGetLastError() << std::endl;
        closesocket(m_socket);
        return;
    }

    m_isConnected = true;
    std::cout << "Connected to server!" << std::endl;
}

void CClient::SendMessage(const std::string& message) {
    NetworkUtils::SendPacket(m_socket, message);
}

void CClient::ReceiveMessagesAsync() {
    int game_state = 0;  // 게임 상태 초기화
    while (m_isConnected) {
        std::string message = NetworkUtils::ReceivePacket(m_socket);
        if (message.empty()) {
            std::cerr << "Connection lost with server" << std::endl;
            Disconnect();
            break;
        }

        // 메시지를 받은 직후 처리
        std::cout << "Received message from server: " << message << std::endl;

        // "Game Start" 메시지가 오면 게임 시작, "Game Over" 메시지가 오면 게임 종료
        if (message == "Game Start" && game_state == 0) {
            game_state = 1;
            sendGameCommandToServer();  // 게임 시작 명령을 보냄
        }
        else if (message == "Game Over" && game_state == 1) {
            game_state = 0;
            sendCommandToServer();  // 게임 종료 명령을 보냄
        }
        else if (game_state == 1) {
            sendGameCommandToServer();
        }
        else if (game_state == 0) {
            sendCommandToServer();  // 다른 명령은 서버로 계속 보냄
        }
    }
}

void CClient::sendCommandToServer() {
    std::string command;
    std::cout << "Enter command: ";
    std::getline(std::cin, command);
    SendMessage(command);
}

void CClient::sendGameCommandToServer() {
    std::string command;
    std::cout << "짝을 맞춰 보세요: ";
    std::getline(std::cin, command);
    SendMessage(command);
}



void CClient::Disconnect() {
    if (m_socket != INVALID_SOCKET) {
        closesocket(m_socket);
    }
    m_isConnected = false;
    WSACleanup();
}
