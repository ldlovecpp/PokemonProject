#include"../../include/PVW/pvw.h"
Elevs* Player_Vs_Wild::change_player_elevs()
{
   system("clear");
   cout << "选择您的宝可梦" << endl;
   int i;
   for(i=0;i<_role->get_pocket().size();i++)
   {
     if(_role->get_pocket()[i].in_buff("吹飞"))
       continue;
     if(_role->get_pocket()[i].is_die())
     {
       continue;
     }
     cout <<"[" << i+1  <<"]"; 
     cout <<_role->get_pocket()[i].getname()<<" : "<<endl; 
     cout << "描述: " << _role->get_pocket()[i].get_introduce() << endl;
     cout << "当前血量/最大血量: "<<_role->get_pocket()[i].get_cur_hp() << "/"<<_role->get_pocket()[i].get_max_hp() <<endl;
     cout << "属性: " << _role->get_pocket()[i].getpro()<<endl;
     cout << "等级: " << _role->get_pocket()[i].get_lv() << endl;
     cout << "稀有度: " << _role->get_pocket()[i].get_rarity() <<endl;
     cout << "高度: " << _role->get_pocket()[i].get_height() << endl;
     cout << "重量: " << _role->get_pocket()[i].get_weight() << endl;
     cout << endl;
   }
   while(1)
   {
   cout << "请输入你的选择: ";
   int choice = 0;
   cin >> choice;
   if(choice<1||choice>_role->get_pocket().size())
   {
     cout << "输入数据不在给定范围内!! " << endl;
   }
   else if(_role->get_pocket()[choice-1].is_die())
   {
     cout << "当前精灵已经死亡,不可选择" << endl;
   }
   else 
   {
     return &_role->get_pocket()[choice-1];
   }
  }
}
bool Player_Vs_Wild::wild_have_other_elevs()
{
    for(int i=0;i<_wild->get_pocket().size();i++)
    {
      if(_wild->get_pocket()[i].is_die() || _wild->get_pocket()[i].in_buff("吹飞"))
        continue;
      else
        return true;
    }
    return false;
}

void Player_Vs_Wild::dis_play(Elevs* elvs,Elevs* elvs2)
{
     system("clear");
     cout << "对战信息: " <<endl <<endl;
     cout <<elvs->getname()<<" : "<<endl; 
     cout << "描述: " << elvs->get_introduce() << endl;
     cout << "当前血量/最大血量: "<<elvs->get_cur_hp() << "/"<<elvs->get_max_hp() <<endl;
     cout << "属性: " << elvs->getpro()<<endl;
     cout << "等级: " << elvs->get_lv() << endl;
     cout << "稀有度: " << elvs->get_rarity() <<endl;
     cout << "高度: " << elvs->get_height() << endl;
     cout << "重量: " << elvs->get_weight() << endl;
     cout << "异常状态:  " ;
     elvs->display_all_buff();
     cout << endl;
     cout << endl <<endl;
     cout << "vs" <<endl<<endl;
     cout <<elvs2->getname()<<" : "<<endl; 
     cout << "描述: " << elvs2->get_introduce() << endl;
     cout << "当前血量/最大血量: "<<elvs2->get_cur_hp() << "/"<<elvs2->get_max_hp() <<endl;
     cout << "属性: " << elvs2->getpro()<<endl;
     cout << "等级: " << elvs2->get_lv() << endl;
     cout << "稀有度: " << elvs2->get_rarity() <<endl;
     cout << "高度: " << elvs2->get_height() << endl;
     cout << "重量: " << elvs2->get_weight() << endl;
     cout << "异常状态:  " ;
     elvs2->display_all_buff();
     cout << endl;
     sleep(5);
}

void Player_Vs_Wild::deal_player_buff()
{
  for(int i=0;i<_role->get_pocket().size();i++)
  {
    //寄生种子
    if(_role->get_pocket()[i].in_buff("寄生种子"))
    {
      _role->get_pocket()[i].sub_hp(_role->get_pocket()[i].get_max_hp()/8);
      for(int i=0;i<_wild->get_pocket().size();i++) 
      {
        if(_wild->get_pocket()[i].in_buff("吸取寄生种子"))
        {
          _wild->get_pocket()[i].add_hp(_role->get_pocket()[i].get_max_hp());
        }
      }
    }
  }
}

