#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>

#include "LoadBalancer.h"

using namespace std;

LoadBalancer::LoadBalancer() {
    servers = vector<Webserver*>();
    requests = queue<Request>();
    waitTime = 0;
}

void LoadBalancer::addRequest(Request req) {
    requests.push(req);
    waitTime+=req.get_process_time();
}

void LoadBalancer::sendRequestToServer(Webserver* server) {
    Request next_req = requests.front();
    server->set_curr_req(next_req);
    waitTime-=next_req.get_process_time();
    server-> set_is_busy(true);
    requests.pop();
    //log request in text file
    logRequestStart(next_req);
} 

void LoadBalancer::processRequests() {
    for (int i = 0; i < (int)(servers.size()); i++) {
        if(!servers[i]->get_is_busy() && !requests.empty()) {
            sendRequestToServer(servers[i]);
        } else {
            servers[i]->process_req();
            if(servers[i]->request_is_done()) {
                logRequestFinish(servers[i]->get_curr_req());
                if(!requests.empty()) {
                    sendRequestToServer(servers[i]);
                } else {
                    servers[i]->set_curr_req(Request());
                    servers[i]->set_is_busy(false);
                }
            }
        }
    }
}

void LoadBalancer::adjustServers() {
    int busyServers = count_if(servers.begin(), servers.end(), [](Webserver* server){ return server->get_is_busy(); });
    int totalServers = servers.size();
    float busyPercentage = static_cast<float>(busyServers) / totalServers;

    // Thresholds
    const float scaleUpThreshold = 1.0; // 100% busy
    const float scaleDownThreshold = 0.5; // 50% busy

    // Scale up if all servers are busy
    if (busyPercentage >= scaleUpThreshold) {
        addServer(new Webserver());
    }
    // Scale down if less than 50% servers are busy, ensuring at least one server remains
    else if (busyPercentage <= scaleDownThreshold && totalServers > 1) {
        removeServer();
    }
}

void LoadBalancer::addServer(Webserver* server) {
    servers.push_back(server);
}


void LoadBalancer::removeServer() {
    // Remove the first idle server found
    auto it = find_if(servers.begin(), servers.end(), [](Webserver* server){ return !server->get_is_busy(); });
    if (it != servers.end()) {
        delete *it; // Delete the dynamically allocated Webserver object
        servers.erase(it); // Remove the pointer from the vector
    }
}

void LoadBalancer::logRequestStart(Request req) {
    //write to log.txt file
    std::ofstream logFile("log.txt", std::ios::app);
    if(logFile.is_open()) {
        logFile << "[" << clock_cycle << "] START Request from " << req.get_ip_in() << " to " << req.get_ip_out() << endl;
        logFile.close(); 
    }
}

void LoadBalancer::logRequestFinish(Request req) {
    std::ofstream logFile("log.txt", std::ios::app);
    if(logFile.is_open()) {
        logFile << "[" << clock_cycle << "] FINISH Request from " << req.get_ip_in() << " to " << req.get_ip_out() << endl;
        logFile.close(); 
    }
}

void LoadBalancer::clearServers() {
    for(Webserver* server : servers) {
        delete server;
    }
    servers.clear();
}

int LoadBalancer::getWaitTime() {
    return waitTime;
}

