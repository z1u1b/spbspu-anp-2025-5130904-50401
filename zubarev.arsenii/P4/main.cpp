#include <iostream>
#include <iomanip>
#include <cctype>

namespace zubarev
{
  size_t getline(std::istream& in, char* data, size_t size);
  void pushOneEl(char** arr, size_t& size, char value);
  char* getline(std::istream& in, size_t& s);
  std::ostream& outputMatrix(std::ostream& out, const char* const str, const size_t size);
  size_t strlen(const char* s);
  bool inStr(const char* const str, const size_t size, const char let);
  int solveSpliceStr(const char* mainStr, const char* secondStr, char* finalStr);
  int solveUniInAlp(const char* const mainStr, size_t mainSize, char* buf);
}

int main()
{
  namespace zub = zubarev;
  size_t mainSize = 0;
  char* mainStr = zub::getline(std::cin, mainSize);
  if (!mainStr) {
    std::cerr << "Input wrong\n";
    return 1;
  }

  const char* secondStr = "def_";
  size_t secondSize = zub::strlen(secondStr);

  size_t finalSize = secondSize + mainSize;
  char* finalStr = nullptr;

  try {
    finalStr = new char[finalSize + 1];
  } catch (const std::bad_alloc&) {
    std::cerr << "Memory allocation failed for square matrix\n";
    return 1;
  }
  zub::solveSpliceStr(mainStr, secondStr, finalStr);
  zub::outputMatrix(std::cout, finalStr, finalSize);
  delete[] finalStr;


  size_t itogSize = 0;
  char* itogStr = nullptr;
  try {
    itogSize = 26;
    itogStr = new char[itogSize + 1];
  } catch (const std::bad_alloc&) {
    std::cerr << "Memory allocation failed for square matrix\n";
    return 1;
  }

  zub::solveUniInAlp(mainStr, mainSize, itogStr);
  zub::outputMatrix(std::cout, itogStr, zub::strlen(itogStr));
  delete[] itogStr;


  delete[] mainStr;
}

void zubarev::pushOneEl(char** arr, size_t& size, char value)
{
  char* newArr = nullptr;
  try {
    newArr = new char[size + 1];
  } catch (const std::bad_alloc&) {
    std::cerr << "Memory allocation failed for square matrix\n";
  }
  for (size_t i = 0; i < size; i++) {
    newArr[i] = (*arr)[i];
  }

  newArr[size] = value;
  delete[] *arr;
  *arr = newArr;
  size++;
}

char* zubarev::getline(std::istream& in, size_t& s)
{
  char let=' ';
  char* data = nullptr;

  bool is_skipws = in.flags() & std::ios_base::skipws;
  if (is_skipws) {
    in >> std::noskipws;
  }

  in >> let;
  while (let != '\n') {
    if (!in && s==0) {
      return nullptr;
    }
    pushOneEl(&data, s, let);
    in >> let;
  }
  pushOneEl(&data, s, '\0');

  if (is_skipws) {
    in >> std::skipws;
  }

  return data;
}


std::ostream& zubarev::outputMatrix(std::ostream& out, const char* const str, const size_t size)
{
  for (size_t i = 0; i < size; ++i) {
    out << str[i];
  }
  std::cout << '\n';
  return out;
}

size_t zubarev::strlen(const char* s)
{
  size_t len = 0;
  while (s[len] != '\0') {
    len++;
  }
  return len;
}


int zubarev::solveSpliceStr(const char* mainStr, const char* secondStr, char* finalStr)
{
  size_t secondSize = zubarev::strlen(secondStr);
  size_t mainSize = zubarev::strlen(mainStr);

  size_t countMain = 0, countSecond = 0;

  while (countMain < mainSize || countSecond < secondSize) {
    if (countMain < mainSize) {
      *(finalStr++) = *(mainStr++);
      countMain++;
    }

    if (countSecond < secondSize) {
      *(finalStr++) = *(secondStr++);
      countSecond++;
    }
  }
  *finalStr = '\0';
  return 0;
}

bool zubarev::inStr(const char* const str, const size_t size, const char let)
{
  for (size_t i = 0; i < size; ++i) {
    if (std::tolower(str[i]) == std::tolower(let)) {
      return true;
    }
  }
  return false;
}


int zubarev::solveUniInAlp(const char* const mainStr, size_t mainSize, char* buf)
{
  const char* alphabet = "abcdefghijklmnopqrstuvwxyz";
  const size_t alpSize = zubarev::strlen(alphabet);

  for (const char* i = alphabet; i < alphabet + alpSize; ++i) {
    if (!(inStr(mainStr, mainSize, *i))) {
      *(buf++) = *i;
    }
  }
  *buf = '\0';
  return 0;
}
