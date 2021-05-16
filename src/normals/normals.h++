#ifndef normals_h
#define normals_h

#include <vector>

class normals {
  static const int x = 0;
  static const int y = 1;
  static const int z = 2;

public:
  static std::vector<float> calculateNormals(std::vector<float>,
                                             std::vector<int>);
};

#endif
