#include <iostream>
#include <stdio.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>
#include <vector>


using namespace emscripten;


template <typename T>
std::vector<T> vecFromJSArrayr(const emscripten::val &v)
{
    std::vector<T> rv;

    const auto l = v["length"].as<unsigned>();
    rv.resize(l);

    emscripten::val memoryView{emscripten::typed_memory_view(l, rv.data())};
    memoryView.call<void>("set", v);

    return rv;
}




class MyClass {
public:
    MyClass(int x, std::string y)
        : x(x)
        , y(y)
    {}

    void incrementX() {
        ++x;
    }

    int getX() const { return x; }
    void setX(int x_) { x = x_; }

     std::string getStringFromInstance() const {
        return y;
    }

private:
    int x;
    std::string y;
};

MyClass lerp(float a, float b, float t, val j) {
    auto k = vecFromJSArrayr<int>(j);
    //std::vector<size_t> shape = k.shape();

    for (const auto i : k ){ // access by const reference
       std::cout << i << ' '<<std::endl;

   }

   MyClass my(1,"c++");

    return my;
}

EMSCRIPTEN_BINDINGS(my_module) {
    function("lerp", &lerp);

    class_<MyClass>("MyClass")
        .constructor<int, std::string>()
        .function("incrementX", &MyClass::incrementX)
        .property("x", &MyClass::getX, &MyClass::setX)
        .property("y", &MyClass::getStringFromInstance)
        ;
}
