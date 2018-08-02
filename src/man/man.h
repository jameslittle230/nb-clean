#pragma once

#include <sys/file.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <errno.h>
#include <unistd.h>
#include <string.h>

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <vector>

namespace man {

class Man
{
public:
    Man();
    virtual ~Man();

private:
};

}
