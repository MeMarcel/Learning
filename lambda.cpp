
#include<algorithm>
#include <iostream>
#include <vector>

void test(int& a){

std::cout << a++;

}
int main()
{
    std::vector<int> liste;
    liste.push_back(1);
    liste.push_back(2);
    std::for_each(liste.begin(),liste.end(),[](int a)
    {
        std::cout << a*2 << std::endl;
    });
    int b = 2;
    test( b);
    int* test = nullptr;
    if(test == nullptr) std::cout << "test";
    std::cout << b;
}

