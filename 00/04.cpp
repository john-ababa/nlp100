/* ============================================================================
 * 04. 元素記号
 * "Hi He Lied Because Boron Could Not Oxidize Fluorine.
 *  New Nations Might Also Sign Peace Security Clause. Arthur King Can."
 * という文を単語に分解し，1, 5, 6, 7, 8, 9, 15, 16, 19番目の単語は先頭の1文字，
 * それ以外の単語は先頭に2文字を取り出し，取り出した文字列から単語の位置
 * （先頭から何番目の単語か）への連想配列（辞書型もしくはマップ型）を作成せよ．
 * ========================================================================= */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <iterator>
#include <iomanip>

std::vector<std::string> splitWord(const std::string &str, char delim)
{
	std::vector<std::string> res;
	size_t current = 0, found;
	while ((found = str.find_first_of(delim, current)) != std::string::npos) {
		res.push_back(std::string(str, current, found - current));
		current = found + 1;
	}
	res.push_back(std::string(str, current, str.size() - current));
	return res;
}

int main(void)
{
	std::string str = "Hi He Lied Because Boron Could Not Oxidize Fluorine. New Nations Might Also Sign Peace Security Clause. Arthur King Can.";
	str.erase(std::remove(str.begin(), str.end(), ','), str.end());
	str.erase(std::remove(str.begin(), str.end(), '.'), str.end());

	std::vector<std::string> vec = splitWord(str, ' ');

	std::map<std::string, int> m;
	for (auto itr = vec.begin(); itr != vec.end(); ++itr) {
		const int d = std::distance(vec.begin(), itr);
		if (d == 0 || d == 4 || d == 5 || d == 6 || d == 7 || d == 8 || d == 14 || d == 15 || d == 18)
			m[itr->substr(0, 1)] = d;
		else 
			m[itr->substr(0, 2)] = d;
	}

	for (auto itr = m.begin(); itr != m.end(); ++itr)
		std::cout << "[" << std::setfill('0') << std::setw(2) << itr->second << "] " << itr->first << std::endl;
}
