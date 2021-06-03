#pragma once

#include "stdafx.h"
#include<boost/asio.hpp>
#include "Log.h"
#include "Config.h"
#include "Network.h"

using namespace boost::asio;
using boost::asio::ip::tcp;
using boost::system::error_code;

class Network {
    public:
    static void send(tcp::socket& socket, string message) {
        try {
            socket.send(buffer(message)); //alert tu odejmij
            Log::print(message);
            // Log::print(message);
            // Log::print(b);
            // Log::print(message.size());
        } catch(std::exception& e) {
            Log::print(e.what());
            Log::print("Cannot send response to client. Not available");
        }
    }

    static string receive(tcp::socket& socket) {
        char data[Config::bufferSize];

        try {
            int bytesRead = socket.receive(buffer(data, Config::bufferSize));
            
            if(bytesRead == 0) {
                return "\0";
            }
            //Log::print(b);
            return string(data);
        } catch(std::exception& e) {
            Log::print(e.what());
            return "\0";
        }
    }
};