#include "objLoader.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <stdexcept> // for std::invalid argument
#include <fstream> // to open the file
#include <sstream> // to tokenize the line
#include <../third/glm/glm.hpp>

objLoader::objLoader(std::string filename)
{

    // C++ way of opening a file
    std::ifstream file;

    // open the file
    file.open(filename);

    //check if the file is open and then process it
    if(file.is_open())
    {
        while(!file.eof())
        {
            //read each line
            std::string line;
            std::getline(file, line);

            //allow a stream to be tokenized and initialize to the line
            std::istringstream iss(line);

            //read the vertex indices
            if(!line.compare(0, 2, "v ")) // if matches line.compare() returns 0
            {
                char c1;
                double v1, v2, v3;
                iss >> c1 >> v1 >> v2 >> v3;
                
                glm::vec3 coords(v1, v2, v3);
                vertexCoordinates.push_back(coords);
            }
            
            //read the face values
            else if(!line.compare(0, 2, "f "))
            {
                //read vertex indices for each face
                char trash;
                int trash1, trash2, trash3, trash4, trash5, trash6, idx1, idx2, idx3;
                iss >> trash >> idx1 >> trash1 >> trash2 >> idx2 >> trash3 >> trash4 >> idx3 >> trash5 >> trash6; 
                //std::cout << idx1 <<idx2 <<idx3<<std::endl;
                std::vector<int> vertices;
                vertices.push_back(idx1--);
                vertices.push_back(idx2--);
                vertices.push_back(idx3--);
            

                faceIndices.push_back(vertices);

            }
        }
    }
    else
    {
        throw std::invalid_argument("No file provided");
    }

    size_t numVertices = vertexCoordinates.size();
    size_t numFaces = faceIndices.size();

    





};

std::vector<glm::vec3> objLoader::getVertexCoordinates()
{
    return vertexCoordinates;
}

std::vector<std::vector<int> > objLoader::getFaceIndices()
{
    return faceIndices;
}

void objLoader::evaulateBoundingBox()
{
    float xMax = 0, xMin = 0, yMax = 0, yMin = 0, zMax = 0, zMin = 0;
    for(unsigned int i = 0; i<vertexCoordinates.size(); i++)
    {
        glm::vec3 coords = vertexCoordinates[i];
        xMax = std::max(coords.x, xMax) > xMax ? coords.x : xMax;
        xMin = std::min(coords.x, xMin) < xMin ? coords.x : xMin;

        yMax = std::max(coords.y, yMax) > yMax ? coords.y : yMax;
        yMin = std::min(coords.y, yMin) < yMin ? coords.y : yMin;

        zMax = std::max(coords.z, zMax) > zMax ? coords.z : zMax;
        zMin = std::min(coords.z, zMin) < zMin ? coords.z : zMin;


    }
    point3D pMax(xMax, yMax, zMax);
    point3D pMin(xMin, yMin, zMin);
    BBox.minBox = pMin;
    BBox.maxBox = pMax;
}

boundingBox objLoader::getBoundingBox()
{
    return BBox;
}