#include "CgLog.h"
#include <Cg/cg.h>
#include <iostream>

void CgLog::Log(string situation, CGcontext context)
{
    CGerror error;
    const char *string = cgGetLastErrorString(&error);

    if (error != CG_NO_ERROR)
    {
        cout<< situation.c_str()<< " " << string<< endl;
        if (error == CG_COMPILER_ERROR)
        {
            cout<< cgGetLastListing(context)<< endl; 
        }
        exit(1);
    }
}