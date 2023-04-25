#pragma once

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

#include "SecondaryFunction.h"

class LogMessage
{
public:
    //Type type() const;
    const std::string& message() const;
};