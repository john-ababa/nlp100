/* ============================================================================
 * 09. Typoglycemia
 * スペースで区切られた単語列に対して，各単語の先頭と末尾の文字は残し，
 * それ以外の文字の順序をランダムに並び替えるプログラムを作成せよ．
 * ただし，長さが４以下の単語は並び替えないこととする．
 * 適当な英語の文（例えば"I couldn't believe that I could actually understand
 * what I was reading : the phenomenal power of the human mind ."）を与え，
 * その実行結果を確認せよ．
 * ========================================================================= */
#include <iostream>
#include <iterator>
#include <random>
#include <sstream>
#include <string>
#include <algorithm>

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

std::string shuffle(std::vector<std::string>& vec)
{
	std::random_device rd;
	std::mt19937 g(rd());

	std::stringstream ss;
	for (auto itr = vec.begin(); itr != vec.end(); ++itr) {
		if (itr->length() >= 4)
			std::shuffle(itr->begin()+1, itr->end()-1, g);
		ss << *itr << ' ';
	}
	return ss.str();
}

int main(void)
{
	const std::string str = "I couldn't believe that I could actually understand what I was reading : the phenomenal power of the human mind .";
	std::vector<std::string> vec = splitWord(str, ' ');

	std::cout << shuffle(vec) << std::endl;
}
