#ifndef LOADBALANCER_H
#define LOADBALANCER_H
#include "Webserver.h"
#include "Request.h"
#include <vector>
#include <queue>
#include "Globals.h"

#define MIN_REQUESTS_PER_SERVER 5;
#define MAX_REQUESTS_PER_SERVER 20;

class LoadBalancer {

    private:
        std::vector<Webserver*> servers;
        std::queue<Request> requests;
        int waitTime;

    public:
        LoadBalancer();
        void addRequest(Request req);
        void processRequests();
        void addServer(Webserver* server);
        void removeServer();
        void adjustServers();
        void sendRequestToServer(Webserver* server);
        void logRequestStart(Request req);
        void logRequestFinish(Request req);
        void clearServers();
        int getWaitTime();
};
#endif