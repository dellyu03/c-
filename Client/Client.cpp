#include "pch.h"
#include "Client.h"


CClient::CClient() : m_socket(INVALID_SOCKET) {}

CClient::~CClient() {
    Disconnect();
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
    while (m_isConnected) {
        std::string message = NetworkUtils::ReceivePacket(m_socket);
        if (message.empty()) {
            std::cerr << "Connection lost with server" << std::endl;
            Disconnect();
            break;
        }
        std::cout << "Received message from server: " << message << std::endl;
        if (message != "Start Game") {
            sendCommandToServer();
        }   
    }
}

void CClient::sendCommandToServer() {
        // 사용자로부터 명령어 입력 받기
        std::string command;
        std::cout << "Enter command: ";
        std::getline(std::cin, command);

        // 입력한 명령어를 서버로 전송
        SendMessage(command);
}

void CClient::UserInput() {
    while (m_isConnected) {
        std::string command;

        if (command == "exit") {
            Disconnect();
            break;
        }
        else {
            SendMessage(command);
        }
    }
}

void CClient::Disconnect() {
    if (m_socket != INVALID_SOCKET) {
        closesocket(m_socket);
    }
    m_isConnected = false;
    WSACleanup();
}
