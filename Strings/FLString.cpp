//
//  FLString.cpp
//  Strings
//
//  Created by Eduard Dzhumagaliev on 5/20/20.
//  Copyright © 2020 Eduard Dzhumagaliev. All rights reserved.
//

#include "FLString.hpp"

FLString::Chunk::Chunk(const size_t chunkSize): charactersChunk(new char[chunkSize]) {
    this->chunkSize = chunkSize;
    for (int i = 0; i < chunkSize; ++i) {
        charactersChunk[i] = '\0';
    }
}

FLString::Chunk::~Chunk() {
    delete [] charactersChunk;
}

FLString::FLString(const size_t chunkSize) {
    if (chunkSize < 3) this->chunkSize = defaultChunkSize;
    this->chunkSize = chunkSize;
    head = new Chunk(this->chunkSize);
    tail = head;
}

FLString::FLString(const char * cstring): FLString::FLString() {
    auto currentChar = cstring;
    while (*currentChar != '\0') {
        operator+=(*currentChar);
        currentChar++;
    }
}

FLString::FLString(const FLString & original) {
    this->chunkSize = original.chunkSize;
    *this = original;
}

void FLString::destructChunks() {
    if (head != nullptr) {
        Chunk * nextChunk = head->next;
        delete head;
        head = nullptr;
        while (nextChunk != nullptr) {
            Chunk * currentChunk = nextChunk;
            nextChunk = nextChunk->next;
            delete currentChunk;
        }
    }
}

FLString::~FLString() {
    destructChunks();
}

size_t FLString::Chunk::getLength() {
    size_t count = 0;
    for (size_t i = 0; i < chunkSize; ++i) {
        if (charactersChunk[i] != '\0') count++;
    }
    return count;
}

bool FLString::isEmpty() const {
    Chunk * currentChunk = head;
    if (currentChunk->getLength() != 0) return false;
    while (currentChunk != tail) {
        currentChunk = currentChunk->next;
        currentChunk->getLength();
        if (currentChunk->getLength() != 0) return false;
    }
    return true;
}

bool FLString::isLastChunkFull() {
    return tail->getLength() == chunkSize;
}

char & FLString::operator[](int b) {
    int charCount = -1;
    
    Chunk * currentChunk = head;
    char & defaultChar = (*currentChunk)[0];
    
    while (currentChunk != nullptr) {
        for (int i = 0; i < chunkSize; i++) {
            if ((*currentChunk)[i] != '\0') charCount++;
            if (charCount == b) return (*currentChunk)[i];
        }
        currentChunk = currentChunk->next;
    }
    
    return defaultChar;
}

FLString & FLString::operator+=(FLString const & source) {
    if (source.isEmpty()) return *this;
    
    Chunk * currentChunk = source.head;
    addString(currentChunk->getChunk());
    
    while (currentChunk != source.tail) {
        currentChunk = currentChunk->next;
        addString(currentChunk->getChunk());
    }
    
    return *this;
}

FLString operator+(FLString & destination, const FLString & source) {
    destination += source;
    return destination;
}


FLString & FLString::operator+=(char const & source){
    if (isLastChunkFull()) {
        tail->next = new FLString::Chunk(chunkSize);
        tail->next->charactersChunk[0] = source;
        tail = tail->next;
    } else {
        size_t freeIndex = tail->getLength();
        tail->charactersChunk[freeIndex] = source;
    }
    
    return *this;
}

FLString & FLString::operator+=(string const & source) {
    addString(source);
    return *this;
}

FLString operator+(FLString & destination, const string & source) {
    destination += source;
    return destination;
}

FLString operator+(FLString & destination, const char & source) {
    destination += source;
    
    return destination;
}

FLString & FLString::operator+=(const char * source) {
    auto currentChar = source;
    while (*currentChar != '\0') {
        operator+=(*currentChar);
        currentChar++;
    }
    return *this;
}

FLString operator+(FLString & destination, const char * source) {
    destination += source;
    
    return destination;
}

string FLString::Chunk::getChunk() {
    string currentChunk = "";
    for (size_t i = 0; i < chunkSize; ++i) {
        if (charactersChunk[i] != '\0') currentChunk += charactersChunk[i];
    }
    
    return currentChunk;
}

string FLString::getRegularString() const {
    string debugString = "";
    Chunk * currentChunk = head;
    debugString += currentChunk->getChunk();
    while (currentChunk != tail) {
        currentChunk = currentChunk->next;
        debugString += currentChunk->getChunk();
    }
    
    return debugString;
}

string FLString::_debugREPL() {
    string debugString = "";
    Chunk * currentChunk = head;
    debugString += currentChunk->getChunk();
    debugString += "⏭";
    while (currentChunk != tail) {
        currentChunk = currentChunk->next;
        debugString += currentChunk->getChunk();
        debugString += "⏭";
    }
    
    return debugString;
}

