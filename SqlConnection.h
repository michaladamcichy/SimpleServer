#pragma once

#include "stdafx.h"
#include<boost/asio.hpp>
#include "Log.h"
#include "Network.h"
#include "MessageHandler.h"

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

class SqlConnection {
private:
    static string address;
    static int port;
    static string user;
    static string password;

    static sql::Driver* driver;;

    sql::Connection* connection;
public:
    static void init(string _address, int _port, string _user, string _password) {
        address = _address;
        port = _port;
        user = _user;
        password = _password;
        
        driver = get_driver_instance();
        
        testConnection();
    }

    static void testConnection() {

    }

    SqlConnection() {
        connection = driver->connect( "tcp://" + address + ":" + to_string(port), user, password);
        connection->setSchema("server");
    }

    ~SqlConnection() {
        delete connection;
    }

    void inc(long long number) {

    }

    int get(long long number) {
        return 0;
    }

    void write(string key, string value) {
        sql::Statement* statement = connection->createStatement();
        sql::ResultSet* result = statement->executeQuery("SELECT keyvalue_key from keyvalues WHERE keyvalue_key=\'" + key + "\';");

        if(result->next()) {
            result = statement->execute("UPDATE keyvalues SET keyvalue_value=\'" + value + "\' WHERE keyvalue_key=\'" + key + "\';");
        } else {
            result = statement->execute("INSERT INTO keyvalues VALUES(\'" + key + "\', \'" + value + "\');");
        }
        delete result;
        delete statement;
    }

    string read(string key) {
        sql::Statement* statement = connection->createStatement();
        sql::ResultSet* result = statement->executeQuery("SELECT keyvalue_value from keyvalues WHERE keyvalue_key=\'" + key + "\';");

        string value = "";
        if(result->next()) {
            value = result->getString(1);
        }

        delete result;
        delete statement;

        return value;
    }

    static void printErrorMessage(sql::SQLException& e) {
        stringstream stream;

        stream << "# ERR: SQLException in " << __FILE__;
        stream << "(" << __FUNCTION__ << ") on line ";
        stream << __LINE__ << endl;
        stream << "# ERR: " << e.what();
        stream << " (MySQL error code: " << e.getErrorCode();
        stream << ", SQLState: " << e.getSQLState() << " )" << endl;

        Log::print(stream.str());
    }


private:
};

string SqlConnection::address = "127.0.0.1";
int SqlConnection::port = 3306;
string SqlConnection::user = "root";
string SqlConnection::password = "";

sql::Driver* SqlConnection::driver;