void Player_Vs_Wild::deal_buff_in_end_type(Roles* role)
{
  for(int i=0;i<role->get_pocket().size();i++)
  {
    if(_role->get_pocket()[i].stus_is_set("灼伤"))
    {
      _role->get_pocket()[i].sub_hp(_role->get_pocket()[i].get_max_hp()/16);
    }
    if(role->get_pocket()[i].stus_is_set("中毒"))
    {
      role->get_pocket()[i].sub_hp(_role->get_pocket()[i].get_max_hp()/8);
    }
  }
}
Elevs* Player_Vs_Wild::change_wild_elevs()
{
  while(1)
  {
    int r = rand()%_wild->get_pocket().size();
    if(_wild->get_pocket()[r].is_die()||_wild->get_pocket()[r].in_buff("吹飞"))
      continue;
    else
      return &_wild->get_pocket()[r];
  }
}
bool Player_Vs_Wild::player_have_other_elevs()
{
   for(int i=0;i<_role->get_pocket().size();i++)
   {
      if(_role->get_pocket()[i].in_buff("吹飞")|| _role->get_pocket()[i].is_die()) 
      {
          continue;
      }
      else
        return true;
   }
   return false;
}
void Player_Vs_Wild::deal_wild_buff()
{
  for(int i=0;i<_wild->get_pocket().size();i++)
  {
    //寄生种子
    if(_wild->get_pocket()[i].in_buff("寄生种子"))
    {
      _wild->get_pocket()[i].sub_hp(_wild->get_pocket()[i].get_max_hp()/8);
      for(int i=0;i<_wild->get_pocket().size();i++) 
      {
        if(_role->get_pocket()[i].in_buff("吸取寄生种子"))
        {
          _role->get_pocket()[i].add_hp(_wild->get_pocket()[i].get_max_hp());
        }
      }
    }
  }
}
bool Player_Vs_Wild::attaker_can_use_skill(Elevs* att)
{
  if(att->in_buff("畏缩"))
  {
    att->remove_buff("畏缩");
    return false;
  }
  return true;
}
void Player_Vs_Wild::player_ack_wild(Elevs* player,Elevs* wild)
{
      fight_Sys fs;
      fs.create_fighting(player,wild,true,_role,_wild);
      system("clear");
      cout << "你对对方宝可梦发动了攻击.."<< endl;
      sleep(3); 
}

void Player_Vs_Wild::wild_ack_player(Elevs* player,Elevs* wild)
{
      fight_Sys fs;
      fs.create_fighting(wild,player,false,_role,_wild);
       system("clear");
      cout << "对方宝可梦对你发动了攻击.."<< endl;
      sleep(3);
}

bool Player_Vs_Wild::player_fist_hit(Elevs* player,Elevs* wild)
{
    int player_speed = player->get_spped();
    int wild_speed = wild->get_spped();
    if(player->stus_is_set("麻痹"))
    {
       player_speed/=2;
    }
    if(wild->stus_is_set("麻痹"))
    {
      wild_speed/=2;
    }
    if(player_speed>=wild_speed)
    {
      return true;
    }
    else 
    {
      return false;
    }
}

