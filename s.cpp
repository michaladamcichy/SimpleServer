#include "stdafx.h"
#include<boost/asio.hpp>
#include "Log.h"
#include "Session.h"
#include "Server.h"

using namespace boost::asio;
using boost::asio::ip::tcp;
using boost::system::error_code;

int main(int argc, const char *argv[])
{   
    if(argc != 6) {
        cout << "Args:\nport_to_run_server, database_address, database_port, db_user, db_password\nuse _ as no password";
        return 1;
    }
    Log::enable();
    
    io_context context;
    tcp::endpoint endpoint(tcp::v4(), atoi(argv[1]));

    Server server(context, endpoint);

    string password;

    if(argv[5][0] == '_')
        password = "";
    else password = argv[5];

    SqlConnection::init(argv[2], atoi(argv[3]), argv[4], password);

    server.run();

    return 0;
}
