#include "request.h"
#include <random>
#include <string>
#include <iostream>

Request::Request()
{
   ip_in = "";
   ip_out = "";
   job_type = '\0';
   time = -1;
}
Request::Request(char job_type): job_type(job_type)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    ip_in = "ip_in";
    ip_out = "ip_out";
    if(job_type == 's')
    {
        std::uniform_int_distribution<> dis(10, 40); 
        time = dis(gen);
        std::cout << "Created a new request of size " << std::to_string(time) << " for type s" << std::endl;
    }
    else if(job_type == 'p')
    {
        std::uniform_int_distribution<> dis(50, 100); 
        time = dis(gen);
        std::cout << "Created a new request of size " << std::to_string(time) <<  "for type p" << std::endl;
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

