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
    FLString flstring = FLString(4);
    FLString flstring1 = FLString(7);
    flstring1= flstring = "";
    cout <<"0"<< flstring << endl;
    
    findAndReplace(flstring, "abc", "abcabc");
    cout << flstring << endl;
    
    // flstring = flstring+"___"+flstring+"------";
    cout <<"1"<< flstring << endl;
    
    findAndReplace(flstring,"", "");
    cout <<"2"<< flstring << endl;
    
    return 0;
}
