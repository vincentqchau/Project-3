#include <LoadBalancer.h>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <Globals.h>

using namespace std;

LoadBalancer::LoadBalancer() {
    servers = vector<Webserver*>();
    requests = queue<Request>();
}

void LoadBalancer::addRequest(Request req) {
    requests.push(req);
    total_wait_time+=req.get_process_time();
}

void LoadBalancer::sendRequestToServer(Webserver* server) {
    Request next_req = requests.front();
    server->set_curr_req(&next_req);
    server-> set_is_busy(true);
    total_wait_time-=next_req.get_process_time();
    requests.pop();
    //log request in text file
} 

void LoadBalancer::processRequests() {
    for (int i = 0; i < servers.size(); i++) {
        if(!servers[i]->get_is_busy() && !requests.empty()) {
            sendRequestToServer(servers[i]);
        } else {
            if(servers[i]->process_req()) {
                if(requests.empty()) {
                    servers[i]->set_curr_req(NULL);
                    servers[i]-> set_is_busy(false);
                } else {
                    sendRequestToServer(servers[i]);
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
    const int cooldownPeriod = 60; // Seconds
    static std::chrono::steady_clock::time_point lastScaleTime = std::chrono::steady_clock::now() - std::chrono::seconds(cooldownPeriod); // Initialize to allow immediate scaling

    std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
    std::chrono::seconds timeSinceLastScale = std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastScaleTime);

    // Scale up if all servers are busy and cooldown period has passed
    if (busyPercentage >= scaleUpThreshold && timeSinceLastScale.count() >= cooldownPeriod) {
        addServer(new Webserver());
        lastScaleTime = currentTime; // Update last scale time
    }
    // Scale down if less than 50% servers are busy and cooldown period has passed
    else if (busyPercentage <= scaleDownThreshold && totalServers > 1 && timeSinceLastScale.count() >= cooldownPeriod) { // Ensure at least one server remains
        // Remove the first idle server found
        auto it = std::find_if(servers.begin(), servers.end(), [](Webserver* server){ return !server->get_is_busy(); });
        if (it != servers.end()) {
            removeServer(*it);
            lastScaleTime = currentTime; // Update last scale time
        }
    }
}

void LoadBalancer::addServer(Webserver* server) {
    servers.push_back(server);
}

void LoadBalancer::removeServer(Webserver* server) {
    auto it = std::find(servers.begin(), servers.end(), server);
    if (it != servers.end()) {
        delete *it; // Deallocate memory
        servers.erase(it); // Remove pointer from vector
    }
}

void LoadBalancer::clear() {
    servers.clear();
}

int LoadBalancer::getWaitTime() {
    return total_wait_time;
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

