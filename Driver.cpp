#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argc, char* argv[]) {
    int opt;
    int servers = 0, time = 0;
    while((opt = getopt(argc, argv, "s:t:")) != -1) {
        switch(opt) {
            case 's':
                servers = atoi(optarg);
                break;
            case 't':
                time = atoi(optarg);
                break;
        }
    }
    if(servers == 0 || time == 0) {
        cout << "Usage: ./Driver -s <servers> -t <time>" << endl;
    } else {
        //create webservers
        
        //create load balancers
    }
}