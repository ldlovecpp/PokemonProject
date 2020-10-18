#include<string>
using namespace std;
extern double restrant(string str1, string str2)
{
		if (str1 == "一般")
		{
			if (str2 == "岩石")
			{
				return 0.5;
			}
			else if (str2 == "幽灵")
			{
				return 0;
			}
		}
		else if (str1 == "火")
		{
			if (str2 == "火")
			{
				return 0.5;
			}
			else if (str2 == "水")
			{
				return 0.5;
			}
			else if (str2 == "草")
			{
				return 2;
			}
			else if (str2 == "冰")
			{
				return 2;
			}
			else if (str2 == "虫")
			{
				return 2;
			}
			else if (str2 == "岩石")
			{
				return  0.5;
			}
			else if (str2 == "龙")
			{
				return 0.5;
			}
		}
		else if (str1 == "水")
		{
			if (str2 == "火")
			{
				return 2;
			}
			else  if (str2 == "水")
			{
				return 0.5;
			}
			else if (str2 == "草")
			{
				return 0.5;
			}
			else if (str2 == "地面")
			{
				return 2;
			}
			else if (str2 == "岩石")
			{
				return 2;
			}
			else if (str2 == "龙")
			{
				return 0.5;
			}
		}
		else if (str1 == "草")
		{
			if (str2 == "火")
			{
				return 0.5;
			}
			else if (str2 == "水")
			{
				return 2;
			}
			else if (str2 == "草")
			{
				return 0.5;
			}
			else if (str2 == "毒")
			{
				return 0.5;
			}
			else if (str2 == "地面")
			{
				return 2;
			}
			else if (str2 == "飞行")
			{
				return 0.5;
			}
			else if (str2 == "虫")
			{
				return 0.5;
			}
			else if (str2 == "岩石")
			{
				return 2;
			}
			else if (str2 == "龙")
			{
				return 0.5;
			}
		}
		else if (str1 == "电")
		{
			if (str2 == "水")
			{
				return 2;
			}
			else if (str2 == "草")
			{
				return 0.5;
			}
			else if (str2 == "电")
			{
				return 0.5;
			}
			else if (str2 == "地面")
			{
				return 0;
			}
			else if (str2 == "飞行")
			{
				return 2;
			}
			else if (str2 == "龙")
			{
				return 0.5;
			}
		}
		else if (str1 == "冰")
		{
			if (str2 == "水")
			{
				return 0.5;
			}
			else if (str2 == "草")
			{
				return 2;
			}
			else if (str2 == "冰")
			{
				return 0.5;
			}
			else if (str2 == "地面")
			{
				return 2;
			}
			else if (str2 == "飞行")
			{
				return 2;
			}
			else if (str2 == "龙")
			{
				return 2;
			}
		}
		else if (str1 == "格斗")
		{
			if (str2 == "一般")
			{
				return 2;
			}
			else if (str2 == "冰")
			{
				return 2;
			}
			else if (str2 == "毒")
			{
				return 0.5;
			}
			else if (str2 == "飞行")
			{
				return 0.5;
			}
			else if (str2 == "超能力")
			{
				return 0.5;
			}
			else if (str2 == "虫")
			{
				return 0.5;
			}
			else if (str2 == "岩石")
			{
				return 2;
			}
			else if (str2 == "幽灵")
			{
				return 0;
			}
		}
		else if (str1 == "毒")
		{
			if (str2 == "草")
			{
				return 2;
			}
			else if (str2 == "毒")
			{
				return 0.5;
			}
			else if (str2 == "地面")
			{
				return 0.5;
			}
			else if (str2 == "虫")
			{
				return 2;
			}
			else if (str2 == "岩石")
			{
				return 0.5;
			}
			else if (str2 == "幽灵")
			{
				return 0.5;
			}
		}
		else if (str1 == "地面")
		{
			if (str2 == "火")
			{
				return 2;
			}
			else if (str2 == "草")
			{
				return 0.5;
			}
			else if (str2 == "电")
			{
				return 2;
			}
			else if (str2 == "毒")
			{
				return 2;
			}
			else if (str2 == "飞行")
			{
				return 0;
			}
			else if (str2 == "虫")
			{
				return 0.5;
			}
			else if (str2 == "岩石")
			{
				return 2;
			}
		}
		else if (str1 == "飞行")
		{
			if (str2 == "草")
			{
				return 2;
			}
			else if (str2 == "电")
			{
				return 0.5;
			}
			else if (str2 == "格斗")
			{
				return 2;
			}
			else if (str2 == "虫")
			{
				return 2;
			}
			else if (str2 == "岩石")
			{
				return 0.5;
			}
		}
		else if (str1 == "超能力")
		{
			if (str2 == "格斗")
			{
				return 2;
			}
			else if (str2 == "毒")
			{
				return 2;
			}
			else if (str2 == "超能力")
			{
				return 0.5;
			}
		}
		else if (str1 == "虫")
		{
			if (str2 == "火")
			{
				return 0.5;
			}
			else if (str2 == "草")
			{
				return 2;
			}
			else if (str2 == "格斗")
			{
				return 0.5;
			}
			else if (str2 == "毒")
			{
				return 2;
			}
			else if (str2 == "飞行")
			{
				return 0.5;
			}
			else if (str2 == "超能力")
			{
				return 2;
			}
		}
		else if (str1 == "岩石")
		{
			if (str2 == "火")
			{
				return 2;
			}
			else if (str2 == "冰")
			{
				return 2;
			}
			else if (str2 == "格斗")
			{
				return 0.5;
			}
			else if (str2 == "地面")
			{
				return 0.5;
			}
			else if (str2 == "飞行")
			{
				return 2;
			}
			else if (str2 == "虫")
			{
				return 2;
			}
		}
		else if (str1 == "幽灵")
		{
			if (str2 == "一般") {
				return 0;
			}
			else if (str2 == "超能力")
			{
				return 0;
			}
			else if (str2 == "幽灵")
			{
				return 2;
			}
		}
		else if (str1 == "龙")
		{
			if (str2 == "龙")
			{
				return 2;
			}
		}
		return 1;
}
