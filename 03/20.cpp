/* ============================================================================
 * 20. JSONデータの読み込み
 * Wikipedia記事のJSONファイルを読み込み，「イギリス」に関する記事本文を表示せよ．
 * ========================================================================= */
#include <iostream>
#include <fstream>
#include <string>
#include "picojson.h"

int main(void)
{
	std::ifstream ifs("jawiki-country.json");

	for (std::string line; std::getline(ifs, line); ) {
		picojson::value v;
		std::string err = picojson::parse(v, line);
		if (err.empty()) {
			picojson::object obj = v.get<picojson::object>();
			if (obj["title"].serialize() == "\"イギリス\"")
				std::cout << obj["text"].serialize() << std::endl;
		}
	}
}
