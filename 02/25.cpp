/* ============================================================================
 * 25. テンプレートの抽出
 * 記事中に含まれる「基礎情報」テンプレートのフィールド名と値を抽出し，
 * 辞書オブジェクトとして格納せよ．
 * ========================================================================= */
#include <iostream>
#include <fstream>
#include <string>
#include <map>
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
	const size_t f = text.find("\\n{{基本情報");
	const size_t l = text.find("\\n}}\\n", f+std::string("\\n{{基本情報").length());

	std::map<std::string, std::string> m;
	for (size_t end, pos = 0; (pos = text.find("\\n|", pos)) != std::string::npos && pos <= l; pos = end) {
		end = text.find("\\n", pos+3);

		const std::string result = text.substr(pos+2, end-pos-2);
		size_t tmp = result.find(" = ");
		m[result.substr(1, tmp)] = result.substr(tmp+3);
	}

	for (auto itr = m.begin(); itr != m.end(); ++itr)
		std::cout << itr->first << "\t" << itr->second << std::endl;
}
