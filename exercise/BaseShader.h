#ifndef baseShader_h__
#define baseShader_h__

class BaseShader
{
protected:
    CGparameter lightPosition;
    CGparameter eyePosition;

public:
    virtual void UpdateParam();


    virtual ~BaseShader(){}
};
#endif