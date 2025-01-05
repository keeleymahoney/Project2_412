#ifndef REQUEST_H
#define REQUEST_H
#include <string> 

class Request {
    public:
        Request(char job_type);
        int getTime();
        void setTime(int time_val);


    private:
        int time;
        char job_type;
        std::string ip_in;
        std::string ip_out;
};

#endif