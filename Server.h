#pragma once
#include "stdafx.h"
#include<boost/asio.hpp>
#include "Log.h"
#include "Session.h"
#include "StatisticHandler.h"
#include "ThreadSafeCounter.h"

using namespace boost::asio;
using boost::asio::ip::tcp;
using boost::system::error_code;

class Server : public StatisticHandler {
public:
    io_context& context;
    tcp::acceptor acceptor;
    
    set<Session*> sessions;
    ThreadSafeCounter counter;

    std::mutex mutex;

    Server(io_context& _context, tcp::endpoint& endpoint) : context(_context), acceptor(context, endpoint) {
        Log::print("Creating server...");
        accept();
        Log::done();
    }

    ~Server() {
    }

    //override
    int getRequests() {
        int sum = 0;
        mutex.lock();
        for(auto& session : sessions) {
            sum += session->getRequests();
        }
        mutex.unlock();

        return sum;
    }

    //override
    int getActive() {
        return sessions.size();
    }

    void accept() {
        acceptor.async_accept(
         [this](error_code ec, tcp::socket socket)
        {
          if (!ec)
          {
              Log::print("Accepted");

              mutex.lock();
              sessions.insert(new Session(*this, move(socket), sessions, counter, mutex));
              mutex.unlock();
          }

          accept();
        });
    }

    void run() {
        context.run();
    }
};
