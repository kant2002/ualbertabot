#include "../SparCraft.h"
#include "../torch/TorchTools.h"

using namespace SparCraft;

int main(int argc, char *argv[])
{
    SparCraft::init();

    try
    {
		AIParameters aiParameters;
        if (argc == 2)
        {
			aiParameters.parseFile(argv[1]);
        }
        else
        {
			aiParameters.parseFile("SparCraft_Config.txt");
        }

        std::string requestType;
        std::cin >> requestType;

        if (requestType == "Move")
        {
            TorchTools::PrintMoveFromFrameStream(aiParameters, std::cin);
        }
        else if (requestType == "Value")
        {
            TorchTools::PrintStateValueFromFrameStream(aiParameters, std::cin);
        }
    }
    catch (SparCraftException e)
    {

    }
    
    
    return 0;
}
