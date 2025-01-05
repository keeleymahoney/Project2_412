#include "web_server.h"
#include "request.h"
#include "load_balancer.h"
#include <iostream>

int main()
{
    int time = 0;
    LoadBalancer s_balancer = LoadBalancer('s');
    LoadBalancer p_balancer = LoadBalancer('p');

    for(int i = 0; i < 100; i++)
    {
        s_balancer.getRequests().push(Request('s'));
        p_balancer.getRequests().push(Request('p'));
    }

    while(time < 10,000)
    {
        s_balancer.processServers();
        p_balancer.processServers();
        s_balancer.assignRequest();
        p_balancer.assignRequest();
        time++;
    }


}