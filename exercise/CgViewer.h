#ifndef cg_viewer_h__
#define cg_viewer_h__
#include "GlutWrapper.h"
class CgViewer : public GlutWrapper
{
private:
    void _Draw() override;

public:
    ~CgViewer()
    {
    }
};



#endif
