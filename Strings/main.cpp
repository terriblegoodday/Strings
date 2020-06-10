//
//  main.cpp
//  Strings
//
//  Created by Eduard Dzhumagaliev on 5/20/20.
//  Copyright © 2020 Eduard Dzhumagaliev. All rights reserved.
//

#include <iostream>
#include "FLString.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    FLString flstring = FLString(5);
    flstring = "abcdef";
    cout << flstring << endl;
    
    findAndReplace(flstring, "abc", "abcabc");
    cout << flstring << endl;
    
    return 0;
}