bool Player_Vs_Wild::player_can_hit(Elevs* player)
{
   if(player->in_buff("破坏光线"))
   {
   player->remove_buff("破坏光线");
   return false;
   }
   return true;
}
bool Player_Vs_Wild:: wild_can_hit(Elevs* wild)
{
   if(wild->in_buff("破坏光线"))
   {
    wild->remove_buff("破坏光线");
     return false;
   }
   return true;
}
bool Player_Vs_Wild::deal_arc()
{
  cout << "当前所持有的物品: " <<endl;
  unordered_map<string ,int>::iterator p = _role->get_arc_info().begin();
  int idx=0;
  while(p!=_role->get_arc_info().end())
  {
    cout << "[" << idx+1 <<"]" <<endl;
    idx++;
    cout <<"名称: " <<p->first <<endl;
    cout <<"数量: "<<p->second <<endl;
    cout <<endl;
    p++;
  }
  cout << endl;
  if(idx!=0)
  {
  cout << "[" << idx+1 <<"]" << ": " <<"退出" <<endl;
  int choice=0;
  p=_role->get_arc_info().begin();
  while(1)
  {
    cout << "请输入你的选择: ";
    cin >>choice;
    if(choice==idx+1)
    {
      return false;
    }
    else if(choice>=1&&choice<=idx)
    {
       for(int i=0;i<choice-1;i++) 
       {
         p++;
       }
       if(p->first=="精灵球"||p->first=="超级球"||p->first=="高级球")
       {
         if(is_triner)
         {
           system("cls");
           cout << "无法对训练师使用" <<endl;
           sleep(3);
           return false;
         }
         else 
         {
          _role->use_arc(p->first);
           Arc arc(_role,&_wild->get_pocket()[0]);
           bool cat_sus=arc.deal_arc(p->first); 
           return cat_sus;
         }
       }
       else 
       {
       _role->use_arc(p->first);
        Arc arc(_role);
        arc.deal_arc(p->first);
        system("cls");
        sleep(3);
        cout << "使用成功" <<endl;
        return false;;
       }
    }
    else 
    {
      cout << "你的输入有误" <<endl;
    }
  }
  }
  else 
  {
    cout << "当前物品为空" <<endl;
    sleep(3);
    return false;
  }
}
bool Player_Vs_Wild::talk_with_player(Elevs*& player)
{

   int choice  =0;
   while(1)
   {
     system("clear");
     cout <<"1.更换妖怪"  <<endl;
     cout <<"2.使用药剂"  <<endl;
     cout <<"3.退出" <<endl;
     cout << "请输入您的选择: ";
     cin >>choice;
     if(choice==1)
     {
      if(player->in_buff("束缚"))
      {
         cout <<"当前精灵被束缚无法被换下....." <<endl;
         sleep(1);
      }
      else 
      {
        player = change_player_elevs();
      }
     }
     else if(choice == 2)
     {
       bool ca=deal_arc();
       if(ca)
         return ca;
     }
     else if(choice==3)
       return false;
     else 
     {
       cout << "您的输入有误,请重新输入" << endl;
     }
   }
}
void Player_Vs_Wild::Fight()
{
  Elevs* player =&_role->get_pocket()[0];
  Elevs* wild=&_wild->get_pocket()[0];
  for(;;)
  {
    deal_wild_buff();
    deal_player_buff();
    deal_buff_in_end_type(_role);
    deal_buff_in_end_type(_wild);
    if(player->in_buff("瞬间移动"))
    {
      deal_fail_info();
      return;
    }
    //显示当前对阵的宝可梦
    //判断当前双方谁先出手
    //if(玩家先)
    //{
    //   if(玩家可以发动攻击) ）
    //   玩家交互(是否更换英雄/使用物品)
    //   玩家对对方发动攻击 
    //   判断当前对方妖怪是否被击倒 ,如果对方已经被击倒则需要更换妖怪如果对方没有可以用的妖怪   游戏结束 
    //   
    //   
    //   if(对方可以发动攻击)
    //   对方对玩家发动攻击
    //   判断玩家当前妖怪是否死亡,如果死亡询问玩家是否要使用药剂或者是更换妖怪  如果玩家没有对应的药剂并且没有英雄游戏结束
    //}
    if(role_is_die())
       deal_fail_info();
    if(wild_is_die())
       deal_success_info();
    //判断玩家是否被吹飞
    if(player->in_buff("吹飞"))
    {
    if(player_have_other_elevs())
    {
       player=change_player_elevs();
    }
    else 
    {
       deal_fail_info();
       return;
    }
    }
    if(wild->in_buff("吹飞"))
    {
      if(wild_have_other_elevs())
      {
        wild=change_wild_elevs();
      }
      else 
      {
        deal_success_info();
        return;
      }
    }
    if(player->in_buff("吼叫"))
    {
    wild->remove_buff("吼叫");
    if(player_have_other_elevs())
    {
       player=change_player_elevs();
    }
    else 
    {
       deal_fail_info();
       return;
    }
    }
    if(wild->in_buff("吼叫"))
    {
      wild->remove_buff("吼叫");
      if(wild_have_other_elevs())
      {
        wild=change_wild_elevs();
      }
      else 
      {
        deal_success_info();
        return;
      }
    }
    dis_play(player,wild);
    if(player_fist_hit(player,wild))
    {
      if(talk_with_player(player))
      {
        deal_success_info();
        return;
      }
      if(player_can_hit(player))
      {
        player_ack_wild(player,wild);
        if(wild->is_die())
        {
           if(wild_have_other_elevs())
           wild=change_wild_elevs();
           else
           {
             deal_success_info();
             return;
           }
        }
      }
      if(wild_can_hit(wild))
      {
          wild_ack_player(player,wild);
          if(player->is_die())
          {
            if(player_have_other_elevs())
            {
               player=change_player_elevs();
            }
            else 
            {
               deal_fail_info();
               return;
            }
          }
      }
    }
    else
    {
      if(wild_can_hit(wild))
      {
          wild_ack_player(player,wild);
          if(player->is_die())
          {
            if(player_have_other_elevs())
            {
               player=change_player_elevs();
            }
            else 
            {
               deal_fail_info();
               return;
            }
          }
      }
      if(talk_with_player(player))
      {
        deal_success_info();
        return;
      }
      if(player_can_hit(player))
      {
        player_ack_wild(player,wild);
        if(wild->is_die())
        {
           if(wild_have_other_elevs())
           wild=change_wild_elevs();
           else
           {
             deal_success_info();
             return;
           }
        }
      }
    }
  }
}

