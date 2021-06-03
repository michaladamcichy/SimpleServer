#pragma once
#include "stdafx.h"

class Log {
private:
    static bool enabled;
    static string last;
    static stringstream buffer;
    static int repeats;

public:
    static string timestamp() {
        auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        string time = ctime(&timenow);
        time[time.size() - 1] = ':';
        time += " ";

        return time;
    } 

    template<class T>
    static void print(T value) {
        cout << timestamp() << value << endl;
    }

    template<class T>
    static void print(string text, T value) {
        cout << timestamp() << text << ": " << value << endl;
    }

    static void done() {
        cout << timestamp() << "DONE\n";
    }

    static void enable() {
        enabled = true;
    }

    static void disable() {
        enabled = false;
    }
};

bool Log::enabled = false;
string Log::last = "";
stringstream Log::buffer;
int Log::repeats = 0;