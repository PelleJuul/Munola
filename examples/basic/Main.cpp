#include <iostream>
#include <Munola.h>

int main(int argv, char **argc)
{
    auto text = "C +E ++G function(arg1, arg2, arg3)";
    auto munola = parseMunola(text);
    
    for (auto m : munola)
    {
        std::cout << m.to_string() << std::endl;
    }

    return 0;
}