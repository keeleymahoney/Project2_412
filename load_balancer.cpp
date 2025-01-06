#include "load_balancer.h"
#include <iostream>
#include <random>

LoadBalancer:: LoadBalancer(char type, int num) : type(type), scale_up(0), scale_down(0)
{
    for(int i = 0; i < num; i++)
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
    std::cout << "Adding " << std::to_string(num) << " servers to type " << type <<  std::endl;
    for(int i = 0; i < num; i++)
    {
        servers.push_back(WebServer(type));
    }
    scale_up++;
}

void LoadBalancer::scaleDown(int num)
{
    std::cout << "Deleting " << std::to_string(num) << " servers from type " << type <<  std::endl;
    for(int i = 0; i < num; i++)
    {
        servers.pop_back();
    }
    scale_down++;
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

int LoadBalancer::getTotalRequests()
{
    int total = 0;
    for(auto& server : servers)
    {
        total += server.getTotal();
    }
    return total;

}

int LoadBalancer::getScaleUp()
{
    return scale_up;
}

int LoadBalancer::getScaleDown()
{
    return scale_down;
}

