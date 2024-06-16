#include <string>

class Request {
    private:
        std::string ip_in;
        std::string ip_out;
        int process_time;

    public:
        Request(std::string in, std::string out, int time);

        std::string get_ip_in();
        std::string get_ip_out();
        std::string get_process_time();
};