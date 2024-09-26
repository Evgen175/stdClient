#ifndef MY_CLIENT_H
#define MY_CLIENT_H

#pragma once
#include <iostream>
#include <sys/socket.h> // Socket
#include <cstring> //mem
#include <netinet/in.h> //sockaddr_in
#include <arpa/inet.h> //inet_addr
#include <unistd.h> // close
#include <chrono>
#include <sstream>
#include <iomanip>
#include <thread>

using namespace std;

inline  string timeStamp (){
    stringstream ss_;
    /////////////////////////
    auto now_ =   chrono::system_clock::now();
    time_t time_t_ = chrono::system_clock::to_time_t(now_);
    chrono::milliseconds ms = chrono::duration_cast<chrono::milliseconds>(now_.time_since_epoch() % chrono::seconds(1));
    /////////////////////////
    ss_ << "[" << put_time(localtime(&time_t_), "%Y-%m-%d %H:%M:%S.") << setfill('0') << setw(3) << ms.count() << "]";
        return ss_.str();
        };

class MyClient {
public:
    MyClient(const MyClient&) = delete;
    MyClient& operator=(const MyClient&) = delete;

//protected:
    explicit MyClient(const string& name, const uint port, const uint period) : name_(name), port_(port), period_(period)  {
        cout << "Client started " << timeStamp() << endl;
}

    void run() {
        int socket_ = socket(AF_INET, SOCK_STREAM, 0);
        if (socket_ < 0) {
            cerr <<"Socket creation error" << endl;
            exit(-1);
        }
        struct sockaddr_in serv_addr_;
        memset(&serv_addr_, 0, sizeof(serv_addr_));
        serv_addr_.sin_family = AF_INET;
        serv_addr_.sin_port = htons(port_);
        serv_addr_.sin_addr.s_addr = inet_addr("127.0.0.1");

        if (connect(socket_, (struct sockaddr*)&serv_addr_, sizeof(serv_addr_)) < 0) {
            cerr << "Error! Connecting to server" << endl;
            close(socket_);
            exit(-1);
        }

        auto message = timeStamp() + " " + name_;
        if (send(socket_, message.c_str(), message.length(), 0) < 0) {
            cerr << "Message sending error" << endl;
            close(socket_);
            exit(-1);
        }
        close(socket_);
    }


private:
    string name_ = nullptr;
    uint port_ = 0;
    uint period_ = 0;
};

#endif // MY_CLIENT_H
