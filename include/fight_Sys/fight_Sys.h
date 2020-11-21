#include"../Roles/roles.h"
double restrant(string str1, string str2);
class fight_Sys
{
public:
  //入口
  void create_fighting(Elevs* att,Elevs* def,bool judge,Roles* roles,Roles* _wild);
  //是否命中要害(正常概率)
  bool hit_main();
  //是否命中要害(特殊概率)
  bool sp_hit_main();
  //获取随机值
  int get_rand();
  // 玩家选择技能
  Skill* player_choice_skill();
  //电脑选择技能
  Skill* computer_choice_skill();
  //处理技能
  void deal_skill();
  //获取技能伤害
  int get_ack(double ack,double def,double lv,double base_ack);
  //属性相克
  double pro_restant(string s);
  //是否命中
  bool is_Hit(Skill* sk);
  //获取节能威力
  int get_skill_ack(Skill* sk);
  //处理相关的buff
  void deal_buff(Skill* sk);
private:
  //是不是训练师,有的技能对训练师野怪作用效果不一样
  bool is_player;
  //进攻的精灵
  Elevs* _attcker;
  //防守的精灵
  Elevs* _defender;
  //玩家
  Roles* _roles;
  //野怪或者是训练师
  Roles* _wild;
  //如果当前精灵的所有技能pp都为0 南无强迫使用挣扎
  Skill stru;
};