bool Player_Vs_Wild::wild_is_die()
{
  int cnt=0;
  for(int i=0;i<_wild->get_pocket().size();++i)
  {
    if(_wild->get_pocket()[i].is_die())
    {
      ++cnt;
    }
  }
  if(cnt==_wild->get_pocket().size())
    return true;
  return false;
}
bool Player_Vs_Wild::role_is_die()
{
  int cnt=0;
  for(int i=0;i<_role->get_pocket().size();++i)
  {
    if(_role->get_pocket()[i].is_die())
    {
      ++cnt;
    }
  }
  if(cnt==_role->get_pocket().size())
    return true;
  return false;
}

void Player_Vs_Wild::deal_fail_info()
{
  remove_all_buff();
  system("clear"); 
  cout << "你被对方击败了 " <<endl;
  sleep(3);
}

void Player_Vs_Wild::deal_success_info()
{
  //回复状态
  remove_all_buff();
  //计算收益
  int a=1;
  int t=1;
  int b=0;
  for(int i=0;i<_wild->get_pocket().size();i++)
  {
   b+=_wild->get_pocket()[i].get_base_exp();
  }
  int L = 0;
  for(int i=0;i<_wild->get_pocket().size();i++)
  {
   L+=_wild->get_pocket()[i].get_lv();
  } 
  int s=0;
  for(int i=0;i<_role->get_pocket().size();++i)
  {
    if(_role->get_pocket()[i].is_die()==false)
      ++s;
  }
  int k=1;
  int get_exp= (a*t*b*L)/(7*s*k);
  for(int i=0;i<_role->get_pocket().size();i++)
  {
    if(_role->get_pocket()[i].is_die()==false)
      _role->get_pocket()[i].add_exp(get_exp);
  }
  int moneyCnt=0;
  for(int i=0;i<_role->get_pocket().size();i++)
  {
    int cnt = _role->get_pocket()[i].in_buff("聚宝功"); 
    moneyCnt+=cnt*_role->get_pocket()[i].get_lv()*5;
    while(_role->get_pocket()[i].in_buff("聚宝功"))
    {
      _role->get_pocket()[i].remove_buff("聚宝功");
    }
  }
  _role->add_money(moneyCnt);
  //打印胜利logal
  system("clear"); 
  cout << "你击败了对方 " <<endl;
  sleep(3);
}
void Player_Vs_Wild::remove_all_buff()
{
  //移除精灵身上的buff和status
  //回复闪避率和攻防等级
  for(int i=0;i<_role->get_pocket().size();i++) 
  {
     _role->get_pocket()[i].remove_all_buff();
     _role->get_pocket()[i].remove_all_stus();
     _role->get_pocket()[i].restore_addtion();
     _role->get_pocket()[i].restroe_hit_dodge_lv();
  }

}

