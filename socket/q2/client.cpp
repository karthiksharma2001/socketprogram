#include <iostream>
#include <cstring>
#include <cstdlib>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>

using namespace std;

const char *HOST = "127.0.0.1";
const int PORT = 8080;

void handle_send(int client_socket) {
    while (true) {
        string data;
        cout << "Enter message to send: ";
        getline(cin, data);

        if (!data.empty()) {
            write(client_socket, data.c_str(), data.size());
        }
    }
}

void handle_recv(int client_socket) {
    while (true) {
        char buffer[2048];
        int bytes_read = read(client_socket, buffer, sizeof(buffer));
        if (bytes_read <= 0) {
            cout << "Connection closed." << endl;
            break;
        }

        buffer[bytes_read] = '\0';
          string s(buffer);
        
        if(s=="exit")
        {
            close(client_socket);
            exit(1);
        }
        cout << buffer << endl;
    }
}

int main() {
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("socket");
        return 1;
    }

    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    if (inet_pton(AF_INET, HOST, &(server_address.sin_addr)) <= 0) {
        perror("inet_pton");
        return 1;
    }

    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("connect");
        return 1;
    }

    string username;
    cout << "Enter username: ";
    getline(cin, username);

    if (!username.empty()) {
        write(client_socket, username.c_str(), username.size());
    } else {
        cout << "Invalid username. Username cannot be empty." << endl;
        close(client_socket);
        return 1;
    }

    thread send_thread(handle_send, client_socket);
    thread recv_thread(handle_recv, client_socket);

    send_thread.join();
    recv_thread.join();

    close(client_socket);
    return 0;
}
