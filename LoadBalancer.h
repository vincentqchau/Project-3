#ifndef LOADBALANCER_H
#define LOADBALANCER_H
#include "Webserver.h"
#include "Request.h"
#include <vector>
#include <queue>
#include "Globals.h"

/// @file LoadBalancer.h
/// @brief Defines the LoadBalancer class, which manages a pool of web servers to distribute incoming requests evenly.

#define MIN_REQUESTS_PER_SERVER 5; ///< Defines the minimum number of requests a server must handle before it's considered to be under heavy load.
#define MAX_REQUESTS_PER_SERVER 20; ///< Sets the maximum number of requests a server can handle before it stops accepting new requests.

/// @class LoadBalancer
/// @brief Manages a pool of web servers, distributing incoming requests among them to balance the load.
class LoadBalancer {

    private:
        /// @brief Stores a dynamic list of servers managed by the load balancer.
        std::vector<Webserver*> servers;
        /// @brief Holds the queue of incoming requests waiting to be distributed.
        std::queue<Request> requests;
        /// @brief Tracks the total wait time for all requests in the queue.
        int waitTime;

    public:
        /// @brief Constructs a new LoadBalancer instance with initial settings.
        LoadBalancer();
        /// @brief Adds a new request to the queue to be processed.
        /// @param req The request to be added.
        void addRequest(Request req);
        /// @brief Processes and distributes requests from the queue to available servers.
        void processRequests();
        /// @brief Adds a new server to the pool of servers managed by the load balancer.
        /// @param server Pointer to the server to be added.
        void addServer(Webserver* server);
        /// @brief Removes a server from the pool, typically used when a server is down or being decommissioned.
        void removeServer();
        /// @brief Dynamically adjusts the number of servers based on the current load, adding or removing servers as needed.
        void adjustServers();
        /// @brief Sends a request to a specified server.
        /// @param server The server to which the request will be sent.
        void sendRequestToServer(Webserver* server);
        /// @brief Logs the start of a request processing for monitoring and debugging purposes.
        /// @param req The request that has started processing.
        void logRequestStart(Request req);
        /// @brief Logs the completion of a request processing for monitoring and debugging purposes.
        /// @param req The request that has finished processing.
        void logRequestFinish(Request req);
        /// @brief Clears all servers from the load balancer, used during shutdown or reset procedures.
        void clearServers();
        /// @brief Retrieves the total wait time for all requests in the queue.
        /// @return The total wait time.
        int getWaitTime();
};
#endif