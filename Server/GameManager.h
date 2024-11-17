#pragma once
#include "pch.h"
#include <winsock2.h>
#include <vector>
#include <mutex>

// CServer를 전방 선언
class CServer;

class GameManager {
public:
    GameManager(CServer& server);  // CServer 객체를 참조
    void AddClient(SOCKET clientSocket);
    void StartGame();
    void NextTurn();
    SOCKET GetCurrentPlayer();

private:
    CServer& m_server;  // CServer 객체를 참조하여 서버 메서드 호출
    std::vector<SOCKET> m_clients;  // 게임에 참여하는 클라이언트 목록
    size_t m_currentTurnIndex = 0;  // 현재 턴을 진행 중인 클라이언트의 인덱스
    std::mutex m_mutex;  // 멀티스레드 환경에서의 안전을 위한 뮤텍스
};