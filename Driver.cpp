#include <iostream>
#include <unistd.h>
#include <Webserver.h>
#include <vector>
#include <LoadBalancer.h>
#include <cmath>
#include <random>
#include <Request.h>
#include <Globals.h>

#define MAX_LOAD_PER_BALANCER 75

using namespace std;

int clock_cycle = 0;

void simulate(int time, vector<LoadBalancer>& balancers) {
    while(clock_cycle < time) {
        for(LoadBalancer balancer : balancers) {
            balancer.processRequests();
        }
        //randomly add new requests
        //give 1/5 chance of a new request being made
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1, 5);
        if(dis(gen) == 1) {
            Request req = generateRequests();
            addRequestToBalancer(balancers, req);
        }
        clock_cycle++;     
    }
}

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
    uniform_int_distribution<> dis(5, 50);
    Request req = Request(generateIP(), generateIP(), dis(gen));
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

void addRequestToBalancer(vector<LoadBalancer>& balancers, Request req) {
    if(balancers.empty()) return;
    LoadBalancer* minBalancer = &balancers[0];
    int minWaitTime = minBalancer->getWaitTime();
    for(LoadBalancer balancer : balancers) {
        if(balancer.getWaitTime() < minWaitTime) {
            minBalancer = &balancer;
            minWaitTime = balancer.getWaitTime();
        }
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
        //create load balancers
        vector<LoadBalancer> balancers;
        int totalLoad = numServers * 100;
        int numBalancers = ceil(totalLoad / MAX_LOAD_PER_BALANCER);
        for(int i = 0; i < numBalancers; i++) {
            LoadBalancer balancer = LoadBalancer();
            balancers.push_back(balancer);
        }
        //add servers to balancers;
        for(int i = 0; i < numServers; i++) {
            Webserver* server = new Webserver();
            balancers[i % numBalancers].addServer(server);
        }
        //create full qeuue of requests
        vector<Request> requests = generateRequests(totalLoad);
        //add requests to balancers
        for(Request req : requests) {
            addRequestToBalancer(balancers, req);
        }
        //simulate load balancing
        simulate(time, balancers);
    }
}