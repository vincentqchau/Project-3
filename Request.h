#ifndef REQUEST_H
#define REQUEST_H
#include <string>

/// @file Request.h
/// @brief Defines the Request class, encapsulating details of a network request including its source and destination IP addresses, and processing time.

/// @class Request
/// @brief Represents a network request with input and output IP addresses and processing time.
class Request {
    private:
        /// @brief IP address from which the request originates.
        std::string ip_in;
        /// @brief IP address to which the request is sent.
        std::string ip_out;
        /// @brief Time required to process the request.
        int process_time;

    public:
        /// @brief Default constructor initializing an empty request.
        Request();
        /// @brief Constructs a request with specified input and output IPs and processing time.
        /// @param in Input IP address.
        /// @param out Output IP address.
        /// @param time Processing time for the request.
        Request(std::string in, std::string out, int time);

        /// @brief Gets the input IP address of the request.
        /// @return Input IP address as a string.
        std::string get_ip_in();
        /// @brief Gets the output IP address of the request.
        /// @return Output IP address as a string.
        std::string get_ip_out();
        /// @brief Gets the processing time of the request.
        /// @return Processing time as an integer.
        int get_process_time();
        /// @brief Simulates the processing of the request.
        void process();
        /// @brief Prints the request details.
        void print();
};

#endif