void FLString::addString(string concatString) {
    for (char concatChar: concatString) {
        if (concatChar != '\0') operator+=(concatChar);
    }
}

FLString & FLString::operator=(const FLString & source) {
    if (this == &source) return *this;
    
    destructChunks();
    
    head = new Chunk(chunkSize);
    head->next = nullptr;
    tail = head;
    
    Chunk * currentChunk = source.head;
    addString(currentChunk->getChunk());
    
    while (currentChunk != source.tail) {
        currentChunk = currentChunk->next;
        addString(currentChunk->getChunk());
    }
    
    return *this;
}



bool operator==(const FLString & left, const FLString & right) {
    return left.getRegularString() == right.getRegularString();
}

bool operator==(const FLString & left, const char * right) {
    return left.getRegularString() == right;
}

FLString & FLString::operator=(const char * source) {
    if (*this == source) return *this;
    
    destructChunks();
    
    head = new Chunk(chunkSize);
    head->next = nullptr;
    tail = head;
    
    auto currentChar = source;
    while (*currentChar != '\0') {
        operator+=(*currentChar);
        currentChar++;
    }
    return *this;
}

ostream & operator<<(ostream & stream, const FLString & source) {
    stream << source.getRegularString();
    return stream;
}

size_t FLString::getLength() {
    size_t length = 0;
    Chunk * currentChunk = head;
    length += currentChunk->getLength();
    
    while (currentChunk != tail) {
        currentChunk = currentChunk->next;
        length += currentChunk->getLength();
    }
    
    return length;
}

size_t FLString::getRawLength() {
    size_t length = 0;
    Chunk * currentChunk = head;
    length += chunkSize;
    
    while (currentChunk != tail) {
        currentChunk = currentChunk->next;
        length += chunkSize;
    }
    
    return length;
}

size_t FLString::getCstringSize(const char * cstring) {
    size_t count = 0;
    auto currentChar = cstring;
    
    while (*currentChar) {
        if (*(currentChar++) != '\0') count++;
    }
    
    return count;
}

char & FLString::Chunk::operator[](int i) {
    return charactersChunk[i % chunkSize];
}

int FLString::find(const char * substring) {
    
    int stringLength = (int)getLength();
    int substringLength = (int)getCstringSize(substring);
    
    if (stringLength - substringLength < 0) return -1;
            
    for (int i = 0; i < stringLength - substringLength + 1; i++) {
        bool fullMatch = true;
        
        for (int j = 0; j < substringLength; j++) {
            
            if ((*this)[i+j] != substring
                [j]) {
                fullMatch = false;
                break;
            }
        }
        if (fullMatch) return i;
    }
    return -1;
}

int FLString::find(const FLString & substring) {
    return find(substring.getRegularString().c_str());
};

FLString FLString::substr(size_t left, size_t count) {
    
    FLString flstring(this->chunkSize);
    size_t rawStringLength = getRawLength();
    size_t stringLength = getLength();
    
    if (left + count > stringLength ||
        left < 0 ||
        count < 1) return "";
    
    size_t charCounter = 0;
    size_t charsIn = 0;
    
    Chunk * currentChunk = head;
    
    
    for (int i = 0; i < rawStringLength; i++) {
        if (i != 0 && i % chunkSize == 0) {
            currentChunk = currentChunk->next;
        }
        
        if ((*currentChunk)[i] != '\0') charCounter++;
        
        if (charCounter - 1 >= left) {
            flstring += (*currentChunk)[i];
            charsIn++;
        }
        if (charsIn == count) return flstring;
    }

    
    return flstring;
}

void FLString::remove(size_t afterIndex, size_t count) {
    size_t rawStringLength = getRawLength();
    size_t stringLength = getLength();
    
    if (afterIndex + count > stringLength ||
        afterIndex < 0 ||
        count < 1) return;
    
    size_t charCounter = 0;
    size_t charsIn = 0;
    
    Chunk * currentChunk = head;
    
    for (int i = 0; i < rawStringLength; i++) {
        if (i != 0 && i % chunkSize == 0) {
            currentChunk = currentChunk->next;
        }
        
        if ((*currentChunk)[i] != '\0') {
            charCounter++;
            if (charCounter - 1 >= afterIndex) {
                (*currentChunk)[i] = '\0';
                charsIn++;
            }
        }
        
        
        if (charsIn == count) return;
    }
}

bool FLString::Chunk::isEmpty() {
    for (int i = 0; i < chunkSize; i++) {
        if (charactersChunk[i] != '\0') return false;
    }
    return true;
}

