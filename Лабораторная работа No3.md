# Строки

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

Наивная реализация 

