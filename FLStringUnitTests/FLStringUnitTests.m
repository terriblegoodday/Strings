//
//  FLStringUnitTests.m
//  FLStringUnitTests
//
//  Created by Eduard Dzhumagaliev on 5/20/20.
//  Copyright © 2020 Eduard Dzhumagaliev. All rights reserved.
//

#import <XCTest/XCTest.h>
#import "FLString.hpp"

@interface FLStringUnitTests : XCTestCase

@end

@implementation FLStringUnitTests

FLString string1;
FLString string2;
FLString string3;

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)addCharactersToString:(FLString * )destination :(string)concatString {
    for (char concatChar: concatString) {
        *destination += concatChar;
    }
}

- (void)testStringInit {
    [self addCharactersToString:&string1:"abcdefgh"];
    cout << string1._debugREPL() << endl;
    XCTAssert(string1._debugREPL() == "abcdefgh⏭");
//    newString += 'b';
//    XCTAssert("abcdefghb");
    [self addCharactersToString:&string1:"qwertyu"];
    cout << string1._debugREPL() << endl;
    XCTAssert(string1._debugREPL() == "abcdefgh⏭qwertyu⏭");
    [self addCharactersToString:&string1: "12345678901234567890"];
    cout << string1._debugREPL() << endl;
    XCTAssert(string1._debugREPL() == "abcdefgh⏭qwertyu1⏭23456789⏭01234567⏭890⏭");
    [self addCharactersToString:&string2:"abc"];
    string1 += string2;
    cout << string1._debugREPL() << endl;
    XCTAssert(string1._debugREPL() == "abcdefgh⏭qwertyu1⏭23456789⏭01234567⏭890abc⏭");
    string1 += string3;
    XCTAssert(string1._debugREPL() == "abcdefgh⏭qwertyu1⏭23456789⏭01234567⏭890abc⏭");
}

- (void)testFindAndReplaceWithStandardLength {
    FLString flstring;
    flstring = "abcdeftre";
    findAndReplace(flstring, FLString("abc"), FLString("abcabc"));
    XCTAssert(flstring == FLString("abcabcdeftre"));
    
    findAndReplace(flstring, "tre", "xxx");
    cout << flstring << endl;
    XCTAssert(flstring == "abcabcdefxxx");
}

- (void)testFindAndReplaceWithVaryingLength {
    for (int i = 1; i < 16; i++) {
        FLString flstring = FLString(i);
        flstring = "abcdeftre";
        
        findAndReplace(flstring, FLString("abc"), FLString("abcabc"));
        XCTAssert(flstring == FLString("abcabcdeftre"));
        
        findAndReplace(flstring, FLString("tre"), FLString("xxx"));
        cout << flstring << endl;
        XCTAssert(flstring == FLString("abcabcdefxxx"));
    }
}

- (void)testFindAndReplaceWithStringDeletion {
    FLString flstring;
    flstring = "abcdeftre";
    findAndReplace(flstring, FLString("abcdeftre"), FLString(""));
    XCTAssert(flstring == FLString(""));
}

- (void)testFindAndReplaceWithIncrementalDeletion {
    FLString flstring;
    flstring = "abcdeftre";
    
    while (flstring.getLength() != 0) {
        char & charToRemove = flstring[(int)flstring.getLength() - 1];
        findAndReplace(flstring, FLString(&charToRemove) , FLString(""));
    }
    
    XCTAssert(flstring == FLString(""));
    
}

- (void)testFindAndReplaceWithMinimisation {
    FLString flstring;
    flstring = "abcdeftre";
    
    findAndReplace(flstring, FLString("abc"), FLString("ab"));
    XCTAssert(flstring == FLString("abdeftre"));
    findAndReplace(flstring, FLString("abd"), FLString("bd"));
    XCTAssert(flstring == FLString("bdeftre"));
    findAndReplace(flstring, FLString("eft"), FLString("f"));
    XCTAssert(flstring == FLString("bdfre"));
}

- (void)testFindAndReplaceNonExistent {
    FLString flstring;
    flstring = "abcdeftre";
    
    findAndReplace(flstring, FLString("iuofhjwe89"), FLString("xxx"));
    XCTAssert(flstring == FLString("abcdeftre"));
}

- (void)testFindAndReplaceDuplicate {
    FLString flstring;
    flstring = "abcdeftre";
    
    findAndReplace(flstring, FLString("abcdeftre"), FLString("abcdeftreabcdeftre"));
    cout << flstring << endl;
    XCTAssert(flstring == FLString("abcdeftreabcdeftre"));
}

@end
