#ifndef LOAD_BALANCER_H
#define LOAD_BALANCER_H
#include <queue>
#include <vector>
#include "web_server.h"
#include "request.h"

class LoadBalancer
{
    public:
        LoadBalancer(char type, int num);
        void assignRequest();
        void scaleUp(int num);
        void scaleDown(int num);
        void generateRequests();
        void processServers();
        void scale();
        int getTotalRequests();
        int getScaleUp();
        int getScaleDown();
        std::vector<WebServer>& getServers();
        std::queue<Request>& getRequests();

    private:
        std::vector<WebServer> servers;
        std::queue<Request> requests;
        char type;
        int scale_up;
        int scale_down;

};

#endif