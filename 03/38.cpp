/* ============================================================================
 * 38. ヒストグラム
 *
 * 単語の出現頻度のヒストグラム（横軸に出現頻度，縦軸に出現頻度をとる単語の種類数を棒グラフで表したもの）を描け．
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

	std::ofstream ofs("38.dat");
	for (auto itr = histgram.begin(); itr != histgram.end(); ++itr)
		ofs << itr->first << "\t" << itr->second << std::endl;
	std::system("gnuplot -e 'plot \"38.dat\" using 0:2:xtic(1) with boxes notitle; pause -1'");
}
