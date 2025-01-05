#include "request.h"
#include <random>
#include <string>

Request::Request(char job_type)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    ip_in = "ip_in";
    ip_out = "ip_out";
    if(job_type == 's')
    {
        std::uniform_int_distribution<> dis(10, 40); 
        time = dis(gen);
    }
    else if(job_type == 'p')
    {
        std::uniform_int_distribution<> dis(50, 100); 
        time = dis(gen);
    }
}

int Request::getTime()
{
    return time;
}

void Request::setTime(int time_val)
{
    time = time_val;
}

