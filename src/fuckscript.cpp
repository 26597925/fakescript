#include "fuckscript.h"

namespace fscript
{

efkerror g_fkerror;

efkerror fkerror()
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

