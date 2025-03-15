#pragma once

#include <vector>
#include <string>
#include <../third/glm/glm.hpp>

struct point3D
{
    float x, y, z;
    point3D(): x(0), y(0), z(0) {};
    point3D(float x_, float y_, float z_): x(x_), y(y_), z(z_) {};
};
struct boundingBox
{

    point3D minBox;
    point3D maxBox;
    
};
class objLoader
{
public:
    objLoader(std::string filename);
    std::vector<glm::vec3> getVertexCoordinates();
    std::vector<std::vector<int> > getFaceIndices();
    void evaulateBoundingBox();
    boundingBox getBoundingBox();
    


private:
    size_t numVertices;
    size_t numFaces;
    boundingBox BBox; //get the bounding box for the object

    std::vector<glm::vec3> vertexCoordinates;
    std::vector<std::vector<int> > faceIndices;


};