/*
 *
 * This code is copyrighted (c) 2021 by
 * Texas A&M Computer Science
 *
 *	There will be RIGOROUS cheat checking on your exams!!
 *	DON'T POST ANYWHERE!! such as CHEGG, public Github, etc
 *  You will be legally responsible.
 */

#include <string>
#include <stdexcept>
#include <iostream>
#include "Tag.h"

using std::string;
using std::vector;

Tag::Tag(string tagName) {
  // TODO(student): implement constructor checks
  if (tagName.size() < 2 ||
    tagName.at(0) != '#' ||
    tagName.at(1) > 'z' || tagName.at(1) < 'a' ||
    ispunct(tagName.size()-1))
  {
    throw std::invalid_argument("tag constructor: invalid tag");
  }
  for (auto i=tagName.begin()+2; i<tagName.end(); ++i)
  {
    if (*i>='A' && *i<='Z')
    {
      throw std::invalid_argument("tag constructor: invalid tag");
    }
  }
  this->tagName = tagName;
}

string Tag::getTagName() {
  return tagName;
}

vector<Post*>& Tag::getTagPosts() {
  return tagPosts;
}

void Tag::addTagPost(Post* post) {
  if (post)
  {
    tagPosts.push_back(post);
  }
  else
  {
    throw std::invalid_argument("post is nullptr");
  }
  
}
