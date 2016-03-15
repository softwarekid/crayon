#include "CgProgram.h"


CgProgram::CgProgram(CGcontext content, CGprofile profile, std::string vertFileName, std::string vertEntry, std::string fragFilename, std::string fragEntry)
{
    _vertShader = new CgShader(content, profile, vertFileName, vertEntry);
    _fragShader = new CgShader(content, profile, fragFilename, fragEntry);
}

CgProgram::~CgProgram()
{
    // maybe I can use unique_ptr
    delete _vertShader;
    _vertShader = nullptr;
    delete _fragShader;
    _fragShader = nullptr;
}