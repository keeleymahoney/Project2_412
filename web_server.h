#ifndef WEB_SERVER_H
#define WEB_SERVER_H
#include "request.h"

class WebServer {
    public:
        WebServer();
        void processRequest();
        Request getRequest();
        bool getBusy();
        void setRequest(Request& request);
        
    private:
        Request current_request;
        bool busy;

};

#endif