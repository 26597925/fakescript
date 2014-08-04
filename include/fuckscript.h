#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "variant.h"

namespace fscript
{

// �����
enum efkerror
{
    efk_ok,
};

efkerror fkerror();

// �����ļ�
bool fkparse(const char * filename);

// �����ļ�
Variant fkcall(const char * func, Variant * arg, int argnum);

}

