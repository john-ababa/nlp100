/* ============================================================================
 * 02. 「パトカー」＋「タクシー」＝「パタトクカシーー」
 * 「パトカー」＋「タクシー」の文字を先頭から交互に連結して文字列「パタトクカシーー」を得よ．
 * ========================================================================= */
#include <iostream>
#include <string>

int main(void)
{
	std::locale::global(std::locale(""));
	const std::wstring str1 = L"パトカー";
	const std::wstring str2 = L"タクシー";

	for (size_t i = 0; i < str1.length(); ++i)
		std::wcout << str1[i] << str2[i] << std::flush;
	std::wcout << std::endl;
}
