#pragma once

#include "stdafx.h"
#include<boost/asio.hpp>
#include <json/json.h>
#include "Log.h"


using namespace boost::asio;
using boost::asio::ip::tcp;
using boost::system::error_code;

class MessageHandler {
public:
    MessageHandler() {
    }

    ~MessageHandler() {
    }

    string stat(float fromStart, float fromConnectionStart, int requests, int active) {
        Json::Value json;
        json["fromStart"] = fromStart;
        json["fromConnectionStart"] = fromConnectionStart;
        json["requests"] = requests;
        json["activeConnections"] = active;

        return encode(json);
    }

    string inc(int count) {
        Json::Value json;
        json["status"] = "ok";
        json["hits"] = count;

        return encode(json);
    }

    string get(int count) {
        Json::Value json;
        json["status"] = "ok";
        json["hits"] = count;

        return encode(json);
    }

    string sleep(int seconds) {
        return "";
    }

    string end() {
        return "";
    }

    string write(string key, string value) {
        return "";
    }

    string read(string value) {
        Json::Value json;
        json["status"] = "ok";
        json["value"] = value;

        return encode(json);
    }

    string del(string key) {
        return "";
    }

    string ok() {
        Json::Value json;
        json["status"] = "ok";
        Log::print(encode(json));
        return encode(json);
    }

    string error() {
        Json::Value json;
        json["status"] = "error";
        Log::print(encode(json));
        return encode(json);
    }

    string encode(Json::Value& json) {
        Json::StreamWriterBuilder encodeBuilder;
        return Json::writeString(encodeBuilder, json);
    }

    Json::Value decode(string jsonString) {
        JSONCPP_STRING error;
        Json::Value root;

        Json::CharReaderBuilder decodeBuilder;
        Json::CharReader* decodeReader = decodeBuilder.newCharReader();

        if (!decodeReader->parse(jsonString.c_str(), jsonString.c_str() + jsonString.size(), &root, &error)) {
            throw std::exception();
        }

        delete decodeReader;

        return root;
    }
};
