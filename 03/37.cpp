/* ============================================================================
 * 37. 頻度上位10語
 *
 * 出現頻度が高い10語とその出現頻度をグラフ（例えば棒グラフなど）で表示せよ．
 * ========================================================================= */
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <fstream>
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

	// 表示
	std::ofstream ofs("37.dat");
	int count = 0;
	for (auto itr = pvec.begin(); itr != pvec.end(); ++itr) {
		ofs << itr->first << "\t" << itr->second << std::endl;
		if (++count == 10)
			break;
	}
	std::system("gnuplot -e 'plot \"37.dat\" using 0:2:xtic(1) with boxes notitle; pause -1'");
}
