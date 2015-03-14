/* ============================================================================
 * 05. n-gram
 * 与えられたシーケンス（文字列やリストなど）からn-gramを作る関数を作成せよ．
 * この関数を用い，"I am an NLPer"という文から単語bi-gram，文字bi-gramを得よ．
 * ========================================================================= */
#include <iostream>
#include <algorithm>
#include <string>

std::vector<std::string> splitWord(const std::string &str, char delim)
{
	std::vector<std::string> res;
	size_t current = 0, found;

	while ((found = str.find_first_of(delim, current)) != std::string::npos) {
		res.push_back(std::string(str, current, found - current));
		current = found + 1;
	}
		
	if (str.size() != current)
		res.push_back(str.substr(current, str.size() - current));
	return res;
}

std::vector<std::string> charBigram(const std::string& str)
{
	if (str.length() < 2)
		return std::vector<std::string>();

	std::vector<std::string> vec;
	for (size_t pos = 0; pos < str.length()-1; ++pos)
		vec.push_back(str.substr(pos, 2));
	return vec;
}

std::vector<std::string> wordBigram(const std::string& str)
{
    std::vector<std::string> result, vec = splitWord(str, ' ');
	if (vec.size() < 2)
		return std::vector<std::string>();

	for (size_t pos = 0; pos < vec.size()-1; ++pos)
		result.push_back(vec[pos] + " " + vec[pos+1]);
    return result;
}

int main(void)
{
	const std::string str = "I am an NLPer";

	std::vector<std::string> wvec = wordBigram(str);
	for (auto itr = wvec.begin(); itr != wvec.end(); ++itr)
		std::cout << *itr << std::endl;
	std::cout << "====" << std::endl;
	std::vector<std::string> cvec = charBigram(str);
	for (auto itr = cvec.begin(); itr != cvec.end(); ++itr)
		std::cout << *itr << std::endl;
}
