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
#include "User.h"

using std::string;
using std::vector;

User::User(string userName) {
  if (userName.size() < 1 ||
    userName.at(0) > 'z' || userName.at(0) < 'a'
  )
  {
    throw std::invalid_argument("user constructor: invalid username");
  }
  for (auto i=userName.begin()+2; i<userName.end(); ++i)
  {
    if (*i>='A' && *i<='Z')
    {
      throw std::invalid_argument("user constructor: invalid username");
    }
  }
  this->userName = userName;
}

string User::getUserName() {
  return userName;
}

vector<Post*>& User::getUserPosts() {
  return userPosts;
}

void User::addUserPost(Post* post) {
  if (post)
  {
    userPosts.push_back(post);
  }
  else
  {
    throw std::invalid_argument("post is nullptr");
  }
}
