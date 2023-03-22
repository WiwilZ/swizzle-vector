# 仿GLSL中swizzle操作的向量库

## 技术路线

- 通过CRTP实现一个Vector和Swizzle的基类Base，用以实现共有的方法
- 通过匿名union和特制的swizzle类实现类似C#的属性
- 限制含有重复元素的swizzle组合为const
- 通过CRT实现Vector的基类VectorBase，用以实现各维度Vector共有的构造函数

## Vector和Swizzle共有的方法

- T&& operator[](std::size_t)
- Vector operator{+/-/\~/!}()、operator-()、operator~()、operator!()
- Swizzle/Vector& operaotr=(Scalar/Swizzle/Vector)
- void operator{+=/-=/\*=//=/%=/&=/|=/^=/<<=/>>=}(Scalar/Swizzle/Vector)
- Swizzle/Vector operaotr{+/-/\*///%/&/|/^/<</>>/&&/||/</<=/>/>=/==/!=}(Scalar/Swizzle/Vector)
- Swizzle/Vector operaotr{+/-/\*///%/&/|/^/<</>>/&&/||/</<=/>/>=/==/!=}(Scalar, Swizzle/Vector)
- bool all/any()
- bool equals/not_equals(Swizzle/Vector)

## 编译器骂人系列（用到的C++特性）[需要C++20!!!]

- CRTP
- using基类的构造函数和赋值函数
- 变长参数包展开
- 折叠表达式
- concept、requires约束
- CTAD

## demo

```cpp
#include <assert.h>
#include "Vector.h"

int main(int argc, const char* argv[]) {
    Vector v1{1, 2, 3, 4};
    assert(v1.x == 1 && v1.y == 2 && v1.z == 3 && v1.w == 4);

    Vector a(v1);
    Vector b(v1.xx);
    Vector c(1, Vector(0, 0), 1);
    Vector d(1, 0, c.xy);

    Vector v2(0, v1.xyz);


    assert((Vector(2, 3, 4, 5) > Vector(2, 3, 4, 5) - v1.x).all());
    assert(!(Vector(0, 3, 4, 5) + v1.xxxx == v1).all());
    assert((Vector(0, 0, 4, 5) + v1.yyyy == v1).any());

    v1 += v2.y;
    assert(v1.equals(Vector(2, 3, 4, 5)));
    v1 -= !v2;
    assert(v1.equals(Vector(1, 3, 4, 5)));


    v1.xyz += v2.www;
    assert(v1.equals(Vector(4, 6, 7, 5)));


    return 0;
}
```
