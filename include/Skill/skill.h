#include"jsoncpp/json/json.h"
#include<unordered_map>
#include"pp.h"
#include<fstream>
#include<iostream>
#include<typeinfo>
using namespace std;
struct Skill_Info
{
  int no;
  string name;
  string category;
  string pro;
  string ways;
  int ack;
  int pp;
  int hit_persent;
  int target_num;
  string introduce;
};
class Skill
{
//读取信息
private:
  template<typename T>
  void read_file(T s);
//创建技能
public:
  void create_Skill_by_name(string name);
  void create_Skill_by_no(int no);
//技能名称
  string get_name();
//技能类别
  string get_category();
//技能属性
  string get_pro();
//技能施加方法
  string get_skill_ways();
//获取技能基础伤害
  int get_skill_base_ack();
//pp系统
  //获取当前pp
  int get_cur_pp();
  //获取最大pp
  int get_max_pp();
  //增加当前pp
  bool add_cur_pp(int c);
  //增加pp上限
  void add_max_pp(int c);
  //减少当前pp
  bool sub_cur_pp(int c =1);
//获取是否命中
  bool is_Hit();
//可以攻击目标数量
  int get_target_num();
//技能介绍
  string get_introduce();
//命中率
  int hit_per();
//buff
  void set_buff(string name);
  void remove_buff(string name);
  bool in_buff(string name);
private:
  //节能信息原始数据
  Skill_Info skill_info;
  //技能的buff比如一击必死这种
  unordered_map<string,int>buff;
  //技能的pp值相关
  PP p;
};
