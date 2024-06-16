#include "Webserver.h"
#include <iostream>

using namespace std;

Webserver::Webserver() {
    curr_req = Request();
    is_busy = false;
}

void Webserver::set_curr_req(Request req) {
    curr_req = req;
}

Request Webserver::get_curr_req() {
    return curr_req;
}

void Webserver::process_req() {
    curr_req.process();
}

bool Webserver::request_is_done() {
    return curr_req.get_process_time() == 0;
}

void Webserver::set_is_busy(bool busy) {
    is_busy = busy;
}

bool Webserver::get_is_busy() {
    return is_busy;
}