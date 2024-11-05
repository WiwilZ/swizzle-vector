#include <iostream>

#include "Vector.h"


int main() {
    Vector<3, int> a(1);
    Vector b(1, 2, 3);
    Vector c(a);
    Vector d(b.cast<float>());
    double arr[]{1, 2};
    Vector e(arr);
    Vector f(a.xx);
    Vector g(a.zx, b.yy);

    std::cout << a << std::endl;

    a = {1, 2, 3};
    a = b;
    a = d;
    a = d.xyx;
    //    a = e;  // error
    //    a = f;  // error
    //    a = a.xx;  // error
    a.xy = b.yx;
    a.zyx = 1;
    //    a.xx = 1;  // error

    auto x = a + 1.;
    auto y = ~a;

    a += d;
    a &= b.xxy;

    std::cout << a.any() << " " << a.all() << std::endl;


    return 0;
}
