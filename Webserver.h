#include <Request.h>

class Webserver {
    private:
        Request* curr_req;
        int curr_time;

    public:
        Webserver();
        void set_curr_req(Request* req);
        Request* get_curr_req();
        bool process_req();
};