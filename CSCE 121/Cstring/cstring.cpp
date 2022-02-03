#include <iostream>
#include "cstring.h"

unsigned int length(char str[]) {
  // returns the length of the string including zero (0)
  size_t i=0;
  while (str[i] != '\0')
  {
    i++;
  }
  return i;
}

unsigned int find(char str[], char character) {
  // returns 
  //  - the index of the first occurence of character in str
  //  - the size if the character is not found
  size_t i=0;
  while (str[i] != character && str[i] != '\0')
  {
    i++;
  }
  return i;
}

bool equalStr(char str1[], char str2[]) {
  // returns true if they are equal and false if they are not
  size_t i=0;
  while (str1[i] == str2[i])
  {
    if (str1[i] == '\0')
    {
      return true;
    }
    i++;
  }
  return false;
}