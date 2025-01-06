/**
 * @file web_server.cpp
 * @brief Implementation of the WebServer class.
 *
 * This file contains the implementation of the WebServer class,
 * which processes requests and tracks server activity.
 */

#include "web_server.h"
#include <iostream>

/**
 * @brief Constructs a WebServer object.
 * 
 * @param type The type of requests this server handles ('s' or 'p').
 */
WebServer::WebServer(char type) : type(type), busy(false), total_processed(0) {}


/**
 * @brief Processes the current request assigned to the server.
 * 
 * Reduces the processing time of the current request by 1 unit.
 * If the processing time reaches 0, the request is completed,
 * and the server becomes free.
 */
void WebServer::processRequest()
{
    current_request.setTime(current_request.getTime() - 1);

    if(current_request.getTime() == 0)
    {
        std:: cout << "Finished this " << type << " request with IP_IN " << current_request.getIPIn() << " and IP_OUT " << current_request.getIPOut() << ". Web Server is now free" << std::endl;
        busy = false;
        total_processed++;
    }

}

/**
 * @brief Retrieves the current request assigned to the server.
 * 
 * @return A copy of the current Request object.
 */
Request WebServer::getRequest() 
{
    return current_request;
}


/**
 * @brief Assigns a new request to the server.
 * 
 * @param new_request The new request to be processed by the server.
 */
void WebServer::setRequest(Request& new_request)
{
    std::cout << "Getting assigned a new " << type << " request of time " << std::to_string(new_request.getTime()) << " with IP_IN " << new_request.getIPIn() << " and IP_OUT " << new_request.getIPOut() << std::endl;
    current_request = new_request;
    busy = true;
}


/**
 * @brief Checks if the server is currently busy.
 * 
 * @return True if the server is busy, otherwise false.
 */
bool WebServer::getBusy()
{
    return busy;
}

/**
 * @brief Retrieves the total number of requests processed by the server.
 * 
 * @return The total number of completed requests.
 */
int WebServer::getTotal()
{
    return total_processed;
}

