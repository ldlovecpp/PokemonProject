#include"../../include/Skill/pp.h"
void PP::init_pp(int pp)
{
  max_pp = cur_pp =pp;
}
void PP::add_max_pp(int pp)
{
  max_pp += pp;
}
bool PP::add_cur_pp(int pp)
{
  if(cur_pp + pp == max_pp)
    return false;
  if(cur_pp+pp>=max_pp)
  {
    cur_pp = max_pp;
  }
  else
  {
   cur_pp+=pp;
  }
  return true;
}
bool PP::sub_cur_pp(int pp)
{
  if(cur_pp-pp < 0)
  {
    return false;
  }
  else 
    cur_pp-=pp;
  return true;
}
bool PP::pp_run_out()
{
  return cur_pp == 0;
}
int PP::get_cur_pp()
{
  return cur_pp;
}
int PP::get_max_pp()
{
  return max_pp;
}
