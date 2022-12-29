#include <iostream>
#include "Vector.h"



int main(int argc, const char* argv[]) {
    math::Vector v1{2, 6};
    math::Vector2<long> v2{4, 5};
    std::cout << "v1(" << v1.x << ", " << v1.y << "), v2(" << v2.x << ", " << v2.y << ")\n";

    ++v1;
    std::cout << "v1(" << v1.x << ", " << v1.y << ")\n";
    v1--;
    std::cout << "v1(" << v1.x << ", " << v1.y << ")\n";
    v1++;
    std::cout << "v1(" << v1.x << ", " << v1.y << ")\n";
    --v1;
    std::cout << "v1(" << v1.x << ", " << v1.y << ")\n";


    v1 += 2;
    std::cout << "v1(" << v1.x << ", " << v1.y << ")\n";
    v1 -= !v2;
    std::cout << "v1(" << v1.x << ", " << v1.y << ")\n";
    v1 *= -v2.yx;
    std::cout << "v1(" << v1.x << ", " << v1.y << ")\n";
    v1 /= +v2.yy;
    std::cout << "v1(" << v1.x << ", " << v1.y << ")\n";
    v1 %= ~v2.yy;
    std::cout << "v1(" << v1.x << ", " << v1.y << ")\n";


    v1.yx += 2;
    std::cout << "v1(" << v1.x << ", " << v1.y << ")\n";
    v1.yx -= v2;
    std::cout << "v1(" << v1.x << ", " << v1.y << ")\n";
    v1.yx *= v2.yx;
    std::cout << "v1(" << v1.x << ", " << v1.y << ")\n";
    v1.yx /= v2.yy;
    std::cout << "v1(" << v1.x << ", " << v1.y << ")\n";
    v1.yx %= v2.yy;
    std::cout << "v1(" << v1.x << ", " << v1.y << ")\n";


    v1 = 2;
    std::cout << "v1(" << v1.x << ", " << v1.y << ")\n";
    v1 = -v2;
    std::cout << "v1(" << v1.x << ", " << v1.y << ")\n";
    v1 = v2.yx;
    std::cout << "v1(" << v1.x << ", " << v1.y << ")\n";
    v1 = v2.yy;
    std::cout << "v1(" << v1.x << ", " << v1.y << ")\n";
    v1 = v2.yy;
    std::cout << "v1(" << v1.x << ", " << v1.y << ")\n";


    auto v3 = v1.xy + 2 - v2.yx * v1 / 2 % v2 - v1.xy + v2.yx;
    std::cout << "v3(" << v3.x << ", " << v3.y << ")\n";


    bool ret = v1 == v1;
    std::cout << ret;



    return 0;
}