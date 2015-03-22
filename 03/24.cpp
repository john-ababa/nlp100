/* ============================================================================
 * 24. ファイル参照の抽出
 * 記事から参照されているメディアファイルをすべて抜き出せ．
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

void searchMediaFile(const std::string& text, const std::string& file)
{
	for (size_t end, pos = 0; (pos = text.find(file, pos)) != std::string::npos; pos = end) {
		end = text.find("|", pos);
		std::cout << text.substr(pos+file.length(), end-pos-file.length()) << std::endl;
	}
}

int main(void)
{
	const std::string text = getGBR();

	searchMediaFile(text, "[[File:");
	searchMediaFile(text, "[[ファイル:");
}
