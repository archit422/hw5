#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <string>
#include <vector>

#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
std::string remove_single_character(const std::string& floating_values_string, char c);
void wordle_helper(
  int i,
  std::string& cur_partial_word,
  const std::set<std::string>& valid_words,
  const std::string& arrangement,
  const std::string& remaining_floating,
  std::set<std::string>& results,
  const std::vector<int>& num_blanks_left
);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here

    std::set<std::string> results; 

    int input_size = static_cast<int>(in.size());
    
    if(input_size ==0)
    {
      return results; 
    }
    

    std::vector<int> blanks_remaining(input_size+1);

    blanks_remaining[input_size] = 0;

    for(int i = input_size-1 ;i>=0; --i)
    {
      if(in[i] == '-')
      {
        blanks_remaining[i] = blanks_remaining[i+1] +1;
      }
      else
      {
        blanks_remaining[i] = blanks_remaining[i+1];
      }
    }
    std::string cur_partial_word = in;
    wordle_helper(0,cur_partial_word,dict,in,floating,results,blanks_remaining);
    return results; 
}

// Define any helper functions here


std::string remove_single_character(const std::string& floating_values_string, char c)
{
  std::string result;
  bool removed = false;

  for(size_t i = 0; i < floating_values_string.size(); i++)
  {
    if(!removed && floating_values_string[i] == c)
    {
      removed = true; 
      continue;
    }
      result += floating_values_string[i];
  }
  return result;
}


void wordle_helper(
  int i,
  std::string& cur_partial_word,
  const std::set<std::string>& valid_words,
  const std::string& arrangement,
  const std::string& remaining_floating,
  std::set<std::string>& results,
  const std::vector<int>& num_blanks_left
)
{
  int cur_size = static_cast<int>(cur_partial_word.size());

  if(i == cur_size)
  {
    if(remaining_floating.empty() && valid_words.find(cur_partial_word) != valid_words.end())
    {
      results.insert(cur_partial_word);
    }
    return;
  }

  int num_blank_left = num_blanks_left[i];
  int num_required = static_cast<int>(remaining_floating.size());
  if(num_required > num_blank_left)
  {
    return;
  }

  if(arrangement[i]!= '-')
  {
    cur_partial_word[i] = arrangement[i];
    wordle_helper(i+1,cur_partial_word,valid_words,arrangement,remaining_floating,results,num_blanks_left);
    return;
  }

  if(num_required == num_blank_left)
  {
    for(size_t j =0; j< remaining_floating.size();j++)
    {
      char c = remaining_floating[j];
      cur_partial_word[i] = c;
      std::string new_remaining_floating = remove_single_character(remaining_floating,c);
      wordle_helper(i+1,cur_partial_word,valid_words,arrangement,new_remaining_floating,results,num_blanks_left);

    }
  }
  
  else
  {
    for(size_t j = 0;j< remaining_floating.size();++j)
    {
      char c =remaining_floating[j];
      cur_partial_word[i] = c;
      std::string new_remaining_floating = remove_single_character(remaining_floating,c);
      wordle_helper(i+1,cur_partial_word,valid_words,arrangement,new_remaining_floating,results,num_blanks_left);
    }

    for(char car = 'a'; car <='z'; ++car)
    {
      cur_partial_word[i] = car; 
      wordle_helper(i+1,cur_partial_word,valid_words,arrangement,remaining_floating,results,num_blanks_left);
    }
  }
}
