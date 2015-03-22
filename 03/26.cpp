/* ============================================================================
 * 26. 強調マークアップの除去
 * 25の処理時に，テンプレートの値からMediaWikiの強調マークアップ（弱い強調，強調，強い強調のすべて）を
 * 除去してテキストに変換せよ（参考: マークアップ早見表）．
 * ========================================================================= */
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
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

std::string removeMarkup(std::string str)
{
	for (size_t pos = 0; (pos = str.find("'''''")) != std::string::npos; )
		str.erase(pos, 5);
	for (size_t pos = 0; (pos = str.find("'''")) != std::string::npos; )
		str.erase(pos, 3);
	for (size_t pos = 0; (pos = str.find("''")) != std::string::npos; )
		str.erase(pos, 2);
	return str;
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
		m[result.substr(1, tmp)] = removeMarkup(result.substr(tmp+3));
	}

	for (auto itr = m.begin(); itr != m.end(); ++itr)
		std::cout << itr->first << "\t" << itr->second << std::endl;
}
