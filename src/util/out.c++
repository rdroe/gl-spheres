#include "out.h++"
#include <iostream>
#include <vector>
#include <string>


extern "C" {

  void out::wrt (std::string a, std::string b) {
    std::cout << a << ": " << b << std::endl;
  }

  void out::wrt (std::string a, int b) {
    std::cout << a << ": " << b << std::endl;
  }

  void out::wrt (std::string a, float b) {
    std::cout << a << ": " << b << std::endl;
  }

  void out::writeThree (std::vector<float> ns, std::string nm) {
      std::cout << nm << ":"
          << ns[0] << ", "
          << ns[1] << ", "
          << ns[2] << ", \n";

  }


  void out::writeThree (std::vector<int> ns, std::string nm) {
      std::cout << nm << ":"
          << ns[0] << ", "
          << ns[1] << ", "
          << ns[2] << ", \n";
  }
}