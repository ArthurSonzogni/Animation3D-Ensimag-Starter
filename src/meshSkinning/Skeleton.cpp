/**
 * Skeleton.cpp
 * Contributors:
 *      * Arthur Sonzogni (author)
 * Licence:
 *      * Public Domain
 */

#include "Skeleton.hpp"
#include <stdexcept>
#include <iostream>

#define GLM_FORCE_RADIANS
#include <glm/gtx/matrix_operation.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define DEGTORAD 0.01745329251f

Skeleton::Skeleton(const std::string& filename)
{
    std::ifstream stream;
    stream.open(filename);

    if (not stream.is_open())
        throw std::invalid_argument(std::string("Can't open the file ") + filename);
   
    std::string line;
    std::stringstream sstream;
    while(std::getline(stream,line))
    {
        sstream << line << " ";
    }

    readHierarchy(sstream);
    readMotion(sstream);


    stream.close();
}

void Skeleton::readHierarchy(std::stringstream& stream)
{
    std::string hierarchy,root, name;
    stream >> hierarchy >> root >> name;

    bool valid = true;
    valid &= ( hierarchy == "HIERARCHY" );
    valid &= ( root == "ROOT" );
    valid &= bool(stream);

    if (not valid)
        throw std::runtime_error("Invalid BVH file");
    else
    {
        this->name = name;
        readSkeleton(stream);
    }
}
void Skeleton::readMotion(std::stringstream& stream)
{
    // this function assign frame and frameTime
    // it read also data with the function addFrameData
    // TODO 
    static bool isDisplayed = false;
    if (not isDisplayed)
    {
        isDisplayed = true;
        std::cerr << std::endl << "Please implement the line " << __LINE__ << " file : " << __FILE__ << std::endl << std::endl;
    }
}

void SkeletonPart::readSkeleton(std::stringstream& stream)
{
    // This function reads the BVH file between two curly braces
    std::string line;
    std::string word;
    while(stream >> word)
    {
        // TODO 
        static bool isDisplayed = false;
        if (not isDisplayed)
        {
            isDisplayed = true;
            std::cerr << std::endl << "Please implement the line " << __LINE__ << " file : " << __FILE__ << std::endl << std::endl;
        }

        if (word == "}")
        {
            return;
        }

    }
    throw std::runtime_error("Invalid BVH file");
}

void SkeletonPart::addChannel(const std::string& name)
{
         if ( name == "Xposition") { motionData.push_back(MotionData()); motionData.back().channel = TX; }
    else if ( name == "Yposition") { motionData.push_back(MotionData()); motionData.back().channel = TY; }
    else if ( name == "Zposition") { motionData.push_back(MotionData()); motionData.back().channel = TZ; }
    else if ( name == "Xrotation") { motionData.push_back(MotionData()); motionData.back().channel = RX; }
    else if ( name == "Yrotation") { motionData.push_back(MotionData()); motionData.back().channel = RY; }
    else if ( name == "Zrotation") { motionData.push_back(MotionData()); motionData.back().channel = RZ; }
    else throw std::invalid_argument("Invalid BVH file, cannot add the channel " + name);
}

void SkeletonPart::addFrameData(std::stringstream& data)
{
    // this function read data for every channel and addFrameData for every children
    static bool isDisplayed = false;
    if (not isDisplayed)
    {
        isDisplayed = true;
        std::cerr << std::endl << "Please implement the line " << __LINE__ << " file : " << __FILE__ << std::endl << std::endl;
    }
}


SkeletonPart::~SkeletonPart()
{
    for(auto child = children.begin(); child != children.end(); ++child)
    {
        delete *child;
    }
}



