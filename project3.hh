///////////////////////////////////////////////////////////////////////////////
// maxprotein.hh
//
// Compute the set of foods that maximizes protein, within a calorie budget,
// with the greedy method or exhaustive search.
//
///////////////////////////////////////////////////////////////////////////////


#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

// Simple structure for a single protein
struct Protein {
	Protein() {
		description = "";
		sequence = "";
	}
	Protein(std::string desc, std::string seq) {
		description = desc;
		sequence = seq;
	}
	std::string		description;
	std::string 	sequence;
};

// Alias for a vector of shared pointers to Protein objects.
typedef std::vector<std::shared_ptr<Protein>> ProteinVector;


// -------------------------------------------------------------------------
// Load all the proteins from a standard FASTA format file with one line
// per sequence (multi-line sequences are not allowed).
// Returns false on I/O error.
// -------------------------------------------------------------------------
bool load_proteins(ProteinVector & proteins, const std::string& path)
{
	//std::cout << "Loading proteins from [" << path << "]" << std::endl;
	proteins.clear();
	std::ifstream ifs(path.c_str());
	if (!ifs.is_open() || !ifs.good()) {
		std::cout << "Failed to open [" << path << "]" << std::endl;
		return false;
	}
	int proteinsLoaded = 0;
	bool have_description = false;
	std::shared_ptr<Protein> newProtein = nullptr;
	while (!ifs.eof()) {
		std::string lineBuffer;
		std::getline(ifs, lineBuffer);
		if (ifs.eof()) {
			break;
		}
		if (lineBuffer.size() == 0) {
			continue;
		}
		if (lineBuffer[0] == '>') {
			newProtein = std::shared_ptr<Protein>(new Protein);
			newProtein->description = lineBuffer.substr(1);
			have_description = true;
		}
		else if (have_description) {
			newProtein->sequence = lineBuffer;
			proteins.push_back(newProtein);
			proteinsLoaded++;
			have_description = false;
		}
	}

	ifs.close();
	//std::cout << "Loaded " << proteinsLoaded << " proteins from [" << path << "]" << std::endl;

	return true;
}


// -------------------------------------------------------------------------
int dynamicprogramming_longest_common_subsequence(const std::string & string1,
	const std::string & string2)
{
	int n = string1.length();
	int m = string2.length();
	//dynamic creation of a 2 dimentional vector 
	std::vector<std::vector<int>>D(n + 1, std::vector<int>(m + 1));

	//initialize all values to zero
	for (int i = 0; i < n; i++)
		D[i][0] = 0;
	for (int j = 0; j < m; j++)
		D[0][j] = 0;

	//dynamic programming magic to find LCS
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			int up = D[i - 1][j];
			int left = D[i][j - 1];
			int diag = D[i - 1][j - 1];
			if (string1[i - 1] == string2[j - 1])
				diag++;
			int intermediate = std::max(up, left);
			D[i][j] = std::max(intermediate, diag);
		}
	}
	return D[n][m];
}

// -------------------------------------------------------------------------
std::unique_ptr<std::vector<std::string>> generate_all_subsequences(const std::string & sequence)
{
	//changed to allocate memory for the vector of strings
	auto R = std::unique_ptr<std::vector<std::string>>(new std::vector<std::string>());
	double n = pow(2, sequence.length());
	//all possible subsequences generating bit wise for loop
	for (uint64_t bits = 0; bits < n; bits++)
	{
		std::string subsequence = "";
		for (int j = 0; j < sequence.length(); j++)
			if (((bits >> j) & 1) == 1)
				subsequence += sequence[j];
		R->push_back(subsequence);
	}
	return R;
}


// -------------------------------------------------------------------------
int exhaustive_longest_common_subsequence(const std::string & string1,
	const std::string & string2)
{
	auto all_subseqs1 = generate_all_subsequences(string1);
	auto all_subseqs2 = generate_all_subsequences(string2);
	int best_score = 0;
	//range based nested for loop
	for (auto& s1 : *all_subseqs1)
	{
		for (auto& s2 : *all_subseqs2)
		{
			if (s1 == s2 && s1.length() > best_score)
				best_score = s1.length();
		}
	}
	return best_score;
}


// -------------------------------------------------------------------------
std::shared_ptr<Protein> exhaustive_best_match(ProteinVector & proteins, const std::string & string1)
{
	//std::shared_ptr<Protein> best_protein = nullptr;
	int best_i = 0;
	int best_score = 0;
	for (int i = 0; i < proteins.size(); i++)
	{
		int score = exhaustive_longest_common_subsequence(proteins[i]->sequence, string1);
		if (score > best_score)
		{
			best_score = score;
			best_i = i;
		}
	}
	return proteins[best_i];
}

// -------------------------------------------------------------------------
std::shared_ptr<Protein> dynamicprogramming_best_match(ProteinVector & proteins, const std::string & string1)
{
	//std::shared_ptr<Protein> best_protein = nullptr;
	int best_i = 0;
	int best_score = 0;
	for (int i = 0; i < proteins.size(); i++)
	{
		int score = dynamicprogramming_longest_common_subsequence(proteins[i]->sequence, string1);
		if (score > best_score)
		{
			best_score = score;
			best_i = i;
		}
	}
	return proteins[best_i];
}


