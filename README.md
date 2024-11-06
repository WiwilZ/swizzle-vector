# 仿GLSL中swizzle操作的向量库

## 实现细节

- 实现一个只读公共基类Base，其中实现了Vector和Swizzle共有的const方法（一元运算符（递增递减运算符除外）、一元数学函数、逐元素cast、any、all）
- 实现一个可变基类MutableBase，其中实现了Vector和Swizzle共有的非const方法（赋值运算符、前置/后置递增递减运算符）
- 实现一个Vector的基类VectorBase，用以实现各维度Vector共有的构造函数和索引运算符
- 使用匿名union和匿名struct实现类似C#的属性
- 限制含有重复元素的Swizzle对象为只读对象，只继承自只读公共基类Base，删除其赋值运算符

## 使用到的C++特性 

- deducing this [需要C++23]
- using父类的构造函数和赋值函数
- 参数包展开
- 折叠表达式
- concept、requires约束
- CTAD
- delete函数
- 匿名union和匿名struct

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
    int arr[]{1, 2};
    Vector e(arr);
    Vector f(a.xx);
    Vector g(1, e);
    Vector h(a.zx, b.yy);

    std::cout << b << std::endl;
    std::cout << b.zyx << std::endl;

    a = d;
    a = d.zyx;
    a.xyz = d.zyx;
    a.xyz = d.zyx;
    //    a = e;   // error
    //    a = e.xy;   // error
    //    a.xyz = e;   // error
    //    a.xyz = e.xy;   // error
    a.zy = e;
    a.zy = e.xy;
    a.zyx = 1;
    a.xy = d.x;
    //    a.xyx = 1;    // error

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
    assert((v1 == Vector(2, 3, 4, 5)).all());
    v1 -= !v2;
    assert((v1 == Vector(1, 3, 4, 5)).all());
    v1.xyz += v2.www;
    assert((v1 == Vector(4, 6, 7, 5)).all());


    return 0;
}
```