glm::mat4 SkeletonPart::applyTransformation(int frame, glm::mat4 transformation)
{
    // compute the new transformation
    glm::mat4 xRot(1.f),yRot(1.f),zRot(1.f);
    glm::vec3 tOffset(0.f);
    for(auto channel = motionData.begin(); channel != motionData.end(); ++channel)
    {
       //if (frame < channel -> data.size())
       switch(channel -> channel)
       {
           case TX : tOffset += channel -> data[frame] * glm::vec3(1.f,0.f,0.f); break;
           case TY : tOffset += channel -> data[frame] * glm::vec3(0.f,1.f,0.f); break;
           case TZ : tOffset += channel -> data[frame] * glm::vec3(0.f,0.f,1.f); break;
           case RX : xRot = glm::rotate(xRot, DEGTORAD * channel -> data[frame] , glm::vec3(1.f,0.f,0.f)); break;
           case RY : yRot = glm::rotate(yRot, DEGTORAD * channel -> data[frame] , glm::vec3(0.f,1.f,0.f)); break;
           case RZ : zRot = glm::rotate(zRot, DEGTORAD * channel -> data[frame] , glm::vec3(0.f,0.f,1.f)); break;
       }
    }

    transformation = transformation * glm::translate(glm::mat4(1.f),offset + tOffset);
    transformation = transformation * zRot * yRot * xRot;
    return transformation;
}

glm::mat4 SkeletonPart::applyRestTransformation(glm::mat4 transformation)
{
    return transformation * glm::translate(glm::mat4(1.f),offset);
}


void SkeletonPart::getWireframe(int frame, std::vector<glm::vec3>& output, glm::mat4 transformation, const glm::vec3& reference)
{
    transformation = applyTransformation(frame, transformation);
    glm::vec3 myPosition = glm::vec3( transformation * glm::vec4(0.f,0.f,0.f,1.f) );

    // add a line
    output.push_back(reference);
    output.push_back(myPosition);

    // add line on every children
    for(auto child = children.begin(); child != children.end(); ++child)
        (**child).getWireframe(frame,output,transformation,myPosition);
}

void Skeleton::getWireframe(int frame, std::vector<glm::vec3>& output)
{
    SkeletonPart::getWireframe(frame, output, glm::mat4(1.f), glm::vec3(0.f));
}

void SkeletonPart::getTransformation(int frame, std::vector<glm::mat4>& output, glm::mat4 transformation, glm::mat4 rest)
{
    transformation = applyTransformation(frame,transformation);
    rest = applyRestTransformation(rest);

    // TODO
    static bool isDisplayed = false;
    if (not isDisplayed)
    {
        isDisplayed = true;
        std::cerr << std::endl << "Please implement the line " << __LINE__ << " file : " << __FILE__ << std::endl << std::endl;
    }

    for(auto child = children.begin(); child != children.end(); ++child)
        (**child).getTransformation(frame,output,transformation,rest);
}

void Skeleton::getTransformation(int frame, std::vector<glm::mat4>& output)
{
    SkeletonPart::getTransformation(frame,output,glm::mat4(1.f),glm::mat4(1.0));
}

void SkeletonPart::getWeight(PointWeight& output, const glm::vec3& p, int& i, glm::mat4 transformation)
{
    // TODO
    static bool isDisplayed = false;
    if (not isDisplayed)
    {
        isDisplayed = true;
        std::cerr << std::endl << "Please implement the line " << __LINE__ << " file : " << __FILE__ << std::endl << std::endl;
    }
    float weight = 1.0;


    // TODO end
    output.insert(weight,i);
    
    ++i;
    for(auto child = children.begin(); child != children.end(); ++child)
        (**child).getWeight(output,p,i,transformation);
}

void Skeleton::getWeight(PointWeight& output, const glm::vec3& p)
{
    int i = 0;
    glm::mat4 transformation = applyRestTransformation(glm::mat4(1.f));

    for(auto child = children.begin(); child != children.end(); ++child)
        (**child).getWeight(output,p,i,transformation);
}

int Skeleton::getFrameMirror(float time)
{
    int frameMiroir = time / frameTime;
    frameMiroir = frameMiroir % ( 2 * frame );
    if (frameMiroir >= frame )
        frameMiroir = 2 * frame - frameMiroir - 1;
    return frameMiroir;
}

