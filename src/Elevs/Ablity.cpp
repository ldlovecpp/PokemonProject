#include"../../include/Elevs/Ability.h"
bool Hp::sub_hp(int cnt)
{
  if(cur_hp==0) 
    return false;
  if(cur_hp-cnt<=0)
    cur_hp=0;
  else 
    cur_hp-=cnt;
  return true;
}
bool Hp::is_die()
{
  return cur_hp==0;
}
int Hp::get_cur_hp()
{
  return cur_hp;
}
int Hp::get_max_hp()
{
  return max_hp;
}
void Hp::update_hp(int lv,int base_point)
{
  max_hp = (double)((double)race_hp + (double)pow((double)base_point,0.5))*(double)lv/50 + 10 + lv;
}
void Hp::init(int lv,int hp,int base_point)
{
  race_hp = hp; 
  update_hp(lv,base_point);
  cur_hp = max_hp;
}
void Hp::add_hp(int cnt)
{
  if(cur_hp + cnt  >=  max_hp)
    cur_hp  = max_hp;
  else 
  {
    cur_hp += cnt;
  }
}
int Ability::get_ack(int c,int lv,int base_point)
{
  return get_abi(lv,c,base_point);
}
int Ability::get_def(int c,int lv,int base_point)
{
  return get_abi(lv,c,base_point);
}
int Ability::get_s_ack(int c,int lv,int base_point)
{
  return get_abi(lv,c,base_point);
}

int Ability::get_s_def(int c,int lv,int base_point)
{
  return get_abi(lv,c,base_point);
}
int Ability::get_speed(int c,int lv,int base_point)
{
  return get_abi(lv,c,base_point);
}
int Ability::get_abi(int lv,int c,int base_point)
{
   return (double)((double)c+(double)pow((double)base_point,0.5)) * (double)lv / 50 + 5;
}
