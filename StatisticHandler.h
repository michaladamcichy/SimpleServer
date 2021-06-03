#pragma once
#include "stdafx.h"
#include "Log.h"

class StatisticHandler {
    private:
        std::chrono::system_clock::time_point start;
        int requests = 0;
    public:
        StatisticHandler() {
            start = std::chrono::system_clock::now();
        }

        float getFromStart() {
            std::chrono::duration<float> seconds = std::chrono::system_clock::now() - start;
            return seconds.count();
        }

        void registerRequest() {
            requests++;
        }

        virtual int getRequests() {
            return requests;
        }

        virtual int getActive() {
            return 1;
        }
};
