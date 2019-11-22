#include "Tensor.hpp"
#include "testem.hpp"

#include <xtensor/xarray.hpp>
#include <emscripten/bind.h>
#include <emscripten/val.h>
#include <vector>


using namespace std;
using namespace emscripten;

template <typename T>
auto vecFromJSArrayr(const emscripten::val &v)
{
    const auto l = v["length"].as<unsigned>();
    xt::xtensor<T, 1> res = xt::empty<int>({l});
    emscripten::val memoryView{emscripten::typed_memory_view(l, res.data())};
    memoryView.call<void>("set", v);

    return res;
}

Tensor lerp(val j) {
    auto k = vecFromJSArrayr<int>(j);
    //std::vector<size_t> shape = k.shape();

   Tensor my(k);

    return my;
}


EMSCRIPTEN_BINDINGS(my_module) {
    emscripten::function("lerp", &lerp);
    emscripten::function("add_", &add_);

    class_<Tensor>("Tensor")
        .constructor<xt::xarray<double>>()
        .function("print_data", &Tensor::print_data)
        .function("rg",&Tensor::print_rg);


}

int main(int argc, char const *argv[]) {
  /* code */
  return 0;
}
