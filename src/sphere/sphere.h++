#ifndef sphere_h
    #define sphere_h

#include <vector>

#include <SDL_opengles2.h>

#include <emscripten.h>

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../normals/normals.h++"

extern "C" {

    class sphere {

      std::vector<float> vecNorms;

      GLint aVertexPosition;
      GLint aVertexNormal;

      static glm::mat4 createBaseMatrix(float x, float y, float z);
      static void bufferFloatData (const std::vector<float> &, GLuint &, GLint &, bool doGenBuffers);
      static int bufferElementData( GLuint &, bool);

      int initSphereBuffers(std::vector<GLuint> &, std::vector<GLuint> &, std::vector<GLuint> &);

      GLuint vertLoc;
      GLuint normLoc;
      GLuint indLoc;
      glm::mat4 mv = sphere::createBaseMatrix(-1, 0, -1.5);
      
      void setVertLoc(GLuint vl) {
        vertLoc = vl;
      };

      void setNormLoc(GLuint vl) {
        normLoc = vl;
      };

      void setIndLoc(GLuint vl) {
        indLoc = vl;
      };
      
      GLfloat * getMvPtr();      
      
      
    public:

      const static std::vector<float> vecVerts;
      const static std::vector<int> vecInds;
  
      void move(glm::vec3 translation) {
	// sphere at index 0 is always the one to move, right now.
	this->mv = glm::translate(this->mv, translation);

      }
      
      sphere(
        GLint aVertexPosition,
        GLint aVertexNormal
        ) :

          aVertexPosition(aVertexPosition), 
          aVertexNormal(aVertexNormal) 
        {
          vecNorms = normals::calculateNormals(vecVerts, vecInds);
        }
        void initToBuffers(std::vector<GLuint> & v, std::vector<GLuint> &n, std::vector<GLuint> &i) ;



        void draw(GLuint, int);
    };

}
#endif
