#pragma once

#include "stdafx.h"
#include<boost/asio.hpp>
#include "Log.h"
#include "Network.h"
#include "MessageHandler.h"

class ThreadSafeCounter {
    private:
        std::mutex mutex;
        hashmap<long long, int> counts;
    public:
        ThreadSafeCounter() {
        }

        int inc(long long number) {
            mutex.lock();

            int value;

            if(counts.find(number) != counts.end()) {
                value = ++counts[number];
            } else {
                value = counts[number] = 1;
            }

            mutex.unlock();

            return value;
        }

        int get(long long number) {
            mutex.lock();
            int value =  counts[number]; 
            mutex.unlock();

            return value;
        }

    private:
};
