#ifndef LOADBALANCER_H
#define LOADBALANCER_H
#include "Webserver.h"
#include "Request.h"
#include <vector>
#include <queue>
#include "Globals.h"

/// @file LoadBalancer.h
/// @brief Defines the LoadBalancer class, which manages a pool of web servers to distribute incoming requests evenly.

#define MAX_SERVERS 30;

/// @class LoadBalancer
/// @brief Manages a pool of web servers, distributing incoming requests among them to balance the load.
class LoadBalancer {

    private:
        /// @brief Stores a dynamic list of servers managed by the load balancer.
        std::vector<Webserver*> servers;
        /// @brief Holds the queue of incoming requests waiting to be distributed.
        std::queue<Request> requests;

    public:
        /// @brief Constructs a new LoadBalancer instance with initial settings.
        LoadBalancer();
        LoadBalancer(int num_servers);

        /// @brief Adds a new request to the queue to be processed.
        /// @param req The request to be added.
        void addRequest(Request req);
        /// @brief Processes and distributes requests from the queue to available servers.
        void processRequests();
        /// @brief Dynamically adjusts the number of servers based on the current load, adding or removing servers as needed.
        void adjustServers();
        /// @brief Sends a request to a specified server.
        /// @param server The server to which the request will be sent.
        void sendRequestToServer(Webserver* server);
        /// @brief Logs the start of a request processing for monitoring and debugging purposes.
        /// @param req The request that has started processing.
        void clearServers();
         void addServer();

        int getQueueSize();
        int getServerCount();

        bool all_servers_idle();

};
#endif