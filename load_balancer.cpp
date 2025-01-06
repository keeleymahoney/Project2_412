/**
 * @file load_balancer.cpp
 * @brief Implementation of the LoadBalancer class.
 * 
 * This file contains the implementation of the LoadBalancer class which is 
 * responsible for managing a pool of web servers, assigning requests to servers, 
 * scaling up or down based on the number of pending requests, and processing requests.
 */

#include "load_balancer.h"
#include <iostream>
#include <random>

/**
 * @brief Constructs a LoadBalancer object.
 * 
 * Initializes the LoadBalancer with a specified job type ('s' or 'p') and a 
 * given number of servers. Each server is added to the LoadBalancer's server pool.
 * 
 * @param type The job type for this LoadBalancer ('s' or 'p').
 * @param num The initial number of servers for the LoadBalancer.
 */
LoadBalancer:: LoadBalancer(char type, int num) : type(type), scale_up(0), scale_down(0)
{
    for(int i = 0; i < num; i++)
    {
        WebServer server = WebServer(type);

        servers.push_back(server);
    }
}

/**
 * @brief Assigns pending requests to available servers.
 * 
 * The function iterates through all servers, and if a server is not busy, it 
 * assigns the first request in the queue to that server.
 */
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

/**
 * @brief Scales the number of servers based on the current queue size.
 * 
 * The function determines the number of servers needed based on the queue size 
 * (calculated as `ceil(requests.size() / 20.0)`), and scales the number of 
 * servers up or down accordingly.
 */
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

/**
 * @brief Increases the number of servers by a specified amount.
 * 
 * This function adds `num` new servers to the server pool and increments the 
 * scale-up count.
 * 
 * @param num The number of servers to add.
 */
void LoadBalancer::scaleUp(int num)
{
    std::cout << "Adding " << std::to_string(num) << " servers to type " << type <<  std::endl;
    for(int i = 0; i < num; i++)
    {
        servers.push_back(WebServer(type));
    }
    scale_up++;
}

/**
 * @brief Decreases the number of servers by a specified amount.
 * 
 * This function removes `num` servers from the server pool and increments the 
 * scale-down count.
 * 
 * @param num The number of servers to remove.
 */
void LoadBalancer::scaleDown(int num)
{
    std::cout << "Deleting " << std::to_string(num) << " servers from type " << type <<  std::endl;
    for(int i = 0; i < num; i++)
    {
        servers.pop_back();
    }
    scale_down++;
}

/**
 * @brief Processes requests on all servers.
 * 
 * Iterates over each server in the pool and processes one request for each 
 * server, if available.
 */
void LoadBalancer::processServers()
{
    for(auto& server : servers)
    {
        server.processRequest();
    }
}

/**
 * @brief Generates a random number of new requests and adds them to the queue.
 * 
 * A random number of requests (between 1 and 4) are generated and added to the 
 * request queue based on the job type ('s' or 'p').
 */
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

/**
 * @brief Gets the list of servers managed by this LoadBalancer.
 * 
 * @return A reference to the vector of WebServer objects.
 */
std::vector<WebServer>& LoadBalancer::getServers()
{
    return servers;
}

/**
 * @brief Gets the queue of pending requests for this LoadBalancer.
 * 
 * @return A reference to the request queue.
 */
std::queue<Request>& LoadBalancer::getRequests()
{
    return requests;
}

/**
 * @brief Gets the total number of requests processed by all servers.
 * 
 * This function iterates over all servers and sums their total processed requests.
 * 
 * @return The total number of requests processed by all servers.
 */
int LoadBalancer::getTotalRequests()
{
    int total = 0;
    for(auto& server : servers)
    {
        total += server.getTotal();
    }
    return total;

}

/**
 * @brief Gets the number of times servers have been scaled up.
 * 
 * @return The number of times servers have been scaled up.
 */
int LoadBalancer::getScaleUp()
{
    return scale_up;
}

/**
 * @brief Gets the number of times servers have been scaled down.
 * 
 * @return The number of times servers have been scaled down.
 */
int LoadBalancer::getScaleDown()
{
    return scale_down;
}

