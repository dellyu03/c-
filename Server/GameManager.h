#pragma once
#include "pch.h"
#include <winsock2.h>
#include <vector>
#include <mutex>

// CServer�� ���� ����
class CServer;

class GameManager {
public:
    GameManager(CServer& server);  // CServer ��ü�� ����
    void AddClient(SOCKET clientSocket);
    void StartGame();
    void NextTurn();
    SOCKET GetCurrentPlayer();

private:
    CServer& m_server;  // CServer ��ü�� �����Ͽ� ���� �޼��� ȣ��
    std::vector<SOCKET> m_clients;  // ���ӿ� �����ϴ� Ŭ���̾�Ʈ ���
    size_t m_currentTurnIndex = 0;  // ���� ���� ���� ���� Ŭ���̾�Ʈ�� �ε���
    std::mutex m_mutex;  // ��Ƽ������ ȯ�濡���� ������ ���� ���ؽ�
};