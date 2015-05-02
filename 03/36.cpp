/* ============================================================================
 * 36. 単語の出現頻度
 *
 * 文章中に出現する単語とその出現頻度を求め，出現頻度の高い順に並べよ．
 * ========================================================================= */
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "common.h"

template<class Map, class Key>
void countWord(Map& m, const Key& k)
{
	typename Map::iterator it = m.lower_bound(k);
	if (it != m.end() && !m.key_comp()(k, it->first))
		it->second++;
	else
		m.insert(it, typename Map::value_type(k, 1));
}

int main(void)
{
	std::map<std::string, int> m;

	std::vector<std::map<std::string, std::string>> vec = runMecab();
	for (auto itr = vec.begin(); itr != vec.end(); ++itr)
		countWord(m, (*itr)["surface"]);

	std::vector<std::pair<std::string, int>> pvec;
	std::copy(m.begin(), m.end(), std::back_inserter(pvec));
	std::sort(pvec.begin(), pvec.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
		return a.second > b.second;
	});

	for (auto itr = pvec.begin(); itr != pvec.end(); ++itr)
		std::cout << itr->second << "\t" << itr->first << std::endl;
}
