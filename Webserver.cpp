#include <Webserver.h>

using namespace std;

Webserver::Webserver() {
    curr_req = NULL;
    curr_time = 0;
}

void Webserver::set_curr_req(Request* req) {
    curr_req = req;
}

Request* Webserver::get_curr_req() {
    return curr_req;
}

bool Webserver::process_req() {
    curr_time++;
    return curr_time == curr_req->get_process_time();
}