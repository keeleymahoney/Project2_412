/**
 * @file request.cpp
 * @brief Implementation of the Request class.
 * 
 * This file provides the implementation for creating and managing requests, 
 * including generating random IP addresses and assigning job types.
 */

#include "request.h"
#include <random>
#include <string>
#include <iostream>


/**
 * @brief Default constructor for the Request class.
 * 
 * Initializes the request with default values.
 */
Request::Request()
{
   ip_in = "";
   ip_out = "";
   job_type = '\0';
   time = -1;
}

/**
 * @brief Parameterized constructor for the Request class.
 * 
 * Creates a request of a specified job type ('s' or 'p') and assigns
 * random processing time and IP addresses.
 * 
 * @param job_type The type of job ('s' for streaming, 'p' for processing).
 */
Request::Request(char job_type): job_type(job_type)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    ip_in = generateIP();
    ip_out = generateIP();
    if(job_type == 's')
    {
        std::uniform_int_distribution<> dis(10, 40); 
        time = dis(gen);
        std::cout << "Created a new request of size " << std::to_string(time) << " for type s with IP_IN " << ip_in << " and IP_OUT " << ip_out << std::endl;
    }
    else if(job_type == 'p')
    {
        std::uniform_int_distribution<> dis(50, 100); 
        time = dis(gen);
        std::cout << "Created a new request of size " << std::to_string(time) << " for type p with IP_IN " << ip_in << " and IP_OUT " << ip_out << std::endl;
    }
    
}

/**
 * @brief Retrieves the incoming IP address of the request.
 * 
 * @return A string representing the incoming IP address.
 */
std::string Request::getIPIn()
{
    return ip_in;
}

/**
 * @brief Retrieves the outgoing IP address of the request.
 * 
 * @return A string representing the outgoing IP address.
 */
std::string Request::getIPOut()
{
    return ip_out;
}

/**
 * @brief Generates a random IPv4 address.
 * 
 * @return A string representing a randomly generated IPv4 address.
 */
std::string Request::generateIP()
{
    std::string ipv4 = "";

    for (int i = 0; i < 4; ++i) {
        int octet = rand() % 256;

        ipv4 += std::to_string(octet);

        if (i < 3) {
            ipv4 += ".";
        }
    }
    return ipv4;
}

/**
 * @brief Retrieves the remaining processing time for the request.
 * 
 * @return The remaining processing time as an integer.
 */
int Request::getTime()
{
    return time;
}

/**
 * @brief Updates the processing time for the request.
 * 
 * @param time_val The new processing time to set.
 */
void Request::setTime(int time_val)
{
    time = time_val;
}

