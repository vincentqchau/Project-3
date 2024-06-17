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
        Request req;
        /// @brief Flag indicating whether the web server is currently processing a request.
        bool busy;
        /// @brief
        int serverId;

    public:
        /// @brief Constructs a new Webserver instance, initially not busy.
        Webserver(int id);
        /// @brief Sets the current request for the web server to process.
        /// @param req The request to be processed.
        void setRequest(Request req);
        /// @brief Retrieves the current request being processed by the web server.
        /// @return The current request.
        Request getRequest();
        /// @brief Initiates the processing of the current request.
        void processRequest();
        /// @brief Sets the busy status of the web server.
        /// @param busy The new busy status.
        void setIsBusy(bool busy);
        /// @brief Retrieves the busy status of the web server.
        /// @return True if the web server is busy, false otherwise.
        bool isBusy();
        /// @brief Checks if the current request has finished processing.
        /// @return True if the request is done, false otherwise.
        bool isRequestDone();
        int getServerId();
};
#endif