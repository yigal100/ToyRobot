#include "boost/ut.hpp"

using namespace boost::ut;

int main(int argc, char** argv)
{
    std::vector<std::string> arguments;
    arguments.reserve(argc);
    for (int i = 0; i < argc; ++i)
    {
        arguments.emplace_back(argv[i]);
    }

    bool isDryRun = false;
    for (auto& arg : arguments)
    {
        if (arg == "--list")
        {
            isDryRun = true;
        }
    }

    cfg<override> = { .filter = "",
                   .colors = colors{},
                   .dry_run = isDryRun };

}


