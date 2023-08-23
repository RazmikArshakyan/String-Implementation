#include <iostream>
#include "String.h"

int main() {
    String str1;
    std::cout << str1.size() << std::endl;
    String str2("Magnus Carlsen Best Chess player");
    String str3("Dubov");

    std::cout << str2 << std::endl;
    std::cout << str3 << std::endl;

    String str4(5,'Z');
    std::cout << str4 << std::endl;
    String str5(17,'M');
    std::cout << str5 << std::endl;

    String str6 = str5;
    std::cout << str6 << std::endl;
    str6 = "Mikael";
    std::cout << str6 << std::endl;
    std::cout << str5 << std::endl;
    
    String str7 ({'1','4','7','9'});
    std::cout << str7 << std::endl;
    String str8 ({'1','1','2','3','5','8','8','8','6','1','2'
    ,'8','9','1','9','6','3','9','8','7','2','6','3','2'});
    std::cout << str8 << std::endl;

    String str9("Johnny");
    String str10;
    str10 = str9;
    std::cout << str10 << std::endl;
    str10 = "Alen";
    std::cout << str10 << std::endl;
    std::cout << str9 << std::endl;
    
    std::cout << str10[2] << std::endl;
    std::cout << str2[15] << std::endl;
    
    std::cout << str2.capacity() << std::endl;
    
    String str11("asasasasaaasaas");
    str11.push_back('6');
    std::cout << str11 << std::endl;

    str11.push_back('7');
    



    return 0;
}