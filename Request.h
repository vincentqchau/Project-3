#ifndef REQUEST_H
#define REQUEST_H
#include <string>

class Request {
    private:
        std::string ip_in;
        std::string ip_out;
        int process_time;

    public:
        Request();
        Request(std::string in, std::string out, int time);

        std::string get_ip_in();
        std::string get_ip_out();
        int get_process_time();
        void process();
        void print();
};

#endif