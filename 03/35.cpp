/* ============================================================================
 * 35. 名詞の連接
 *
 * 名詞の連接（連続して出現する名詞）を最長一致で抽出せよ．
 * ========================================================================= */
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "common.h"

int main(void)
{
	std::stringstream ss;
	std::vector<std::map<std::string, std::string>> vec = runMecab();
	for (auto itr = vec.begin(); itr != vec.end(); ++itr) {
		if ((*itr)["pos"] == "名詞") {
			ss << (*itr)["surface"];
		} else if (!ss.str().empty()) {
			std::cout << ss.str() << std::endl;
			ss.str("");
		}
	}
}
