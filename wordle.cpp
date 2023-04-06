#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
// std::set<std::string> assignFloat(std::string in, std::set<std::string> setIn, const std::set<std::string>& dic, std::string floating, int index);
// std::set<std::string> assignChar(std::string in, std::set<std::string> setIn, const std::set<std::string>& dic);
// bool find(std::string& in, const std::set<std::string>& dic);
void helper(std::string in, const std::string& floating, const std::set<std::string>& dict, std::set<std::string>& sets, const unsigned int c);
void helper2( const unsigned int c, std::string in, const std::set<std::string>& dict, std::set<std::string>& sets);

std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{

    std::set<std::string> sets;
    helper(in, floating, dict, sets, 0);
    return sets;

}
void helper2(const unsigned int c, std::string in, const std::set<std::string>& dict, std::set<std::string>& sets)
{
	if(c == in.length() )
	{
		if( dict.find(in) != dict.end() )
		{
			sets.insert(in); 
			return; 
		}
	}
	else if( in[c] == '-' )
	{
		for (int i=97; i<123; i++)
		{
			in[c] = char(i);
			helper2(  c+1, in, dict, sets );
		}
	}
	else
	{
		helper2(  c+1, in, dict, sets );
	}
}
void helper(std::string in, const std::string& floating, const std::set<std::string>& dict, std::set<std::string>& sets, const unsigned int c)
{
	if( floating.length() ==c)
	{
		helper2(0,  in, dict, sets );
		return;
	}

	for(  int i = 0; i < (int)in.length(); i++ )
	{
		if( in[i] == '-' )
		{
			in[i] = floating[c];
			helper(in, floating, dict, sets, c+1 );//fill in the rest
			in[i] = '-';//to keep recursion
		}
	}
}

