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
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Network.h"

using std::string;
using std::vector;
using std::ifstream;

Network::Network() {
  // empty containers of vectors already created
  // no implementation is needed here
}

void Network::loadFromFile(string fileName) {
  // TODO(student): load user and post information from file
  ifstream f(fileName);
  string word;
  string name;
  uint postId;
  string msg("");
  bool hasCommand;
  if (f.is_open())
  {
    while (f >> word)
    {
      if (word == "User")
      {
        f >> name;
        try
        {
          addUser(name);
        }
        catch(const std::invalid_argument& e)
        {
          throw std::runtime_error(e.what());
        }
      }
      else if (word == "Post")
      {
        if (f.peek() == '\n')
        {
          throw std::runtime_error("empty command");
        }
        f >> postId;
        if (f.peek() == '\n')
        {
          throw std::runtime_error("empty command");
        }
        f >> name;
        if (f.peek() == '\n')
        {
          throw std::runtime_error("empty message");
        }
        f.ignore();
        getline(f, msg);

        if (!msg.empty())
        {
          try
          {
            if (isspace(msg.at(0)))
            {
              throw std::runtime_error("Invalid space at the beginning of message");
            }
            addPost(postId, name, msg);
          }
          catch (const std::invalid_argument& e)
          {
            throw std::runtime_error(e.what());
          }
        }
        else
        {
          throw std::runtime_error("empty line");
        }
      }
      else
      {
        throw std::runtime_error("invalid file format");
      }
      if (f.fail())
      {
        throw std::runtime_error("invalid file format");
      }
    }
  }
  else
  {
    throw std::invalid_argument("file doesn't exist");
  }
}

void Network::addUser(string userName) {
  uint i;
  string uname;
  // Convert all characters to lowercase
  for (char& l : userName)
  {
    if (l>='A' && l<='Z')
    {
      l += (char)32;
    }
  }
  for (User* user : users)
  {
    if (userName == user->getUserName())
    {
      throw std::invalid_argument("user is already in the network: " + userName);
    }
  }
  users.push_back(new User(userName));
  std::cout << "Added User " << userName <<  std::endl;
}

void Network::addPost(unsigned int postId, string userName, string postText) {
  bool tagFound;
  for (char& l : userName)
  {
    if (l<='Z' && l>='A')
    {
      l += (char)32;
    }
    
  }
  
  for (User* user : users)
  {
    if (userName == user->getUserName())
    {
      for (Post* post : posts)
      {
        if (post->getPostId() == postId)
        {
          throw std::invalid_argument("post with same post id already exists");
        }
      }
      Post* post = new Post(postId, userName, postText);
      posts.push_back(post);
      user->addUserPost(post);
      for (string& tag : post->findTags())
      {
        tagFound = false;
        for (Tag* t : tags)
        {
          if (t->getTagName() == tag)
          {
            t->addTagPost(post);
            tagFound = true;
            break;
          }
        }
        if (!tagFound)
        {
          try
          {
            Tag* newTag = new Tag(tag);
            newTag->addTagPost(post);
            tags.push_back(newTag);
          }
          catch(const std::exception&)
          {
            continue;
          }
        }
      }
      std::cout << "Added Post " << postId << " by " << userName << std::endl;
      return;
    }
  }
  throw std::invalid_argument("user not found");
}

vector<Post*> Network::getPostsByUser(string userName) {
  // TODO(student): return posts created by the given user
  if (userName.size())
  {
    for (User* user : users)
    {
      if (userName == user->getUserName())
      {
        return user->getUserPosts();
      }
    }
  }
  throw std::invalid_argument("Invalid username");
}

vector<Post*> Network::getPostsWithTag(string tagName) {
  // TODO(student): return posts containing the given tag
  if (tagName.size())
  {
    for (Tag* tag : tags)
    {
      if (tag->getTagName() == tagName)
      {
        return tag->getTagPosts();
      }
    }
  }
  throw std::invalid_argument("Invalid tagname");
}

vector<string> Network::getMostPopularHashtag() {
  // TODO(student): return the tag occurring in most posts
  uint numPosts(tags.at(0)->getTagPosts().size());
  vector<string> maxTags{tags.at(0)->getTagName()};
  for (auto i=tags.begin()+1; i<tags.end(); ++i)
  {
    if ((*i)->getTagPosts().size() >= numPosts)
    {
      if ((*i)->getTagPosts().size() > numPosts)
      {
        numPosts = (*i)->getTagPosts().size();
        maxTags.clear();
      }
      maxTags.push_back((*i)->getTagName());
    }
  }
  return maxTags;
}

/**
  * Destructor
  * Do not change; already implemented.
  */
Network::~Network() {
  for (unsigned int i = 0; i < users.size(); ++i) {
    delete users.at(i);
  }
  for (unsigned int i = 0; i < tags.size(); ++i) {
    delete tags.at(i);
  }
  for (unsigned int i = 0; i < posts.size(); ++i) {
    delete posts.at(i);
  }
}