void FLString::insert(size_t afterIndex, FLString & substring) {
    
    size_t stringLength = getLength();
    
    if (afterIndex + 1 > stringLength) return;
    
    Chunk * currentChunk = head;
    
    if (afterIndex == 0) {
        head = new Chunk(chunkSize);
        head->next = currentChunk;
        currentChunk = head;
        size_t charsIn = 0;
        string stringToInsert = substring.getRegularString();
        size_t substringLength = stringToInsert.length();
        while (charsIn < substringLength) {
            Chunk * newChunk = new Chunk(chunkSize);
            newChunk->next = currentChunk->next;
            currentChunk->next = newChunk;
            currentChunk = newChunk;
            for (int i = 0; i < chunkSize; i++) {
                if (charsIn < substringLength) (*currentChunk)[i] = stringToInsert[charsIn++];
            }
        }
        return;
    }
    
    bool chunkNotFound = true;
    
    size_t indexCounter = 0;
    int chunkIndex = 0;
        
    while (currentChunk->next != nullptr && chunkNotFound) {
        for (int i = 0; i < chunkSize; i++) {
            if (chunkNotFound && (*currentChunk)[i] != '\0') indexCounter++;
            if (chunkNotFound && indexCounter - 1 == afterIndex) {
                chunkNotFound = false;
                chunkIndex = i;
            }
        }
        if (chunkNotFound) {
            currentChunk = currentChunk->next;
        }
    }
    
    string stringToInsert = substring.getRegularString();
    size_t substringLength = stringToInsert.length();
    size_t charsIn = 0;
    
    if (currentChunk->next != nullptr) {
        string charsLeft;
        
        for (int i = chunkIndex; i < chunkSize; i++) {
            if ((*currentChunk)[i] != '\0') {
                charsLeft += (*currentChunk)[i];
                (*currentChunk)[i] = '\0';
            }
        }
        
        Chunk * newChunk = new Chunk(chunkSize);
        newChunk->next = currentChunk->next;
        currentChunk->next = newChunk;
        
        for (int i = 0; i < charsLeft.length(); i++) {
            (*newChunk)[i] = charsLeft[i];
        }
        
        while (currentChunk->next->isEmpty() && charsIn < substringLength) {
            currentChunk = currentChunk->next;
            for (int i = 0; i < chunkSize; i++) {
                if (charsIn < substringLength) (*currentChunk)[i] = stringToInsert[charsIn++];
                else return;
            }
        }
        
        if (charsIn == substringLength) return;
        
        while (charsIn < substringLength) {
            Chunk * newChunk = new Chunk(chunkSize);
            newChunk->next = currentChunk->next;
            currentChunk->next = newChunk;
            currentChunk = newChunk;
            if (currentChunk->next == nullptr) tail = currentChunk;
            
            for (int i = 0; i < chunkSize; i++) {
                if (charsIn < substringLength) (*currentChunk)[i] = stringToInsert[charsIn++];
                else return;
            }
        }
    } else {
        string charsLeft;
        
        for (int i = chunkIndex; i < chunkSize; i++) {
            if ((*currentChunk)[i] != '\0') {
                charsLeft += (*currentChunk)[i];
                (*currentChunk)[i] = '\0';
            }
        }
        
        Chunk * rightChunk = new Chunk(chunkSize);
        tail = rightChunk;
        
        for (int i = 0; i < charsLeft.length(); i++) {
            (*rightChunk)[i] = charsLeft[i];
        }
        
        while (charsIn < substringLength) {
            Chunk * newChunk = new Chunk(chunkSize);
            currentChunk->next = newChunk;
            newChunk->next = rightChunk;
            currentChunk = newChunk;
            for (int i = 0; i < chunkSize; i++) {
                if (charsIn < substringLength) (*currentChunk)[i] = stringToInsert[charsIn++];
            }
        }
    }
}

void FLString::insert(size_t afterIndex, const char * substring) {
    FLString flstring = substring;
    insert(afterIndex, flstring);
}

void findAndReplace(FLString & flstring, const char * stringA, const char * stringB) {
    FLString remainder = flstring;
    size_t stringALength = flstring.getCstringSize(stringA);
    FLString concat;
    while (remainder.find(stringA) != -1) {
        auto index = remainder.find(stringA);
        FLString replaceString = remainder.substr(0, index);
        cout << replaceString << endl;
        remainder = remainder.substr(index+stringALength, remainder.getLength()-index-stringALength);
        cout << remainder << endl;
        concat += replaceString;
        concat += stringB;
    }
    concat += remainder;
    flstring = concat;
}

void findAndReplace(FLString & flstring, const FLString & stringA, const FLString & stringB) {
    findAndReplace(flstring, stringA.getRegularString().c_str(), stringB.getRegularString().c_str());
}
