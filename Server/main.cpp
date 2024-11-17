
#include "pch.h"
#include "Server.h"

int main() {
    CServer server;

    if (!server.Initialize()) {
        return -1;
    }

    server.StartListening();

    return 0;
}
