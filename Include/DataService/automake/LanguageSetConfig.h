#pragma once
#include <vector>
#include "Global.h"

class LanguageSetDefine
{
public:
 	/// <summary> 
 	/// 编号
	/// </summary>
	int ID;
 	/// <summary> 
 	/// 本机语言代码
	/// </summary>
	const char* language;
 	/// <summary> 
 	/// 语言包ID
	/// </summary>
	int l_languageID;
 	/// <summary> 
 	/// 手机默认语言编号
	/// </summary>
	std::vector<int> telephone;
 	/// <summary> 
 	/// 语言开关,1=开启，0 =关闭
	/// </summary>
	int enumSwitch;
 	/// <summary> 
 	/// 翻译语言代码
	/// </summary>
	const char* translate;
 	/// <summary> 
 	/// 游戏版本号
	/// </summary>
	const char* gameID;
 	/// <summary> 
 	/// 测试
	/// </summary>
	EunmTest test;
 	/// <summary> 
 	/// 坐标
	/// </summary>
	Vec2 test2;
 	/// <summary> 
 	/// 坐标2
	/// </summary>
	std::vector<Vec2> test3;
};