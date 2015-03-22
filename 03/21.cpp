/* ============================================================================
 * 21. カテゴリ名を含む行を抽出
 * 記事中でカテゴリ名を宣言している行を抽出せよ．
 * ========================================================================= */
#include <iostream>
#include <fstream>
#include <string>
#include "picojson.h"

std::string getGBR()
{
	std::ifstream ifs("jawiki-country.json");

	for (std::string line; std::getline(ifs, line); ) {
		picojson::value v;
		std::string err = picojson::parse(v, line);
		if (err.empty()) {
			picojson::object obj = v.get<picojson::object>();
			if (obj["title"].serialize() == "\"イギリス\"")
				return obj["text"].serialize();
		}
	}
	return "";
}

int main(void)
{
	const std::string text = getGBR();

	size_t pos = 0;
	while ((pos = text.find("[[Category:", pos)) != std::string::npos) {
		size_t end = text.find("]]", pos);
		size_t tmp = text.find("|", pos);
		if (tmp != std::string::npos && tmp < end)
			end = tmp;

		std::cout << text.substr(pos+11, end-pos-11) << std::endl;
		pos = end;
	}
}
