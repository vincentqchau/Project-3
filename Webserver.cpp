#include "Webserver.h"
#include <iostream>

using namespace std;

Webserver::Webserver(int id) {
    req = Request();
    busy = false;
    serverId = id;
}

void Webserver::setRequest(Request req) {
    this->req = req;
}

Request Webserver::getRequest() {
    return req;
}

void Webserver::processRequest() {
    req.process();
}

bool Webserver::isRequestDone() {
    return req.get_process_time() == 0;
}

void Webserver::setIsBusy(bool busy) {
    this->busy = busy;
}

bool Webserver::isBusy() {
    return busy;
}

int Webserver::getServerId() {
    return serverId;
}