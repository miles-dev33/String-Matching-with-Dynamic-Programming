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
    } else if (have_description) {
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
  return 0;
}

// -------------------------------------------------------------------------
std::unique_ptr<std::vector<std::string>> generate_all_subsequences(const std::string & sequence)
{
 	std::unique_ptr<std::vector<std::string>> subsequences(nullptr);

	return subsequences;
}


// -------------------------------------------------------------------------
int exhaustive_longest_common_subsequence(const std::string & string1, 
										  const std::string & string2)
{
	return 0;
}


// -------------------------------------------------------------------------
std::shared_ptr<Protein> exhaustive_best_match(ProteinVector & proteins, const std::string & string1)
{
	std::shared_ptr<Protein> best_protein = nullptr;

	return best_protein;
}

// -------------------------------------------------------------------------
std::shared_ptr<Protein> dynamicprogramming_best_match(ProteinVector & proteins, const std::string & string1)
{
	std::shared_ptr<Protein> best_protein = nullptr;

	return best_protein;
}


