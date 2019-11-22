//
//  Tensor.cpp
//  fullmetal
//
//  Created by miguel myers on 5/15/19.
//  Copyright © 2019 miguel myers. All rights reserved.
//

#include "Tensor.hpp"
#include <iostream>
#include <xtensor/xrandom.hpp>
#include <xtensor/xarray.hpp>
#include <xtensor/xio.hpp>

//#include <xtensor-blas/xlinalg.hpp>
#include <boost/variant/variant.hpp>
#include <memory>
using namespace std;

Tensor::Tensor(){};
Dependancies::Dependancies(){};

// tamplete for ensure_type
template<typename Base, typename T>
inline bool instanceof(const T){
    return is_base_of<Base, T>::value;
}

template<typename T>
auto ensure_type(T a){
    if (instanceof<Tensor>(a)){
        return a;
    }
    else{
        return Tensor(a);
    }

}


Tensor::Tensor(xt::xarray<double> a, bool b, std::vector<Dependancies> d){
    data = a;
    requires_grad = b;
    depend_on = d;
    shape = data.shape();
    grad = nullptr;
    if (this->requires_grad){this->zero_grad();};

};
Tensor::~Tensor(){};



Dependancies::Dependancies(Tensor a, std::function<xt::xarray<double>( xt::xarray<double> )> b, string c){
    tenor = a;
    grad_fn = b;
    name = c;
};
Dependancies::~Dependancies(){};

void Tensor::print_rg(){
  std::cout<<this->requires_grad<<std::endl;

  for (auto i : this->depend_on)
        std::cout << i.tenor.data << std::endl;

};
void Tensor::zero_grad(){
    auto i = full_like(this->data, 0.);
    shared_ptr<Tensor> k = make_shared<Tensor>(i);
    this->grad = k;
};

void Tensor::print_data(){
  std::cout<<this->data<<std::endl;
};
// add
    Tensor operator+(const Tensor & a, const Tensor& b){
        //cout<<ensure_type(a)<<endl;
        return add(a,b);
    };

    Tensor operator+(const int & a, const Tensor& b){
       Tensor _a = Tensor(a);
        return add(_a,b);
    };

    Tensor operator+(const Tensor & a, const int& b){
        Tensor _b = Tensor(b);
        return add(a,_b);
    };

    Tensor add(Tensor t1, Tensor t2){
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
