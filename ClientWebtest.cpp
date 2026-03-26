#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <thread>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#pragma warning(disable: 4996)

class Client_chats
{
private:
    SOCKET client;
    SOCKADDR_IN serveraddr;



public:
    Client_chats(const std::string& serverip, int port)
    {
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);

        client = socket(AF_INET, SOCK_STREAM, 0);
        serveraddr.sin_family = AF_INET;
        serveraddr.sin_port = htons(port);
        inet_pton(AF_INET, serverip.c_str(), &serveraddr.sin_addr);
    }
    ~Client_chats()
    {
        closesocket(client);
        WSACleanup();
    }
    void Connect()
    {
        if (connect(client, (SOCKADDR*)&serveraddr, sizeof(serveraddr)) < 0)
        {
            std::cerr << "Connection failed." << '\n';
            exit(EXIT_FAILURE);
        }

        std::cout << "Connected to the server. Welcome to the chat!" << '\n';
    }
    void send_message(const std::string& message)
    {
        send(client, message.c_str(), message.length(), 0);
    }
    void MessageReceive()
    {
        char buffer[1024];
        while (true)
        {
            int bytesreceived = recv(client, buffer, sizeof(buffer),0);
            if (bytesreceived == SOCKET_ERROR || bytesreceived == 0)
            {
                std::cout << "Disconnet from server." << '\n';
                break;
            }
            std::cout << std::string(buffer, bytesreceived) << '\n';
        }
    }
    void runs()
    {
        std::thread receivethread([this] {MessageReceive(); });
        receivethread.detach();

        std::string input{};
        std::string username{};
        

        std::cout << "Enter your username: \n";
        std::getline(std::cin, username);
        send_message(username);


        int client_num{ 0 };
        int bytes_received = recv(client, (char*)&client_num, sizeof(client_num), 0);
        int num = ntohl(client_num); // обратное преобразование

        std::cout << num << '\n';



        while (true)
        {
            std::getline(std::cin, input);
            send_message(input);
            if (input == "exit")
            {
                break;
            }
        }
    }
};

int main() 
{
    std::string server_ip{};
    std::cout << "Enter server ip: ";
    std::cin >> server_ip;
    Client_chats client(server_ip, 1500);
    client.Connect();
    client.runs();
    
    return 0;
}