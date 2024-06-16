#include "Request.h"
#include <iostream>

using namespace std;

Request::Request() : ip_in(""), ip_out(""), process_time(-1) {}

Request::Request(string in, string out, int time) : ip_in(in), ip_out(out), process_time(time) {}

string Request::get_ip_in() {
    return ip_in;
}

string Request::get_ip_out() {
    return ip_out;
}

int Request::get_process_time() {
    return process_time;
}

void Request::process() {
    process_time--;
}

void Request::print() {
    cout << "Rquest(" << ip_in << ", " << ip_out << ", " << process_time << ")" << endl;
}