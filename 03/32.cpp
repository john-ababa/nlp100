/* ============================================================================
 * 32. 動詞の原形
 *
 * 動詞の原形をすべて抽出せよ．
 * ========================================================================= */
#include <iostream>
#include <string>
#include <vector>
#include "common.h"

int main(void)
{
	std::vector<std::map<std::string, std::string>> vec = runMecab();
	for (auto itr = vec.begin(); itr != vec.end(); ++itr) {
		if ((*itr)["pos"] == "動詞")
			std::cout << (*itr)["base"] << std::endl;
	}
}
