#include <iostream>
#include "CMyArray.h"

int main() {
    CMyArray<std::string> sArr;
    sArr.PushBack("Hello");
    sArr.PushBack("World");
    std::cout << "String array: ";
    for (const auto& s : sArr) std::cout << s << ' ';
    std::cout << "\n";

    CMyArray<float> fArr;
    fArr.PushBack(3.14f);
    fArr.PushBack(2.71f);
    std::cout << "Float array: ";
    for (float f : fArr) std::cout << f << ' ';
    std::cout << "\n";

    return 0;
}
