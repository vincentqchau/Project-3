#include <LoadBalancer.h>

using namespace std;

LoadBalancer::LoadBalancer() {
    servers = vector<Webserver*>();
    requests = queue<Request>();
}

void LoadBalancer::addRequest(Request req) {
    requests.push(req);
}

void LoadBalancer::processRequests() {
    for (int i = 0; i < servers.size(); i++) {
        if(servers[i]->get_curr_req() == NULL) {
            if(!requests.empty()) {
                servers[i]->set_curr_req(&requests.front());
                requests.pop();
            }
        } else {
            if(servers[i]->process_req()) {
                if(requests.empty()) {
                    servers[i]->set_curr_req(NULL);
                } else {
                    servers[i]->set_curr_req(&requests.front());
                    requests.pop();
                }
            }
        }
    }
}

void LoadBalancer::addServer(Webserver* server) {
    servers.push_back(server);
}

void LoadBalancer::removeServer(Webserver* server) {
    for(int i = 0; i < servers.size(); i++) {
        if(servers[i] == server) {
            servers.erase(servers.begin() + i);
        }
    }
}

void LoadBalancer::clear() {
    servers.clear();
}

