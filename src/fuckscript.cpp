#include "fuckscript.h"

namespace fscript
{

fkerror g_fkerror;

fkerror fkerror()
{
    return g_fkerror;
}

// �����ļ�
bool fkparse(const char * filename)
{
    return true;
}

// �����ļ�
Variant fkcall(const char * func, Variant * arg, int argnum)
{
    return Variant();
}

}

