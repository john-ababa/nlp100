/* ============================================================================
 * 03. 円周率
 *
 * "Now I need a drink, alcoholic of course, after the heavy lectures involving quantum mechanics."
 * という文を単語に分解し，各単語の（アルファベットの）文字数を先頭から出現順に並べたリストを作成せよ．
 * ========================================================================= */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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
	std::string str = "Now I need a drink, alcoholic of course, after the heavy lectures involving quantum mechanics.";
	str.erase(std::remove(str.begin(), str.end(), ','), str.end());
	str.erase(std::remove(str.begin(), str.end(), '.'), str.end());

	std::vector<std::string> vec = splitWord(str, ' ');
	std::sort(vec.begin(), vec.end(), [](const std::string& s1, const std::string& s2) {
		return s1.length() < s2.length();
	});
	
	for (auto itr = vec.begin(); itr != vec.end(); ++itr)
		std::cout << "[" << itr->length() << "] " << *itr << std::endl;
}
