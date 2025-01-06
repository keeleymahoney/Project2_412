#ifndef REQUEST_H
#define REQUEST_H
#include <string> 

class Request {
    public:
        Request();
        Request(char job_type);
        int getTime();
        void setTime(int time_val);
        std::string getIPIn();
        std::string getIPOut();


    private:
        std::string generateIP();
        int time;
        char job_type;
        std::string ip_in;
        std::string ip_out;
};

#endif