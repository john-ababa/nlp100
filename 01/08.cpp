/* ============================================================================
 * 08. 暗号文
 * 与えられた文字列の各文字を，以下の仕様で変換する関数cipherを実装せよ．
 *   英小文字ならば(219 - 文字コード)の文字に置換
 *   その他の文字はそのまま出力
 * この関数を用い，英語のメッセージを暗号化・復号化せよ．
 * ========================================================================= */
#include <iostream>
#include <sstream>
#include <string>

std::string encode(const std::string& str)
{
	std::stringstream ss;
	for (auto itr = str.begin(); itr != str.end(); ++itr) {
		if ('a' <= *itr && *itr <= 'z')
			ss << (char)(219 - *itr);
		else
			ss << *itr;
	}
	return ss.str();
}

int main(void)
{
	const std::string str = "AbcDe!fGh#IJKl$mnOP'QRs(tuv)wx=;++ YZ";
	std::cout << str << std::endl;

	const std::string enc = encode(str);
	std::cout << enc << std::endl;

	const std::string dec = encode(enc);
	std::cout << dec << std::endl;
}
