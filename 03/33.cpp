/* ============================================================================
 * 33. サ変名詞
 *
 * サ変接続の名詞をすべて抽出せよ．
 * ========================================================================= */
#include <iostream>
#include <string>
#include <vector>
#include "common.h"

int main(void)
{
	std::vector<std::map<std::string, std::string>> vec = runMecab();
	for (auto itr = vec.begin(); itr != vec.end(); ++itr) {
		if ((*itr)["pos"] == "名詞" && (*itr)["pos1"] == "サ変接続")
			std::cout << (*itr)["surface"] << std::endl;
	}
}
