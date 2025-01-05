#include "web_server.h"
#include <iostream>

WebServer::WebServer(char type) : type(type), busy(false) {}
void WebServer::processRequest()
{
    current_request.setTime(current_request.getTime() - 1);

    if(current_request.getTime() == 0)
    {
        // std:: cout << "finished this request. server is now free" << std::endl;
        busy = false;
    }

}
Request WebServer::getRequest() 
{
    return current_request;
}

void WebServer::setRequest(Request& new_request)
{
    // std::cout << "getting assigned a new request of time " << std::to_string(new_request.getTime()) << std::endl;
    current_request = new_request;
    busy = true;
}

bool WebServer::getBusy()
{
    return busy;
}

