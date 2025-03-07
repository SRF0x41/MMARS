#include <iostream>
#include <cstring>      // For memset, strlen
#include <sys/socket.h> // For socket functions
#include <arpa/inet.h>  // For inet_addr, htons
#include <unistd.h>     // For close()

class SocketComm
{
private:
    int client_socket;

public:
    SocketComm()
    {
        
    }

    int createConnection(){
        // Create a TCP socket
        client_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (client_socket == -1)
        {
            std::cerr << "Error creating socket!\n";
            return -1;
        }

        // Define server details
        sockaddr_in server_addr{};
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(12345);                  // Port must match the server
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Localhost

        // Connect to the server
        if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
        {
            std::cerr << "Connection failed!\n";
            close(client_socket);
            return -1;
        }

        std::cout << "Connected to the server!\n";

        return 0;
    }

    void sendMessage(char *message)
    {
        send(client_socket, message, strlen(message), 0);
    }

    void receiveDataPrint()
    {
        // Receive response from server
        char buffer[1024] = {0};
        recv(client_socket, buffer, sizeof(buffer), 0);
        std::cout << "Server response: " << buffer << std::endl;
    }

    void closeSocket()
    {
        close(client_socket);
    }
};
