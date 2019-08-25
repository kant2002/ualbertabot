#include "../SparCraft.h"
#include "Benchmarks.h"
#include <iostream>

using namespace SparCraft;

int main(int argc, char* argv[])
{
    SparCraft::init();
	AIParameters parameters;
	parameters.parseFile("SparCraft_Config.txt");

    printf("Running Benchmarks\n");
    Benchmarks::DoBenchmarks(parameters, "SparCraft_Config.txt");

    return 0;
}