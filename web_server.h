#ifndef WEB_SERVER_H
#define WEB_SERVER_H
#include "request.h"

class WebServer {
    public:
        WebServer(char type);
        void processRequest();
        Request getRequest();
        bool getBusy();
        int getTotal();
        void setRequest(Request& request);
        
    private:
        Request current_request;
        char type;
        bool busy;
        int total_processed;
        

};

#endif