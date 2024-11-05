# 仿GLSL中swizzle操作的向量库

## 实现细节

- 使用“deducing this”实现一个公共基类Base，Base中实现了Vector和Swizzle共有的方法（赋值运算符、一元运算符、一元数学函数、逐元素cast）
- 使用CRT实现Vector的基类VectorBase，用以实现各维度Vector共有的构造函数和索引运算符
- 使用匿名union实现类似C#的属性
- 限制含有重复元素的Swizzle对象为只读对象，通过删除其可变的成员函数（赋值运算符、前置/后置递增递减运算符）实现

## 使用到的C++特性 

- deducing this [需要C++23]
- using父类的构造函数和赋值函数
- 参数包展开
- 折叠表达式
- concept、requires约束
- CTAD
- delete函数
- 匿名union

## demo

```cpp
#include <cassert>

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


    Vector v1{1, 2, 3, 4};
    assert(v1.x == 1 && v1.y == 2 && v1.z == 3 && v1.w == 4);
    Vector v2(0, v1.xyz);
    assert((Vector(2, 3, 4, 5) > Vector(2, 3, 4, 5) - v1.x).all());
    assert(!(Vector(0, 3, 4, 5) + v1.xxxx == v1).all());
    assert((Vector(0, 0, 4, 5) + v1.yyyy == v1).any());
    v1 += v2.y;
    assert((v1 ==Vector(2, 3, 4, 5)).all());
    v1 -= !v2;
    assert((v1 == Vector(1, 3, 4, 5)).all());
    v1.xyz += v2.www;
    assert((v1 ==Vector(4, 6, 7, 5)).all());


    return 0;
}

```
