/* ============================================================================
 * 23. セクション構造
 * 記事中に含まれるセクション名とそのレベル（例えば"== セクション名 =="なら1）を表示せよ．
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
	while ((pos = text.find("\\n=", pos)) != std::string::npos) {
		int count = 0;
		size_t end = text.find("=\\n", pos);
		pos += 2;
		while (text[pos] == '=') {
			++pos;
			++count;
		}
		while (text[end] == '=')
			--end;
		std::cout << count << " " << text.substr(pos, end+1-pos) << std::endl;
		pos = end;
	}
}
