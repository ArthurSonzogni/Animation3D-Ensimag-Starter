#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


// structure that holds the four best weight
struct PointWeight
{
    glm::ivec4 index;
    glm::dvec4 weight;

    PointWeight():
        index(-1,-1,-1,-1),
        weight(0.0,0.0,0.0,0.0)
    {}

    void insert(double value, int ind)
    {
        for(int i = 0; i<4; ++i)
        {
            if (weight[i]<value)
            {
                for(int j = 3; j>i; --j)
                {
                    weight[j] = weight[j-1];
                    index[j] = index[j-1];
                }
                weight[i] = value;
                index[i] = ind;
                break;
            }
        }
    }
};
