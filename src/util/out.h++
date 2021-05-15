#ifndef out_h
    #define out_h

#include <vector>
#include <string>

extern "C" {
  struct out {
    static void wrt(std::string, std::string);
    static void wrt(std::string, int);
    static void wrt(std::string, float);
    static void writeThree(std::vector<float>, std::string);
    static void writeThree(std::vector<int>, std::string);
  };
}

#endif