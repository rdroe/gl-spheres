#ifndef file_util_h
  #define file_util_h

#include <fstream>

  extern "C" {

  class file_util {
    public:
    static std::string read(std::string fname) {
      std::string output_txt = "";
      std::ifstream ifs;
      ifs.open (fname, std::ifstream::in);
      char c = ifs.get();
      while (ifs.good()) {
        output_txt = output_txt + c;
        c = ifs.get();
      }
      ifs.close();
      return output_txt;
    }
  };
}

#endif