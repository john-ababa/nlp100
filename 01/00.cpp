/* ============================================================================
 * 00. 文字列の逆順
 * 文字列"stressed"の文字を逆に（末尾から先頭に向かって）並べた文字列を得よ．
 * ========================================================================= */
#include <iostream>
#include <algorithm>
#include <string>

int main(void)
{
	std::string str = "stressed";
	std::reverse(str.begin(), str.end()); 
	std::cout << str << std::endl;
}
