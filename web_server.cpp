#include "web_server.h"

WebServer::WebServer(): busy(false){}
void WebServer::processRequest()
{
    current_request.setTime(current_request.getTime() - 1);

    if(current_request.getTime() == 0)
    {
        busy = false;
    }

}
Request WebServer::getRequest() 
{
    return current_request;
}

void WebServer::setRequest(Request& new_request)
{
    current_request = new_request;
    busy = true;
}

bool WebServer::getBusy()
{
    return busy;
}

