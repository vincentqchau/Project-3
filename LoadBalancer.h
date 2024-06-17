#ifndef LOADBALANCER_H
#define LOADBALANCER_H
#include "Webserver.h"
#include "Request.h"
#include <vector>
#include <queue>
#include "Globals.h"

/// @file LoadBalancer.h
/// @brief Defines the LoadBalancer class, which manages a pool of web servers to distribute incoming requests evenly.

#define MAX_SERVERS 30; ///< Maximum number of servers that can be managed by the LoadBalancer.

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

        /// @brief Constructs a LoadBalancer with a specified number of servers.
        /// @param num_servers Initial number of servers to be added to the pool.
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

        /// @brief Clears all servers from the pool, typically used for cleanup or reinitialization.
        void clearServers();

        /// @brief Adds a new server to the pool, increasing the capacity for handling requests.
        void addServer();

        /// @brief Returns the number of requests currently waiting in the queue.
        /// @return The size of the request queue.
        int getQueueSize();

        /// @brief Returns the current number of servers in the pool.
        /// @return The number of servers.
        int getServerCount();

        /// @brief Checks if all servers are currently idle.
        /// @return True if all servers are idle, false otherwise.
        bool all_servers_idle();

};
#endif