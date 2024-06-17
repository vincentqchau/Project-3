#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>

#include "LoadBalancer.h"
#include "Globals.h"

using namespace std;

LoadBalancer::LoadBalancer() {
    LoadBalancer(1);
}

LoadBalancer::LoadBalancer(int num_servers) {
    servers = vector<Webserver*>();
    requests = queue<Request>();
    for(int i = 0; i < num_servers; i++) {
        servers.push_back(new Webserver(i));
    }
}

void LoadBalancer::processRequests() {
    for (int i = 0; i < (int)(servers.size()); i++) {
        if(!servers[i]->isBusy() && !requests.empty()) {
            sendRequestToServer(servers[i]);
        } else {
            servers[i]->processRequest();
            if(servers[i]->isRequestDone()) {
                //log request
                std::ofstream logFile("log.txt", std::ios::app);
                if(logFile.is_open()) {
                    logFile <<  "[" << clock_cycle << "] " << "SERVER " << servers[i]->getServerId() << " completed request." << endl;
                }
                if(!requests.empty()) {
                    sendRequestToServer(servers[i]);
                } else {
                    servers[i]->setRequest(Request());
                    servers[i]->setIsBusy(false);
                }
            }
        }
    }
}

void LoadBalancer::sendRequestToServer(Webserver* server) {
    Request next_req = requests.front();
    server->setRequest(next_req);
    server->setIsBusy(true);
    requests.pop();
    //log request
    std::ofstream logFile("log.txt", std::ios::app);
    if(logFile.is_open()) {
        logFile << "[" << clock_cycle << "] " << "Request from " << next_req.get_ip_in() << " to " << next_req.get_ip_out() << " sent to SERVER "  << server->getServerId() << " for DURATION " << next_req.get_process_time() << endl;
    }
} 

void LoadBalancer::adjustServers() {
    //count how many servers are busy
    int busyServers = 0;
    for(Webserver* server : servers) {
        if(server->isBusy()) {
            busyServers++;
        }
    }
    int max_servers = MAX_SERVERS;
    if(busyServers == (int)servers.size() && (int)servers.size() < max_servers) {
        servers.push_back(new Webserver(servers.size()-1));
        //log server addition
        std::ofstream logFile("log.txt", std::ios::app);
        if(logFile.is_open()) {
            logFile << "[" << clock_cycle << "] " << "SERVER" << servers.size()-1 << " has been created." << endl;
        }
    } else if(busyServers < (int)(servers.size()/10) && servers.size() > 1) {
        //find a non busy server to remove
        for(Webserver* server : servers) {
            if(!server->isBusy()) {
                servers.erase(std::remove(servers.begin(), servers.end(), server), servers.end());
                delete server;
                //log server removal
                std::ofstream logFile("log.txt", std::ios::app);
                if(logFile.is_open()) {
                    logFile << "[" << clock_cycle << "] " << "SERVER" << servers.size()-1 << " has been removed." << endl;
                }
                break;
            }
        }
    }
}

bool LoadBalancer::all_servers_idle() {
    for(Webserver* server : servers) {
        if(server->isBusy()) {
            return false;
        }
    }
    return true;
}

void LoadBalancer::clearServers() {
    for(Webserver* server : servers) {
        std::ofstream logFile("log.txt", std::ios::app);
        if(logFile.is_open()) {
            logFile << "[" << clock_cycle << "] " << "SERVER" << server->getServerId() << " has been deallocated" << endl;
        }
        delete server;
    }
    servers.clear();
}

void LoadBalancer::addRequest(Request req) {
    requests.push(req);
}

int LoadBalancer::getQueueSize() {
    return requests.size();
}

int LoadBalancer::getServerCount() {
    return servers.size();
}
