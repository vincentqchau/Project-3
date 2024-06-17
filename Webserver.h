#ifndef WEBSERVER_H
#define WEBSERVER_H
#include "Request.h"

/// @file Webserver.h
/// @brief Defines the Webserver class, which simulates a web server's ability to process incoming network requests.

/// @class Webserver
/// @brief Represents a web server that can process requests.
///
/// This class models a web server which can be assigned requests to process. It keeps track of its busy status
/// and the current request it is handling.
class Webserver {
    private:
        /// @brief The current request being processed by the web server.
        Request req;
        /// @brief Flag indicating whether the web server is currently processing a request.
        bool busy;
        /// @brief Unique identifier for the web server.
        int serverId;

    public:
        /// @brief Constructs a new Webserver instance with a specified ID, initially not busy.
        /// @param id The unique identifier for the web server.
        Webserver(int id);

        /// @brief Assigns a request for the web server to process, setting it to busy.
        /// @param req The request to be processed by the web server.
        void setRequest(Request req);

        /// @brief Retrieves the current request being processed by the web server.
        /// @return The request currently being processed.
        Request getRequest();

        /// @brief Initiates the processing of the current request.
        /// This function simulates the processing of a request by the web server.
        void processRequest();

        /// @brief Sets the busy status of the web server.
        /// @param busy The new busy status of the web server.
        void setIsBusy(bool busy);

        /// @brief Retrieves the busy status of the web server.
        /// @return True if the web server is currently busy, false otherwise.
        bool isBusy();

        /// @brief Checks if the current request has finished processing.
        /// @return True if the request processing is complete, false otherwise.
        bool isRequestDone();

        /// @brief Retrieves the server's unique identifier.
        /// @return The unique identifier of the web server.
        int getServerId();
};
#endif