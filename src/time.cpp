#include "time.hpp"


string now () {
    auto now = std::chrono::system_clock::now();
       std::time_t time = std::chrono::system_clock::to_time_t(now);

       char mbstr[100];
       if (std::strftime(mbstr, sizeof(mbstr), "[%H:%M:%S] ", std::localtime(&time)))
       {
//          std::cout << mbstr;
           return mbstr;
       }
}
