#include <Request.h>

using namespace std;

Request::Request(string in, string out, int time) {
    ip_in = in;
    ip_out = out;
    process_time = time;
}

string Request::get_ip_in() {
    return ip_in;
}

string Request::get_ip_out() {
    return ip_out;
}

int Request::get_process_time() {
    return process_time;
}