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
    std::cout << str11 << std::endl;
    str11.push_back('6');
    std::cout << str11 << std::endl;
    str11.push_back('5');
    std::cout << str11 << std::endl;
    str11.pop_back();
    std::cout << str11 << std::endl;
    str11.pop_back();
    std::cout << str11 << std::endl;
    str11.pop_back();
    std::cout << str11 << std::endl;

    String str12;
    std::cout << str12.empty() << std::endl;
       
    String str13("Hello world in dynamic memory");
    String str14(" Appending words as in dyn_mem");
    String str15(" Append  abc");
    String str16(" ab");

    str13 += str14;
    std::cout << str13 << std::endl;
    str13 += str15;
    std::cout << str13 << std::endl; 
    str15 += str16;
    std::cout << str15 << std::endl;
    str15 += str16;
    std::cout << str15 << std::endl;
    str16 += str14;
    std::cout << str16 << std::endl;

    String str17;
    std::cin >> str17;
    std::cout << str17 << std::endl; 

    String str18 = "Hello Malmo 999999";
    std::cout << str18 << std::endl;
    str18 = "hi malmo";
    std::cout << str18 << std::endl;


    return 0;
}