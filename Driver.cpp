#include <iostream>
#include <unistd.h>
#include <cmath>
#include <random>
#include <vector>
#include <string>
#include <fstream>

#include "Webserver.h"
#include "LoadBalancer.h"
#include "Request.h"
#include "Globals.h"

using namespace std;

int clock_cycle = 0;

string generateIP() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 255);
    string ip = to_string(dis(gen)) + "." + to_string(dis(gen)) + "." + to_string(dis(gen)) + "." + to_string(dis(gen));
    return ip;
}

Request generateRequests() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(5, 500);
    int processTime = dis(gen);
    Request req = Request(generateIP(), generateIP(), processTime);
    return req;
}

vector<Request> generateRequests(int numRequests) {
    vector<Request> reqs;
    for(int i = 0; i < numRequests; i++) {
        Request req = generateRequests();
        reqs.push_back(req);
    }
    return reqs;
}

void simulate(int time, LoadBalancer& balancer) {
    //log initial state in log file
    std::ofstream logFile("log.txt", std::ios::app);
    if(logFile.is_open()) {
        logFile << "Simulation has begun" << endl;
        logFile << "Server count: " << balancer.getServerCount() << endl;
        logFile << "Simulation Duration: " << time << endl;
        logFile << "Starting queue size: " << balancer.getQueueSize() << endl;
        logFile.close();
    }
    while(clock_cycle < time) {
        balancer.processRequests();
        //only adjust every 100 cycles

        //60% chance of adjusting server
        random_device rand;
        mt19937 g(rand());
        uniform_int_distribution<> dist(1, 10);
        if(dist(g) <= 6) {
            balancer.adjustServers();
        }

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1, 100);
        if(dis(gen) == 1) {
            Request req = generateRequests();
            if(logFile.is_open()) {
                logFile << "[" << clock_cycle << "] " << "New Request has been made from " << req.get_ip_in() << " to " << req.get_ip_out() << endl;
                logFile.close();
            }
        }

        clock_cycle++;     
    }
    
    bool allServersIdle = balancer.all_servers_idle();
    balancer.clearServers();

    std::ofstream finalLog("log.txt", std::ios::app);
    if(finalLog.is_open()) {
        finalLog << "Simulation ended" << endl;
        finalLog << "All servers idle: " << (allServersIdle ? "true" : "false") << endl;
        finalLog << "Ending queue size: " << balancer.getQueueSize() << endl;
        finalLog << "Ending server count: " << balancer.getServerCount() << endl;
        finalLog.close();
    }
}

int main(int argc, char* argv[]) {
    int opt;
    int numServers = 0, time = 0;
    while((opt = getopt(argc, argv, "s:t:")) != -1) {
        switch(opt) {
            case 's':
                numServers = atoi(optarg);
                break;
            case 't':
                time = atoi(optarg);
                break;
        }
    }
    if(numServers == 0 || time == 0) {
        cout << "Usage: ./Driver -s <servers> -t <time>" << endl;
    } else {
        LoadBalancer balancer = LoadBalancer(numServers);
        //generate requests
        vector<Request> reqs = generateRequests(numServers * 100);
        for(Request req : reqs) {
            balancer.addRequest(req);
        }
        //start simulation
        simulate(time, balancer);
    }
}