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
    FLString flstring = FLString(3);
    flstring = "abcdef";
    cout << flstring << endl;
    
    FLString flstring2 = "abcdef";
    cout << flstring2 << endl;
    cout << (flstring == flstring2) << endl;
    cout << flstring.getLength() << " " << flstring2.getLength() << endl;
    
    cout << flstring.find("ef") << endl;
    cout << flstring.substr(4, 2) << endl;
    cout << flstring.substr(2, 4) << endl;
    cout << flstring.substr(4, 5) << endl;
    cout << flstring.substr(-2, -3) << endl;
    flstring.remove(2, 2);
    cout << flstring << endl;
    FLString stringToInsert = "abcdfere";
    flstring.insert(2, stringToInsert);
    flstring.insert(0, stringToInsert);
    cout << flstring._debugREPL() << endl;
    cout << flstring._debugREPL() << endl;
    cout << flstring << endl;
    findAndReplace(flstring, "abc", "abcabc");
    cout << flstring << endl;
    
    return 0;
}
