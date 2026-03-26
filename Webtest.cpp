#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <thread>
#include <WinSock2.h>
#include <WS2tcpip.h>


#pragma comment(lib, "ws2_32.lib")

#pragma warning(disable: 4996)



class ChatServer
{
private:
    SOCKET serverSocket;
    std::unordered_map<std::string, SOCKET> clients;
    int indexid; // уникальный айди для каждого из пользователей(НАХОДИТСЯ В ДОРАБОТКЕ)
public:
    ChatServer(int Port) : indexid(0) // здесь мы создали сокет сервера.
    {
        WSAData wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);


        serverSocket = socket(AF_INET, SOCK_STREAM,0);
        SOCKADDR_IN addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(Port);
        addr.sin_addr.s_addr = INADDR_ANY;


        bind(serverSocket, (SOCKADDR*)&addr, sizeof(addr));

        listen(serverSocket, 4);
    }
    ~ChatServer()
    {
        closesocket(serverSocket);
        WSACleanup();
    }

    void AcceptClient()
    {
        while (true)
        {
            SOCKET clientsocket;
            SOCKADDR_IN addr_client;
            int lenaddr_client = sizeof(addr_client);
            clientsocket = accept(serverSocket, (SOCKADDR*)&addr_client, &lenaddr_client);

            std::thread Clientthread([this, clientsocket] {handlerclient(clientsocket); });
            Clientthread.detach();
        }
    }
    void handlerclient(SOCKET client)
    {
        int net_num = htonl(indexid++); // преобразование что бы отправить
        send(client, (char*)&net_num, sizeof(net_num), 0);
        
        char buffer[1024];
        int bytesreceived = recv(client, buffer, sizeof(buffer), 0);
        std::string clietname(buffer, bytesreceived);
        clients[clietname] = client;


        std::cout << "Client connected: " << clietname << " " << " Id: " << indexid << '\n';

        while (true)
        {
            bytesreceived = recv(client, buffer, sizeof(buffer), 0);
            if (bytesreceived <= 0)
            {
                std::cout << "Client disconnected: " << clietname << " " << " Id: " << indexid << '\n';
                clients.erase(clietname);
                closesocket(client);
                break;
            }
            std::string messageReceived(buffer, bytesreceived);
            std::cout << "Received from " << clietname << ": " << messageReceived << '\n';

            std::string buffer_to_send = clietname + ": " + messageReceived;
            for (auto& Pair : clients)
            {
                if (Pair.first != clietname)
                { // что бы не отправлять самому отправителю сообщение
                    send(Pair.second, buffer_to_send.c_str(), buffer_to_send.length(),0);
                }
            }
        }
    }
};




int main() 
{
    ChatServer server(1500);

    server.AcceptClient();
    return 0;
}