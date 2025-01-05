#include "load_balancer.h"
#include <iostream>
#include <random>

LoadBalancer:: LoadBalancer(char type) : type(type)
{

    for(int i = 0; i < 5; i++)
    {
        WebServer server = WebServer(type);

        servers.push_back(server);
    }
}

void LoadBalancer::assignRequest()
{
    for(auto& server : servers)
    {
        if(!(server.getBusy()))
        {
            if(requests.size() > 0)
            {
                server.setRequest(requests.front());
                requests.pop();
            }
            
        }
    }
}

void LoadBalancer::scale()
{
    if(std::ceil(requests.size() / 20.0) > servers.size())
    {
        std::cout << "The needed servers for type " << type << " is " << std::to_string(std::ceil(requests.size() / 20.0)) << " and the current number is " << std::to_string(servers.size()) << std::endl;
        scaleUp(std::ceil(requests.size() / 20.0) - servers.size());
    }

    else if(std::ceil(requests.size() / 20.0) < servers.size())
    {
        std::cout << "The needed servers for type " << type << " is " << std::to_string(std::ceil(requests.size() / 20.0)) << " and the current number is " << std::to_string(servers.size()) << std::endl;
        scaleDown(servers.size() - std::ceil(requests.size() / 20.0));
    }
}

void LoadBalancer::scaleUp(int num)
{
    std::cout << "adding " << std::to_string(num) << " servers" << std::endl;
    for(int i = 0; i < num; i++)
    {
        servers.push_back(WebServer(type));
    }
}

void LoadBalancer::scaleDown(int num)
{
    std::cout << "deleting " << std::to_string(num) << " servers" << std::endl;
    for(int i = 0; i < num; i++)
    {
        servers.pop_back();
    }
}

void LoadBalancer::processServers()
{
    for(auto& server : servers)
    {
        server.processRequest();
    }
}

void LoadBalancer::generateRequests()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 4); 

    for(int i = 0; i < dis(gen); i++)
    {
        requests.push(Request(type));
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

