#include <LoadBalancer.h>

using namespace std;

LoadBalancer::LoadBalancer() {
    servers = vector<Webserver*>();
    requests = queue<Request>();
}

void LoadBalancer::addRequest(Request req) {
    requests.push(req);
    total_wait_time+=req.get_process_time();
}

void LoadBalancer::processRequests() {
    for (int i = 0; i < servers.size(); i++) {
        if(servers[i]->get_curr_req() == NULL) {
            if(!requests.empty()) {
                Request next_req = requests.front();
                servers[i]->set_curr_req(&next_req);
                total_wait_time-=next_req.get_process_time();
                requests.pop();
            }
        } else {
            if(servers[i]->process_req()) {
                if(requests.empty()) {
                    servers[i]->set_curr_req(NULL);
                } else {
                    Request next_req = requests.front();
                    servers[i]->set_curr_req(&next_req);
                    total_wait_time-=next_req.get_process_time();
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

