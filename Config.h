#pragma once

#include "stdafx.h"
#include<boost/asio.hpp>
#include "Log.h"

using namespace boost::asio;
using boost::asio::ip::tcp;
using boost::system::error_code;

class Config {
public:
    static const int bufferSize = 10000;
};