/*
 *
 * This code is copyrighted (c) 2021 by
 * Texas A&M Computer Science
 *
 *	There will be RIGOROUS cheat checking on your exams!!
 *	DON'T POST ANYWHERE!! such as CHEGG, public Github, etc
 *  You will be legally responsible.
 */

#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>
#include "Post.h"

using std::string;
using std::vector;

Post::Post(unsigned int postId, string userName, string postText)
  : postId(postId), userName(userName), postText(postText) {
  if (postId == 0 || userName == "" || postText == "") {
    throw std::invalid_argument("post constructor: invalid parameter values");
  }
}

unsigned int Post::getPostId() {
  return postId;
}

string Post::getPostUser() {
  return userName;
}

string Post::getPostText() {
  return postText;
}

vector<string> Post::findTags() {
  vector<string> postTags{};
  string word;
  uint i;
  bool add;
  std::stringstream txt(postText);

  while (txt >> word)
  {
    if (word.at(0) == '#')
    {
      i=0;
      for (auto l=word.begin()+1; l<word.end(); ++l)
      {
        if (*l>='A' && *l<='Z')
        {
          *l += (char)32; // Convert uppercase to lowercase
        }
        else if (*l == '?' || *l == '!' || *l == ',' || *l == '.')
        {
          word.erase(l, word.end()); // Erase from punctuation to the end
          break;
        }
        ++i;
      }
      add = true;
      for (const string& tag : postTags)
      {
        if (tag == word)
        {
          add = false;
          break;
        }
      }
      if (add)
      {
        postTags.push_back(word);
      }
    }
  }
  return postTags;
}
