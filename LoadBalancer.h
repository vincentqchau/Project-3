#include <Webserver.h>
#include <Request.h>
#include <vector>
#include <queue>

#define MIN_REQUESTS_PER_SERVER 5;
#define MAX_REQUESTS_PER_SERVER 25;

class LoadBalancer {

    private:
        std::vector<Webserver*> servers;
        std::queue<Request> requests;
        int total_wait_time;

    public:
        LoadBalancer();
        void addRequest(Request req);
        void processRequests();
        void addServer(Webserver* server);
        void removeServer(Webserver* server);
        void clear();
        int getWaitTime();
        void adjustServers();

};