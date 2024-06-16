#include <Request.h>

class Webserver {
    private:
        Request* curr_req;
        int curr_time;
        bool is_busy;

    public:
        Webserver();
        void set_curr_req(Request* req);
        Request* get_curr_req();
        bool process_req();
        void set_is_busy(bool busy);
        bool get_is_busy();
};