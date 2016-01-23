#ifndef mesh_h__
#define mesh_h__
class Mesh
{
private:
    int vertexCount;
public:
    Mesh() : vertexCount(0)
    {
    }

    inline int GetVertexCount(){return vertexCount;}

};
#endif