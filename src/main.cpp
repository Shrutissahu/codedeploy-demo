#include <iostream>
#include "Factorial.h"

int main(int argc, char* argv[])
{
    int n = atoi(argv[1]);
    auto factorial = Factorial::GetFactorial(n);

    std::cout << "Here is the Factorial for the number " << n << " = " << factorial << std::endl;    
    return 0;
}
