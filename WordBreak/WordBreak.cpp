// WordBreak.cpp : Defines the entry point for the console application.
/*
Given an input string and a dictionary of words, find out if the input string can be segmented into a space - separated 
sequence of dictionary words.

Consider the following dictionary
{ i, like, sam, sung, samsung, mobile, ice,
cream, icecream, man, go, mango}

Input:  ilike
Output: Yes
The string can be segmented as "i like".

Input:  ilikesamsung
Output: Yes
The string can be segmented as 
	"i like samsung"
or  "i like sam sung".

*/

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;


bool isInDictionary(string A, vector<string> &dict)
{
	//check if string A is part ofthe dictionary
	auto it = dict.begin();
	for (; it != dict.end(); ++it)
	{
		if (A.compare(*it) == 0) //string matches
		{
			return true;
		}
	}

	return false;
}

void wordBreak_Util(string A, int n, vector<string> &B, string curr_sol, vector<string> &sol_set)
{
	for (int i = 1; i <= n; i++)
	{
		string prefix = A.substr(0, i);

		if (isInDictionary(prefix, B))
		{
			if (i == n)
			{
				curr_sol += prefix;
				sol_set.push_back(curr_sol);
				return;
			}
			wordBreak_Util(A.substr(i, n - i), n - i, B, curr_sol + prefix + " ", sol_set);
		}
	}
}

vector<string> wordBreak_Recursive(string A, vector<string> &B) 
{
	vector<string> sol_set;
	string curr_sol = "";
	wordBreak_Util(A, A.size(), B, curr_sol, sol_set);

	return sol_set;
}

vector<string> wordBreak_Iterative(string A, vector<string> &B)
{
	//insert the dictionay words in to unordered_set
	unordered_set<string> dict(B.begin(), B.end());
	//Below words contains all the valid parse starting from the idx i of string A.
	vector<vector<string> > words(A.length() + 1, vector<string>(0));
	//initializing the last 
	words[A.length()].push_back("");

	//For each parse, starting idx "i", we find an idx "j" such that A[i..j-1] is part of  the dictionary.
	//Then we update words[i] = A[i..j-1] + words[j];
	//generate solutions from end
	for (int i = A.length() - 1; i >= 0; i--)
	{
		vector<string> values;
		for (int j = i + 1; j <= A.length(); j++)
		{
			//We are placing space at jth position
			if (dict.find(A.substr(i, j - i)) != dict.end())
			{
				//We are iterating loop over as there could be multiple possible parse from jth position..
				//therefore appending each parse with the prefix.
				for (int k = 0; k < words[j].size(); k++)
				{
					values.push_back(A.substr(i, j - i) + (words[j][k].empty() ? "" : " ") + words[j][k]);
				}
				
			}
		}
		words[i] = values;
	}

	return words[0];
}

int main()
{
	string A;
	cin >> A;
	
	int N;
	cin >> N; 

	vector<string> B;
	string word;
	for (int i = 0; i < N; i++)
	{
		cin >> word;
		B.push_back(word);
	}

	cout << "------------------------wordBreak_Recursive---------------------------" << endl;
	vector<string> res = wordBreak_Recursive(A, B);
	//print the result
	auto it = res.begin();
	for (; it != res.end(); ++it)
	{
		cout << (*it) << " " << endl;
	}
	cout << endl;

	cout << "------------------------wordBreak_Iterative---------------------------" << endl;
	res = wordBreak_Iterative(A, B);
	it = res.begin();
	for (; it != res.end(); ++it)
	{
		cout << (*it) << " " << endl;
	}
	cout << endl;
	
    return 0;
}

