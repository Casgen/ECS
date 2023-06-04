#pragma once
#include "Program.h"

/**
 * Since Compute shaders are completely separated from the pipeline, a separate program has to be created.
 * Therefore compute shaders are considered as a standalone program.
 */
class ComputeProgram : public Program
{
public:
    ComputeProgram(const std::string& shaderPath);
};
