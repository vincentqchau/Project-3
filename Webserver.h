#ifndef WEBSERVER_H
#define WEBSERVER_H
#include "Request.h"

class Webserver {
    private:
        Request curr_req;
        bool is_busy;

    public:
        Webserver();
        void set_curr_req(Request req);
        Request get_curr_req();
        void process_req();
        void set_is_busy(bool busy);
        bool get_is_busy();
        bool request_is_done();
};
#endif