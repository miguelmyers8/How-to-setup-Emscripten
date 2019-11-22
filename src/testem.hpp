#include <iostream>
#include <stdio.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>
#include <vector>

#include "Tensor.hpp"
#include <xtensor/xrandom.hpp>
#include <xtensor/xarray.hpp>
#include <xtensor/xio.hpp>

//#include <xtensor-blas/xlinalg.hpp>
#include <boost/variant/variant.hpp>
#include <memory>
using namespace std;

Tensor add_(Tensor t1, Tensor t2){
    auto out = t1.data + t2.data;
    bool requires_grad = t1.requires_grad || t2.requires_grad;
    std::vector<Dependancies> depends_on = {};

    if(t1.requires_grad){

        auto add_grad_1 = [=] (xt::xarray<double> y) {
            xt::xarray<double> grad = y;
            xt::svector<size_t> shape = t1.shape;
            int ndims_added = y.dimension() - t1.data.dimension();

            for (int i = 0; i< ndims_added; ++i)
                 grad = xt::sum(grad, 0);

            for(std::size_t k = 0; k < shape.size(); ++k)
                if (shape[k] == 1)
                    grad = xt::sum(grad,(k+0),xt::keep_dims);

            return grad;
        };

        depends_on.push_back(Dependancies(t1,add_grad_1,"add.<add_grad_1>"));
    };

     if(t2.requires_grad){
         auto add_grad_2 = [=] (xt::xarray<double> y) {
             xt::xarray<double> grad = y;
             xt::svector<size_t> shape = t1.shape;
             int ndims_added = y.dimension() - t2.data.dimension();

             for (int i = 0; i< ndims_added; ++i)
                 grad = xt::sum(grad, 0);

             for(std::size_t i = 0; i < shape.size(); ++i)
                 if (shape[i] == 1)
                     grad = xt::sum(grad,(i+0),xt::keep_dims);

             return grad ;
        };
     depends_on.push_back(Dependancies(t2,add_grad_2,"add.<add_grad_2>"));
     };
    return Tensor(out,requires_grad,depends_on);
};
