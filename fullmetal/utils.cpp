//
//  utils.cpp
//  fullmetal
//
//  Created by miguel myers on 11/10/19.
//  Copyright © 2019 miguel myers. All rights reserved.
//

#include <stdio.h>

template<typename O, typename C>
auto type_convert(O orignal, C clone){
     typedef decltype(orignal) type;
     return type(clone,false);
}
