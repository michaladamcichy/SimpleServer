#pragma once

#include<iostream>
#include<fstream>
#include<cstdio>
#include<vector>
#include<thread>
#include<mutex>
#include<string>
#include<cstring>
#include<cstdio>
#include<map>
#include<unordered_map>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<cassert>
#include<chrono>
#include<ctime>
#include<cstdio>
#include <memory>
#include <set>
#include <sstream>
#include <exception>
#include <functional>
#include <signal.h>
#include <unistd.h>
#include <iomanip>

using std::cout;
using std::vector;
using std::map;
using std::unordered_map;
using std::pair;
using std::string;
using std::to_string;
using std::ifstream;
using std::getline;
using std::max;
using std::min;
using std::ofstream;
using std::ifstream;
using std::set;
using std::move;
using std::stringstream;
using std::endl;
using std::function;

template<class X, class Y>
using hashmap = unordered_map<X,Y>;

#define uint unsigned int