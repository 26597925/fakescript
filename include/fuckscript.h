#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "variant.h"

namespace fscript
{

// �����
enum fkerror
{
    fk_ok,
};

fkerror fkerror();

// �����ļ�
bool fkparse(const char * filename);

// �����ļ�
Variant fkcall(const char * func, Variant * arg, int argnum);

}

