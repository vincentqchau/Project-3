#ifndef WEBSERVER_H
#define WEBSERVER_H
#include "Request.h"

/// @file Webserver.h
/// @brief Defines the Webserver class, which simulates a web server's ability to process incoming network requests.

/// @class Webserver
/// @brief Represents a web server that can process requests.
class Webserver {
    private:
        /// @brief The current request being processed by the web server.
        Request curr_req;
        /// @brief Flag indicating whether the web server is currently processing a request.
        bool is_busy;

    public:
        /// @brief Constructs a new Webserver instance, initially not busy.
        Webserver();
        /// @brief Sets the current request for the web server to process.
        /// @param req The request to be processed.
        void set_curr_req(Request req);
        /// @brief Retrieves the current request being processed by the web server.
        /// @return The current request.
        Request get_curr_req();
        /// @brief Initiates the processing of the current request.
        void process_req();
        /// @brief Sets the busy status of the web server.
        /// @param busy The new busy status.
        void set_is_busy(bool busy);
        /// @brief Retrieves the busy status of the web server.
        /// @return True if the web server is busy, false otherwise.
        bool get_is_busy();
        /// @brief Checks if the current request has finished processing.
        /// @return True if the request is done, false otherwise.
        bool request_is_done();
};
#endif