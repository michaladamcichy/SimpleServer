#pragma once

#include "stdafx.h"
#include<boost/asio.hpp>
#include "Log.h"
#include "Network.h"
#include "MessageHandler.h"
#include "StatisticHandler.h"
#include "SqlConnection.h"
#include "ThreadSafeCounter.h"


using namespace boost::asio;
using boost::asio::ip::tcp;
using boost::system::error_code;

class Session : public StatisticHandler {
    private:
        StatisticHandler& server;
        tcp::socket socket;
        set<Session*>& sessions;
        ThreadSafeCounter& counter;
        std::mutex& mutex;

        SqlConnection sqlConnection;

        MessageHandler messageHandler;

        std::thread thread;

    public:
        Session(StatisticHandler& _server, tcp::socket _socket, set<Session*>& _sessions, ThreadSafeCounter& _counter, std::mutex& _mutex) :
            server(_server), socket(move(_socket)), sessions(_sessions), counter(_counter), mutex(_mutex) {
            
            thread = std::thread([this] () {
                Log::print("New session started");

                bool end = false;

                while(!end) {
                    string rawRequest = Network::receive(socket);
                    
                    if(rawRequest == "\0") {
                        Log::print("Connection closed");
                        break;
                    }

                    try {
                        Log::print(rawRequest);

                        Json::Value request;
                        
                        request = messageHandler.decode(rawRequest);
                        
                        if(request["cmd"] == "STAT") {
                            Network::send(socket, messageHandler.stat(server.getFromStart(), this->getFromStart(), this->getRequests(), server.getActive()));
                        } else if(request["cmd"] == "INC") {
                            int count = counter.inc(request["args"]["number"].asInt64());
                            
                            Network::send(socket, messageHandler.inc(count));
                        } else if(request["cmd"] == "GET") {
                            int count = counter.get(request["args"]["number"].asInt64());
                            Network::send(socket, messageHandler.get(count));
                        } else if(request["cmd"] == "SLEEP") {
                            sleep(request["args"]["delay"].asInt());

                            Network::send(socket, messageHandler.ok());
                        } else if(request["cmd"] == "END") {
                            Network::send(socket, messageHandler.ok());
                            end = true;
                        } else if(request["cmd"] == "WRITE") {
                            try {
                                sqlConnection.write(request["args"]["key"].asString(), request["args"]["value"].asString());
                                Network::send(socket, messageHandler.ok());
                            } catch(sql::SQLException &e) {
                                Log::print("WRITE failed");
                                throw e;
                            }
                        } else if(request["cmd"] == "READ") {
                            try {
                                string value = sqlConnection.read(request["args"]["key"].asString());
                                Network::send(socket, messageHandler.read(value));
                            } catch(std::exception& e) {
                                Log::print("READ failed");
                                throw e;
                            }
                        }
                        else {
                            Log::print("Invalid request");
                            Network::send(socket, messageHandler.error());
                        }

                        registerRequest();
                    } catch(std::exception& e) {
                        Log::print(e.what());
                        Network::send(socket, messageHandler.error());
                    }
                }
                Log::print("Connection closed");

                cleanUp();
            });

            thread.detach();
        }

        virtual ~Session() {}

        void joinThread() {
            thread.join();
        }

    private:
        void cleanUp() {
                auto it = sessions.find(this);
                mutex.lock();
                sessions.erase(it);
                mutex.unlock();
                delete this;
            }
};
