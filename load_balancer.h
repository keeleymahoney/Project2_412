#ifndef LOAD_BALANCER_H
#define LOAD_BALANCER_H
#include <queue>
#include <vector>
#include "web_server.h"
#include "request.h"

class LoadBalancer
{
    public:
        LoadBalancer(char type);
        void assignRequest();
        void scaleUp(int num);
        void scaleDown(int num);
        void requestsGenerator(char type);
        void processServers();
        std::vector<WebServer>& getServers();
        std::queue<Request>& getRequests();

    private:
        std::vector<WebServer> servers;
        std::queue<Request> requests;
        char type;

};

#endif