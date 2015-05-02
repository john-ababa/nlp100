/* ============================================================================
 * 39. Zipfの法則
 *
 * 単語の出現頻度順位を横軸，その出現頻度を縦軸として，両対数グラフをプロットせよ．
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
	std::vector<std::map<std::string, std::string>> vec = runMecab();

	std::map<std::string, int> m;
	for (auto itr = vec.begin(); itr != vec.end(); ++itr)
		countWord(m, (*itr)["surface"]);

	std::map<int, int> histgram;
	for (auto itr = m.begin(); itr != m.end(); ++itr)
		countWord(histgram, itr->second);

	std::ofstream ofs("39.dat");
	for (auto itr = histgram.begin(); itr != histgram.end(); ++itr)
		ofs << itr->first << "\t" << itr->second << std::endl;
	std::system("gnuplot -e 'set logscale x; set logscale y; plot \"39.dat\" using 1:2 with linespoints notitle; pause -1'");
}
