#include "normals.h++"
#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include <math.h>

std::vector<float> normals::calculateNormals(const std::vector<float> vs, const std::vector<int> ind) {  // NOLINT misc-unused-parameters
    std::vector<float> ns;

    ns.resize(vs.size() + 3);

    for (int i = 0; i < vs.size(); i += 3) {
      ns[i + x] = 0.0;
      ns[i + y] = 0.0;
      ns[i + z] = 0.0;
    }

    for (int i = 0; i < ind.size(); i += 3) {
      std::vector<float> v1(3);
      std::vector<float> v2(3);
      std::vector<float> v3(3);
      std::vector<float> normal(3);

      try {
        v1[x] =
          vs[3 * ind[i + 2] + x]
          - vs[3 * ind[i + 1] + x];
        } catch (std::exception err) {
          throw err;
        }
        v1[y] = vs[3 * ind[i + 2] + y] - vs[3 * ind[i + 1] + y];
        v1[z] = vs[3 * ind[i + 2] + z] - vs[3 * ind[i + 1] + z];

        v2[x] = vs[3 * ind[i] + x] - vs[3 * ind[i + 1] + x];
        v2[y] = vs[3 * ind[i] + y] - vs[3 * ind[i + 1] + y];
        v2[z] = vs[3 * ind[i] + z] - vs[3 * ind[i + 1] + z];


        // Cross product by Sarrus Rule
        normal[x] = v1[y] * v2[z] - v1[z] * v2[y];
        normal[y] = v1[z] * v2[x] - v1[x] * v2[z];
        normal[z] = v1[x] * v2[y] - v1[y] * v2[x];

        // Update the normals of that triangle: sum of vectors
        for (int j = 0; j < 3; j++) {
          ns[3 * ind[i + j] + x] = ns[3 * ind[i + j] + x] + normal[x];
          ns[3 * ind[i + j] + y] = ns[3 * ind[i + j] + y] + normal[y];
          ns[3 * ind[i + j] + z] = ns[3 * ind[i + j] + z] + normal[z];
        }
    }
    for (int i = 0; i < vs.size(); i += 3) {
      // With an offset of 3 in the array (due to x, y, z contiguous values)
      std::vector<float> nn(ns.size() + 3);
      nn[x] = ns[i + x];
      nn[y] = ns[i + y];
      nn[z] = ns[i + z];


      float len = sqrt((nn[x] * nn[x]) + (nn[y] * nn[y]) + (nn[z] * nn[z]));

      if (len == 0) len = 1.0;
      nn[x] = nn[x] / len;
      nn[y] = nn[y] / len;
      nn[z] = nn[z] / len;
      ns[i + x] = nn[x];
      ns[i + y] = nn[y];
      ns[i + z] = nn[z];
    }
    return ns;
  }
