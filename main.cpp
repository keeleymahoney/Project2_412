/**
 * @file main.cpp
 * @brief Entry point for the load balancing simulation.
 * 
 * Simulates the behavior of load balancers managing requests across web servers.
 * Users can specify the number of time cycles and servers for both streaming ('s') 
 * and processing ('p') job types. The program generates requests, processes them, 
 * and scales servers dynamically based on time cycles.
 */

#include "web_server.h"
#include "request.h"
#include "load_balancer.h"
#include <iostream>

/**
 * @brief Main function for the load balancing simulation.
 * 
 * This function initializes the load balancers, generates requests, processes 
 * them through time cycles, and dynamically scales the servers. At the end, 
 * it outputs statistics about the load balancers and their performance.
 * 
 * @return Returns 0 upon successful execution.
 */
int main()
{
    int time = 0;
    int s_servers = 0;
    int p_servers = 0;
    std::cout << "Please enter the number of time cycles you would like to use: " << std::endl;
    std::cin >> time;

    std::cout << "Please enter the number of s servers you would like to use: " << std::endl;
    std::cin >> s_servers;

    std::cout << "Please enter the number of p servers you would like to use: " << std::endl;
    std::cin >> p_servers;
    
    LoadBalancer s_balancer = LoadBalancer('s', s_servers);
    LoadBalancer p_balancer = LoadBalancer('p', p_servers);

    for(int i = 0; i < 20*s_servers; i++)
    {
        s_balancer.getRequests().push(Request('s'));
    }

    for(int k = 0; k < 20*p_servers; k++)
    {
        p_balancer.getRequests().push(Request('p'));
    }

    for(int j = 0; j < time; j++)
    {
        std::cout << "Time cycle: " << j << std::endl;
        s_balancer.processServers();
        p_balancer.processServers();
        s_balancer.assignRequest();
        p_balancer.assignRequest();

        if(j % 25 == 0)
        {
            s_balancer.generateRequests();
            p_balancer.generateRequests();
        }

        if(j % 50 == 0)
        {
            s_balancer.scale(); 
            
        }

        if(j % 100 == 0)
        {
            p_balancer.scale();
        }
    }

    std::cout << '\n' << std::endl;
    std::cout << "---------Stats for s load balancer---------" << std::endl;
    std::cout << "S requests range from 10 to 40 seconds" << std::endl;
    std::cout << "Initial servers: " << s_servers << std::endl;
    std::cout << "Initial starting queue size: " << (20*s_servers) << std::endl;
    std::cout << "Total Requests processed: " << s_balancer.getTotalRequests() << std::endl;
    std::cout << "Total servers scaled up: " << s_balancer.getScaleUp() << std::endl;
    std::cout << "Total servers scaled down: " << s_balancer.getScaleDown() << std::endl;
    std::cout << "Current number of servers: " << s_balancer.getServers().size() << std::endl;
    std::cout << "Current number of requests in the queue " << s_balancer.getRequests().size() << std::endl << std::endl;

    std::cout << "---------Stats for p load balancer---------" << std::endl;
    std::cout << "P requests range from 50 to 100 seconds" << std::endl;
    std::cout << "Initial servers: " << p_servers << std::endl;
    std::cout << "Initial starting queue size: " << (20*p_servers) << std::endl;
    std::cout << "Total Requests processed: " << p_balancer.getTotalRequests() << std::endl;
    std::cout << "Total servers scaled up: " << p_balancer.getScaleUp() << std::endl;
    std::cout << "Total servers scaled down: " << p_balancer.getScaleDown() << std::endl;
    std::cout << "Current number of servers: " << p_balancer.getServers().size() << std::endl;
    std::cout << "Current number of requests in the queue " << p_balancer.getRequests().size() << std::endl << std::endl;

    std::cout << "Total time: " << time << " clock cycles" << std::endl;

    return 0;
}