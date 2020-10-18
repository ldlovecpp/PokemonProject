#include"../Roles/roles.h"
double restrant(string str1, string str2);
class fight_Sys
{
public:
  void create_fighting(Elevs* att,Elevs* def,bool judge,Roles* roles,Roles* _wild);
  bool hit_main();
  bool sp_hit_main();
  int get_rand();
  Skill* player_choice_skill();
  Skill* computer_choice_skill();
  void deal_skill();
  int get_ack(double ack,double def,double lv,double base_ack);
  double pro_restant(string s);
  bool is_Hit(Skill* sk);
  int get_skill_ack(Skill* sk);
  void deal_buff(Skill* sk);
private:
  bool is_player;
  Elevs* _attcker;
  Elevs* _defender;
  Roles* _roles;
  Roles* _wild;
  Skill stru;
};
