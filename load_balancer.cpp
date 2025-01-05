#include "load_balancer.h"

LoadBalancer:: LoadBalancer(char type) : type(type)
{

    for(int i = 0; i < 5; i++)
    {
        WebServer server = WebServer();

        servers.push_back(server);
    }
}

void LoadBalancer::assignRequest()
{
    std::cout << "Assigning a request to server of type " << type << std::endl;
    for(auto& server : servers)
    {
        if(!(server.getBusy()))
        {
            server.setRequest(requests.front());
            requests.pop();
        }
    }
}

void LoadBalancer::scaleUp(int num)
{

}

void LoadBalancer::scaleDown(int num)
{

}

void LoadBalancer::processServers()
{
    td::cout << "Processing a server of type " << type << std::endl;
    for(auto& server : servers)
    {
        server.processRequest();
    }
}

std::vector<WebServer>& LoadBalancer::getServers()
{
    return servers;
}

std::queue<Request>& LoadBalancer::getRequests()
{
    return requests;
}

