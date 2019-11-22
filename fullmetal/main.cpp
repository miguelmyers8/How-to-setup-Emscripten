//
//  main.cpp
//  fullmetal
//
//  Created by miguel myers on 5/6/19.
//  Copyright © 2019 miguel myers. All rights reserved.
//

#include <iostream>
#include "Tensor.hpp"
#include "utils.cpp"

#include <xtensor/xrandom.hpp>
#include <xtensor-blas/xlinalg.hpp>
#include <tuple>
#include <string>
#include <optional>
#include <cstddef>
#include <vector>
#include <xtensor/xarray.hpp>
#include <xtensor/xadapt.hpp>
#include <xtensor/xio.hpp>


auto aa = xt::random::randn<double> ({2, 2});
auto bb = xt::random::randn<double> ({2, 2});

xt::xarray<double> k = {{ 11, 12, 13 }};
xt::xarray<double> l = {{  1,  1,  1 }};
xt::xarray<double> ll = {6};
xt::xarray<double> f = {{ 11, 12, 16 }};
auto v = k+l;


int main(int argc, const char * argv[]) {
    std::vector<double> v = {1., 2., 3., 4., 5., 6. };
    std::vector<std::size_t> shape = { 1 , 3 };
    auto a1 = xt::adapt(v, shape);

    xt::xarray<double> a2 = {{ 1., 2., 3.},
                             { 4., 5., 6.}};
    xt::svector<size_t> shape_ = a1.shape();
    
    
    std::cout << a1<<std::endl;

        return 0;
}
