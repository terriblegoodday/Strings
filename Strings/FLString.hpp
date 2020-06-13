//
//  FLString.hpp
//  Strings
//
//  Created by Eduard Dzhumagaliev on 5/20/20.
//  Copyright © 2020 Eduard Dzhumagaliev. All rights reserved.
//

#ifndef FLString_hpp
#define FLString_hpp

#include <stdio.h>
#include <iostream>

using namespace std;

class FLString {
private:
    static const size_t defaultChunkSize = 8;
    
    size_t chunkSize;
    size_t getCstringSize(const char * cstring);
    
    struct Chunk {
        Chunk(const size_t chunkSize=defaultChunkSize);
        ~Chunk();
        
        Chunk * next = nullptr;
        
        size_t chunkSize;
        size_t getLength();
        string getChunk();
        bool isEmpty();
        
        // Implements InputIt/_InputIterator
        Chunk & operator++();
        
        char * charactersChunk;
        
        char & operator[](int i);
    };
    
    Chunk * head = nullptr;
    Chunk * tail = nullptr;
    
    bool isLastChunkFull();
    void addString(string concatString);
    void destructChunks();
    
    string getRegularString() const;
    
    size_t getRawLength();
    
public:
    FLString(const size_t chunkSize=defaultChunkSize);
    FLString(const FLString & source);
    FLString(const char * cstring);
    ~FLString();
    
    bool isEmpty() const;
    size_t getLength();
    
    FLString & operator=(const FLString & source);
    FLString & operator=(const char * source);
    friend FLString operator+(FLString & destination, const FLString & source);
    friend FLString operator+(FLString & destination, const char & source);
    friend FLString operator+(FLString & destination, const string & source);
    friend FLString operator+(FLString & destination, char const * source);

    FLString & operator+=(FLString const & source);
    FLString & operator+=(char const & source);
    FLString & operator+=(string const & source);
    FLString & operator+=(char const * source);
    
    char & operator[](int i);
    
    friend bool operator==(const FLString & left, const FLString & right);
    friend bool operator==(const FLString & left, const char * count);
    
    friend ostream & operator<<(ostream & stream, const FLString & source);
    friend istream & operator>>(istream & stream, FLString & destination);
    
    int find(const char * substring);
    FLString substr(size_t left, size_t count = 1);
    
    string _debugREPL();
    
    void remove(size_t afterIndex, size_t count = 1);
    void insert(size_t afterIndex, FLString & substring);
    void insert(size_t afterIndex, const char * subtring);
    
    friend void findAndReplace(FLString & flstring, const char * stringA, const char * stringB);
    friend void findAndReplace(FLString & flstring, const FLString & stringA, const FLString & stringB);
    
};

#endif /* FLString_hpp */
