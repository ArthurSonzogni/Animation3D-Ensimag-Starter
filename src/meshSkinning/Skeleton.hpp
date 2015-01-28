/**
 * Skeleton.hpp
 * Contributors:
 *      * Arthur Sonzogni (author)
 * Licence:
 *      * Public Domain
 */

#ifndef SKELETON_MV97YKB4
#define SKELETON_MV97YKB4

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <sstream>
#include "PointWeight.hpp"

class Skeleton;
class SkeletonPart;


class SkeletonPart
{
    friend class Skeleton;

    public:
        

    protected:
        ~SkeletonPart();

        // data parsing helper function
        void addChannel(const std::string& name);
        void addFrameData(std::stringstream& data);      // TODO implement me (step 2)
        void readSkeleton(std::stringstream& stream); // TODO implement me (step 1)

        // skeleton data processing
        void getWireframe(int frame, std::vector<glm::vec3>& output, glm::mat4 transformation, const glm::vec3& reference);
        void getTransformation(int frame, std::vector<glm::mat4>& output, glm::mat4 transformation, glm::mat4 rest);
        void getWeight(PointWeight& output, const glm::vec3& p, int& i, glm::mat4 transformation); // TODO implement me (step 3)

        // utils
        glm::mat4 applyTransformation(int frame, glm::mat4 transformation);
        glm::mat4 applyRestTransformation(glm::mat4 transformation);

        enum Channel {   TX,TY,TZ,   RX,RY,RZ   };
        struct MotionData
        {
            Channel channel;
            std::vector<float> data;
        };

        // data // TODO fill this data (step 1)
        std::string name;
        glm::vec3 offset;
        std::vector<MotionData> motionData;
        std::vector<SkeletonPart*> children;

};

class Skeleton : public SkeletonPart
{
    public:

        Skeleton(const std::string& filename);
        void readHierarchy(std::stringstream& stream);
        void readMotion(std::stringstream& stream);

        void getWireframe(int frame, std::vector<glm::vec3>& output);
        void getTransformation(int frame, std::vector<glm::mat4>& output);
        void getOffsetTransformation(std::vector<glm::mat4>& output);
        void getWeight(PointWeight& output, glm::mat4 transformation);
        void getWeight(PointWeight& output, const glm::vec3& p);

        int getFrameMirror(float time);
        int getFrame() {return frame;}
        float getFrameTime() {return frameTime;}

    private:


        // data
        int frame;
        float frameTime;
};




#endif /* end of include guard: SKELETON_MV97YKB4 */
