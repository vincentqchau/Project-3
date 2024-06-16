#include <Webserver.h>

using namespace std;

Webserver::Webserver() {
    curr_req = NULL;
    curr_time = 0;
    is_busy = false;
}

void Webserver::set_curr_req(Request* req) {
    curr_req = req;
    curr_time = 0;
}

Request* Webserver::get_curr_req() {
    return curr_req;
}

bool Webserver::process_req() {
    curr_time++;
    return curr_time == curr_req->get_process_time();
}

void Webserver::set_is_busy(bool busy) {
    is_busy = busy;
}

bool Webserver::get_is_busy() {
    return is_busy;
}