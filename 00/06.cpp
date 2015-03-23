/* ============================================================================
 * 06. 集合
 * "paraparaparadise"と"paragraph"に含まれる文字bi-gramの集合を，
 * それぞれ, XとYとして求め，XとYの和集合，積集合，差集合を求めよ．さらに，
 * 'se'というbi-gramがXおよびYに含まれるかどうかを調べよ．
 * ========================================================================= */
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

std::vector<std::string> charBigram(const std::string& str)
{
	if (str.length() < 2)
		return std::vector<std::string>();

	std::vector<std::string> vec;
	for (size_t pos = 0; pos < str.length()-1; ++pos)
		vec.push_back(str.substr(pos, 2));
	return vec;
}

void print(const std::vector<std::string>& vec)
{
	for (auto itr = vec.begin(); itr != vec.end(); ++itr)
		std::cout << *itr << " " << std::flush;
	std::cout << std::endl;
}

int main(void)
{
	std::vector<std::string> vec1 = charBigram("paraparaparadise");
	sort(vec1.begin(), vec1.end());
	vec1.erase(std::unique(vec1.begin(), vec1.end()), vec1.end());

	std::vector<std::string> vec2 = charBigram("paragraph");
	sort(vec2.begin(), vec2.end());
	vec2.erase(std::unique(vec2.begin(), vec2.end()), vec2.end());

	std::vector<std::string> u, d, i;
	std::set_union(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), std::back_inserter(u));
	std::set_difference(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), std::back_inserter(d));
	std::set_intersection(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), std::back_inserter(i));

	print(u);
	print(d);
	print(i);
}
