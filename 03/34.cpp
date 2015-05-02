/* ============================================================================
 * 34. 「AのB」
 *
 * 2つの名詞が「の」で連結されている名詞句を抽出せよ．
 * ========================================================================= */
#include <iostream>
#include <string>
#include <vector>
#include "common.h"

int main(void)
{
	std::vector<std::map<std::string, std::string>> vec = runMecab();
	for (auto itr = vec.begin(); itr != vec.end(); ++itr) {
		if (!((*itr)["pos"] == "名詞"))
			continue;
		if (!(itr+1 != vec.end() && (*(itr+1))["surface"] == "の"))
			continue;
		if (!(itr+2 != vec.end()) && (*(itr+2))["pos"] == "名詞")
			continue;
		std::cout << (*itr)["surface"] << (*(itr+1))["surface"] << (*(itr+2))["surface"] << std::endl;
	}
}
