#include <Webserver.h>
#include <Request.h>
#include <vector>
#include <queue>

class LoadBalancer {

    private:
        std::vector<Webserver*> servers;
        std::queue<Request> requests;

    public:
        LoadBalancer();
        void addRequest(Request req);
        void processRequests();
        void addServer(Webserver* server);
        void removeServer(Webserver* server);
        void clear();

};