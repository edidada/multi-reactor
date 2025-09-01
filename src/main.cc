
#include <cstdlib>
#include <iostream>
#include <string>

#ifdef MULTI1
#include "MultiPoller.h"
#else
#include "Poller.h"
#endif

#include "TcpServer.h"
#include "TcpConn.h"

int main() {
#ifdef MULTI1
    MultiPoller<2> poller;
    TcpServer server1(&poller);

    server1.Start(8989, [](TcpConn::Ptr conn) {
        std::cout << "[Multi Poller1]New connection established on server1\n";

        conn->SetReadCallback([conn]() {
            std::cout << "Received: " << conn->GetAllData() << std::endl;
            conn->Send("HTTP/1.1 200 OK\r\nContent-Length: 12\r\n\r\nHello Mark!\r\n", 53);
        });
    });

    TcpServer server2(&poller);
    server2.Start(8990, [](TcpConn::Ptr conn) {
        std::cout << "[Multi Poller1]New connection established on server2\n";

        conn->SetReadCallback([conn]() {
            std::cout << "Received: " << conn->GetDataUntilCrLf() << std::endl;
            conn->Send("Hello from server2!\r\n", 22);
        });
    });

#elif MULTI2
    Poller poller1;
    TcpServer server1(&poller1);
    server1.Start(8989, [](TcpConn::Ptr conn) {
        std::cout << "[Multi Poller2]New connection established on server1\n";

        conn->SetReadCallback([conn]() {
            std::cout << "Received: " << conn->GetAllData() << std::endl;
            conn->Send("HTTP/1.1 200 OK\r\nContent-Length: 12\r\n\r\nHello Mark!\r\n", 53);
        });
    });

    Poller poller2;
    TcpServer server2(&poller2);
    server2.Start(8990, [](TcpConn::Ptr conn) {
        std::cout << "[Multi Poller2]New connection established on server2\n";

        conn->SetReadCallback([conn]() {
            std::cout << "Received: " << conn->GetDataUntilCrLf() << std::endl;
            conn->Send("Hello from server2!\r\n", 22);
        });
    });

#else

    Poller poller;
    TcpServer server1(&poller);
    server1.Start(8989, [](TcpConn::Ptr conn) {
        std::cout << "[Poller]New connection established on server1\n";

        conn->SetReadCallback([conn]() {
            std::cout << "Received: " << conn->GetAllData() << std::endl;
            conn->Send("HTTP/1.1 200 OK\r\nContent-Length: 12\r\n\r\nHello Mark!\r\n", 53);
        });
    });
    TcpServer server2(&poller);
    server2.Start(8990, [](TcpConn::Ptr conn) {
        std::cout << "[Poller]New connection established on server2\n";

        conn->SetReadCallback([conn]() {
            std::cout << "Received: " << conn->GetDataUntilCrLf() << std::endl;
            conn->Send("Hello from server2!\r\n", 22);
        });
    });

#endif
    while(true) {
        // 如果输入 quit，则退出
        std::string input;
        std::getline(std::cin, input);

        if (input == "quit") {
            std::exit(0);
        }
    }
    return 0;
}