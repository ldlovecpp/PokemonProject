#pragma  once
#include<math.h>
class Hp
{
public:
bool sub_hp(int cnt);
bool is_die();
int get_cur_hp();
int get_max_hp();
void update_hp(int lv,int base_point);
void init(int lv,int hp,int base_point);
void add_hp(int cnt);
private:
  int cur_hp;
  int max_hp;
  int race_hp;
};
class Ability{
public:
  int get_ack(int ack,int lv,int base_point);
  int get_def(int ack,int lv,int base_point);
  int get_s_ack(int ack,int lv,int base_point);
  int get_s_def(int ack,int lv,int base_point);
  int get_speed(int ack,int lv,int base_point);
private:
  int get_abi(int lv,int c,int base_point);
};
