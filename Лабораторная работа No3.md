# Строки

## repl.it: [https://repl.it/@terriblegoodday/Strings](https://repl.it/@terriblegoodday/Strings)

## Постановка задачи 

Реализовать класс для представления АТД – абстрактного типа даных.
Строки (многосимвольные звенья фиксированной длины) – односвязный список.

- [ ] Конструктор (2 шт.)
- [ ] Конструктор копирования
- [ ] Длина
- [ ] Печать (перегрузка cout)
- [ ] Поиск
- [ ] Перегрузка присваивания
- [ ] Перегрузка+
- [ ] `substr` (`copy`)

- [ ] Как реализовать замену всех вхождений `“abc”` на `"abcabc"`

## Константы

`const size_t defaultChunkSize = 8` – размер блока в строке по умолчанию

## Спецификация

### `FLString(const size_t chunkSize = defaultChunkSize`

Создает строку с заданной длиной блока.

### `FLString(const char * cstring)`

Создает строку с длиной блока по умолчанию из стандартной строки С.

### `FLString(const FLString & source)`

Конструктор копирования.

### `FLString & operator=(const FLString & source)`

Перегрузка оператора присваивания. Присваиваем уже существующую строку `FLString`, причем оставляем уже существующий в приемнике размер блока .

### `FLString & operator=(const char * source)`

Перегрузка оператора присваивания. Присваиваем существующему экземпляру класса стандартную строку C, оставляя уже существующую в приемнику длину блока.

### `friend FLString operator+(FLString & destination, const FLString & source)`

### `friend FLString operator+(FLString & destination, const char & source)`

### `friend FLString operator+(FLString & destination, const string & source)`

### `friend FLString operator+(FLString & destination, char const * source)`

### FLString & operator+=(FLString const & source)
### FLString & operator+=(char const & source)
### FLString & operator+=(string const & source)
### FLString & operator+=(char const * source)

Перегрузка операторов сложения.

### `friend bool operator==(const FLString & left, const FLString & right)`
### `friend bool operator==(const FLString & left, const char * count)`

Перегрузка проверки на равенство для экземпляров `FLString` и экземпляра `FLString` + стандартной C-строки.

### `friend ostream & operator<<(ostream & stream, const FLString & source)`
### `friend istream & operator>>(istream & stream, FLString & destination)`

Перегрузка операторов ввода/вывода.

### `int find(const char * substring)`

Ищет индекс первого вхождения подстроки `substring` (представлена в виде стандартной C-строки) в экземпляр класса.

### `FLString substr(size_t left, size_t count = 1)`
 
Вывод подстроки, начинающейся с `left` и имеющей длину `count`.

Если `left+count` больше длины строки, то выводит пустую строку.

Если `left` $\lt$ 0 или `count` $\lt$ 0, то выводит пустую строку.

### `void remove(size_t after, size_t count = 1)`

Удаляет подстроку, начинающуюся с `after` и имеющую длину `count`.

### `void insert(size_t afterIndex, FLString & substring)`
### `void insert(size_t afterIndex, const char * subtring)`

Вставляет подстроку в экземляр класса по индексу `afterIndex`. Можно вставлять как `FLString`, так и стандартную C-строку.

### `friend void findAndReplace(FLString & flstring, const char * stringA, const char * stringB)`
### `friend void findAndReplace(FLString & flstring, const char * stringA, const char * stringB)`

Поиск и замена всех вхождений `stringA` на `stringB`

## Тесты

### Инициализация строки
```
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
```


### Поиск и замена вхождений
```
- (void)testFindAndReplaceWithStandardLength {
	// Здесь начинается
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
```
