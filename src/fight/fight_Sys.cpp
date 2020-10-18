#include"../../include/fight_Sys/fight_Sys.h"
#include<unistd.h>
bool fight_Sys::is_Hit(Skill* sk)
{
    int hit_persent = _attcker->get_hit_per();
    int dodge_persent = _defender->get_dodge_per();
    int skill_persent = sk->hit_per();
    int r =rand()%255+1;
    int a = 0;
    if(skill_persent==100)
    {
      a=255;
    }
    else if(skill_persent==95)
    {
      a=242;
    }
    else if(skill_persent==90)
    {
      a=229;
    }
    else if(skill_persent==85)
    {
      a=216;
    }
    else if(skill_persent==80)
    {
      a=204;
    }
    else if(skill_persent==75)
    {
      a=191;
    }
    else if(skill_persent==70)
    {
      a=178;
    }
    else if(skill_persent==60)
    {
      a=153;
    }
    else if(skill_persent== 55)
    {
      a=140;
    }
    else if(skill_persent==50)
    {
      a=127;
    }
    else 
    {
      a=100;
    }
    int A= a*hit_persent*dodge_persent;
    if(A>=r)
    {
      return true;
    }
    else 
      return false;
}
int fight_Sys::get_rand()
{
  return rand()%100+1;
}
bool fight_Sys::hit_main()
{
   int r= _attcker->get_spped()/512; 
   r*=100;
   int rd= get_rand();
   return r>=rd; 
}
void fight_Sys::create_fighting(Elevs* att,Elevs* def,bool judge,Roles*roles ,Roles* wild)
{
  _attcker = att;
  _defender = def;
  _roles = roles;
  is_player = judge;
  _wild = wild;
  stru.create_Skill_by_name("挣扎"); 
  deal_skill();
}
Skill* fight_Sys::player_choice_skill()
{
  system("clear");
  cout <<"请选择你的技能: " <<endl<<endl;
  cout<< "宝可梦: " <<_attcker->getname(); 
  cout << endl;
  int cnt = 0;
  for(int i=0;i<_attcker->get_All_Skill().size();i++)
  {
   if(_attcker->get_All_Skill()[i].get_cur_pp()==0)
   {
     ++cnt;
   }
   if(_attcker->get_All_Skill()[i].in_buff("定身法"))
   {
     _attcker->get_All_Skill()[i].remove_buff("定身法");
     ++cnt;
   }
  }
  cout <<"1"<<endl;
  if(cnt == _attcker->get_All_Skill().size())
  {
     return &stru;
  }
  for(int i=0 ;i <_attcker->get_All_Skill().size();i++)
  {
   if(_attcker->get_All_Skill()[i].in_buff("定身法"))
   {
     continue;
   }  
    cout << "[" <<i+1 << "] ";
    cout << _attcker->get_All_Skill()[i].get_name() <<endl;
    cout << "技能描述: " << _attcker->get_All_Skill()[i].get_introduce() << endl;
    cout << "属性: "; 
    cout << _attcker->get_All_Skill()[i].get_pro() <<endl;
    cout << "当前pp/最大pp: " << _attcker->get_All_Skill()[i].get_cur_pp() <<"/" << _attcker->get_All_Skill()[i].get_max_pp() << endl;
    cout << "施法方式: " << _attcker->get_All_Skill()[i].get_skill_ways() <<endl;
    cout << "技能类型: " << _attcker->get_All_Skill()[i].get_category() <<endl;
  }
  while(1)
  {
    cout << "请输入您的选择: ";
    int choice=0;
    cin >> choice;
  
    if(choice <1 || choice >_attcker->get_All_Skill().size())
    {
      cout << "输入信息不在可选范围内..." <<endl;
    }
    else if(_attcker->get_All_Skill()[choice-1].get_cur_pp()==0)
    {
      cout << "技能pp已经耗尽,无法释放!!"<<endl;
    }
    else 
    {
    _attcker->set_Last_Skill(&_attcker->get_All_Skill()[choice-1]);
     return &_attcker->get_All_Skill()[choice-1];
    }
  }
}
Skill* fight_Sys::computer_choice_skill()
{
  system("clear");
  cout << "对方选择技能中........" <<endl;
  sleep(3);
  int cnt=0;
  for(int i=0;i<_attcker->get_All_Skill().size();i++)
  {
   if(_attcker->get_All_Skill()[i].get_cur_pp()==0)
   {
     ++cnt;
   }
  }
  if(cnt == _attcker->get_All_Skill().size())
  {
     return &stru;
  }
  while(1)
  {
  int r= rand()%_attcker->get_All_Skill().size();
  if(_attcker->get_All_Skill()[r].get_cur_pp()!=0)
  return &_attcker->get_All_Skill()[r];
  else 
    continue;
  }
}
int fight_Sys::get_ack(double ack,double def,double lv,double base_ack)
{
  double  res = (2*lv+10)/250*(ack/def)*base_ack + 2;
  return res;
}
bool fight_Sys::sp_hit_main()
{
  int r = _attcker->get_spped()*4/256 ;
  r*=100;
  int rd = get_rand();
  return r>=rd;
}
int fight_Sys::get_skill_ack(Skill* sk)
{
    //特殊技能踢倒的技能威力和对方宝可梦的体重有关因此要单独处理
    int base=0;
    if(sk->get_name()=="踢到")
    {
      stringstream ss;
      ss<<_defender->get_weight();
      double a=0.0;
      ss>>a;
      if(a<=9.9) 
      {
        base=20;
      }
      else if(a>=10.0&&a<=24.9)
      {
        base=40;
      }
      else if(a>=25&&a<=49.9)
      {
        base=60;
      }
      else if(a>=50&&a<=99.9)
      {
        base=80;
      }
      else if(a>=100&&a<=199.9)
      {
        base=100;
      }
      else if(a>=200)
      {
        base=120;
      }
    }
    else 
    {
      base=sk->get_skill_base_ack();
    }
    //属性一致
    if(_attcker->in_pro(sk->get_pro()))
      base*=1.5;
    return base;
}
void fight_Sys::deal_skill()
{
   Skill* sk;
   if(is_player)   
   {
    sk=player_choice_skill(); 
   }
   else 
   {
     sk=computer_choice_skill();
   }
   //睡眠
   if(_attcker->stus_is_set("睡眠"))
   {
     _attcker->remove_stus("睡眠");
     if(sk->get_name()!="梦话"&&sk->get_name()!="打鼾")
     {
       return;
     }
   }
   //冰冻
   if(_attcker->stus_is_set("冰冻"))
   {
   if(sk->get_name()!="火焰轮"&&sk->get_name()!="神圣之火"&&sk->get_name()!="闪焰重返"&&sk->get_name()!="热水"&&sk->get_name()!="交错火焰"&&sk->get_name()!="蒸汽爆炸"&&sk->get_name()!="燃尽"&&sk->get_name()!="熊熊火爆")
     return;
   else 
     _attcker->remove_stus("冰冻");
   } 
   if(sk->get_name() == "模仿")
   {
     sk->sub_cur_pp();  
     if(sk->get_name() == "指挥")
       return;
     if(sk->get_name() == "模仿")
       return;
     if(sk->get_name() == "挣扎")
       return;
     sk = _defender->get_last_use_Skill();
   }
   if(sk->get_name() == "鹦鹉学舌")
   {
     sk->sub_cur_pp();  
     if(sk->get_name() == "指挥")
       return;
     if(sk->get_name() == "模仿")
      return;
     if(sk->get_name() == "挣扎")
       return;
     if(sk->get_name() == "变身")
       return;
     if(sk->get_name() == "挣扎")
       return;
     if(sk->get_name() == "鹦鹉学舌")
       return;
     if(sk->get_name() == "双倍奉还")
       return;
     if(sk->get_name() == "忍耐")
       return;
     if(sk->get_name() == "替身")
       return;
     sk = _defender->get_last_use_Skill();
   }

   int base_ack=0;
   if(sk->get_skill_base_ack()!=0)
   {
    int att_ack = _attcker->get_ack();
    int defder_def=_defender->get_def();
    base_ack = get_ack(att_ack,defder_def,_attcker->get_lv(),get_skill_ack(sk));
   }
  //混乱
   if(_attcker->in_buff("混乱"))
   {
     int r = rand()%3;
     if(r==0)
     {
       _attcker->sub_hp(get_ack(_attcker->get_ack(),_attcker->get_def(),_attcker->get_lv(),40));
       _attcker->remove_buff("混乱");
       return;
     }
   }
   //灼伤
   if(sk->get_category()!="物理"&&_attcker->stus_is_set("灼伤"))
   {
      base_ack/=2;
   }
   if(sk->get_category() == "特殊"&&_defender->in_buff("光墙"))
   {
     base_ack/=2;
   }
   if(base_ack<1)
     base_ack=1;
   if(sk->get_name() == "拍击")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name()=="空手劈")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(sp_hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name()=="连环巴掌")
   {
     sk->sub_cur_pp();
     int r= get_rand();
     if(r>=60)
     {
       int c = rand()%1+2;
       base_ack*=c;
     }
     else if(r>=85)
     {
       int c=rand()%1+5;
       base_ack*=c;
     }
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(sp_hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name()=="连续拳")
   {
     sk->sub_cur_pp();
     int r= get_rand();
     if(r>=60)
     {
       int c = rand()%1+2;
       base_ack*=c;
     }
     else if(r>=85)
     {
       int c=rand()%1+5;
       base_ack*=c;
     }
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(sp_hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name()=="百万吨重拳")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name()=="聚宝功")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     } 
     _attcker->set_buff("聚宝功");
   }
   else if(sk->get_name()=="撞击")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     } 
   }
   else if(sk->get_name()=="火焰拳")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     } 
     int r = get_rand();
     if(r>=90)
     {
       _defender->set_stus("灼伤");
     }
   }
   else if(sk->get_name()=="冰冻拳")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r = get_rand();
     if(r>=90)
     {
       _defender->set_stus("冰冻",2);
     }
   }
   else if(sk->get_name()=="雷电拳")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r = get_rand();
     if(r>=90)
     {
       _defender->set_stus("麻痹");
     }
   }
   else if(sk->get_name()=="抓")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name()=="夹住")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name()=="断头钳")
   {
     if(_attcker->get_lv()<_defender->get_lv())
     {
      return;
     }
     sk->sub_cur_pp();
     int per = 100-_attcker->get_lv()+30-_defender->get_lv();
     int r =get_rand();
     if(r>=per)
     {
       _defender->sub_hp(_defender->get_cur_hp());
     }
   }
   else if(sk->get_name()=="旋风刀")
   {
     sk->sub_cur_pp();
     if(_attcker->in_buff("旋风刀"))
     {
       _attcker->remove_buff("旋风刀");
      _defender->sub_hp(base_ack*(sp_hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     else 
     {
       _attcker->set_buff("旋风刀");
     }
   }
   else if(sk->get_name()=="剑舞")
   {
     sk->sub_cur_pp();
     _attcker->add_ack_addtion(2);
   }
   else if(sk->get_name()=="居合斩")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name()=="起风")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        if(_defender->in_buff("飞翔"))
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro())*2);
        else 
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
  }
  else if(sk->get_name()=="翅膀攻击")
  {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
  }
  else if(sk->get_name()=="吹飞")
  {
    if(_defender->get_lv() > _attcker->get_lv())
    {
      return;
    }
    else 
    {
     sk->sub_cur_pp();
      _defender->set_buff("吹飞");
    }
  }
  else if(sk->get_name()=="飞翔")
  {
    if(_attcker->in_buff("飞翔"))
    {
       _attcker->remove_buff("飞翔");
       if(is_Hit(sk))
       {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
       }
    }
    else 
    {
        sk->sub_cur_pp();
        _attcker->set_buff("飞翔");
    }
  }
  else if(sk->get_name()=="绑紧")
  {
     sk->sub_cur_pp();

     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     } 
  }
  else if(sk->get_name()=="摔打")
  {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     } 
  }
  else if(sk->get_name()=="藤鞭")
  {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     } 
  }
  else if(sk->get_name()=="踩踏")
  {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     } 
  }
  else if(sk->get_name()=="二连踢")
  {
      sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     } 
  }
  else if(sk->get_name()=="百万吨重踢")
  {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
  }
  else if(sk->get_name()=="飞踢")
  {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
        _attcker->sub_hp(_attcker->get_cur_hp()/2);
     }
  }
  else if(sk->get_name()=="回旋踢")
  {
      sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r = get_rand();
     if(r>=75)
     {
       _defender->set_buff("畏惧");
     }
  }
  else  if(sk->get_name() == "泼沙")
  {
    sk->sub_cur_pp();
    if(_defender->in_buff("白雾"))
    {
      _defender->remove_buff("白雾");
    }
    else
    _defender->sub_hit_per(1);
  }
  else if(sk->get_name() == "头锤")
  {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r = get_rand();
     if(r>=70)
     {
       _defender->set_buff("畏缩");
     }
  }
  else if(sk->get_name() == "角撞")
  {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
  }
  else if(sk->get_name() == "乱击")
  {
     sk->sub_cur_pp();
     int r= get_rand();
     if(r>=60)
     {
       int c = rand()%1+2;
       base_ack*=c;
     }
     else if(r>=85)
     {
       int c=rand()%1+5;
       base_ack*=c;
     }
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(sp_hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
  }
  else if(sk->get_name() == "角钻")
  {
     if(_attcker->get_lv()<_defender->get_lv())
     {
      return;
     }
     sk->sub_cur_pp();
     int per = 100-_attcker->get_lv()+30-_defender->get_lv();
     int r =get_rand();
     if(r>=per)
     {
       _defender->sub_hp(_defender->get_cur_hp());
     }
  }
  else if(sk->get_name() == "撞击")
  {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
  }
  else if(sk->get_name() == "泰山压顶")
  {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r = get_rand();
     if(r>=70)
     {
       _defender->set_stus("麻痹");
     }
  }
  else if(sk->get_name() == "紧束" )
  {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     } 
     if(!_defender->in_buff("束缚"))
     {
       _defender->set_buff("束缚");
       _defender->set_buff("束缚");
       _defender->set_buff("束缚");
       _defender->set_buff("束缚");
     }
  }
  else if(sk->get_name() == "猛撞")
  {
      sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
        _attcker->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro())/4);
     }
  }
  else if(sk->get_name()== "大闹一番")
  {
    if(!is_player)
    {
    int r = _roles->get_pocket().size();
    _roles->get_pocket()[r].sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro())); 
    }
    else 
    {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
    }
    sk->sub_cur_pp();
    _attcker->set_buff("混乱");
  }
   else if(sk->get_name()=="舍身冲撞")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
        _attcker->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro())/4);
     }
   }
   else if(sk->get_name()=="摇尾巴")
   {
      sk->sub_cur_pp();
     if(is_Hit(sk))
     {
      if(_defender->in_buff("白雾"))
      {
       _defender->remove_buff("白雾");
      }
      else
      _defender->sub_def_addtion(1);
     }
   }
   else if(sk->get_name()=="毒针")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r = rand()%100;
     if(r>=70)
       _defender->set_buff("毒针");
   }
   else if(sk->get_name()=="双击")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(2*base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r = rand()%100;
     if(r>=80)
      _defender->set_stus("中毒");
   }
   else if(sk->get_name()=="飞弹针")
   {
     sk->sub_cur_pp();
     int r= get_rand();
     if(r>=60)
     {
       int c = rand()%1+2;
       base_ack*=c;
     }
     else if(r>=85)
     {
       int c=rand()%1+5;
       base_ack*=c;
     }
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name()=="瞪眼")
   {
      sk->sub_cur_pp();
    if(is_Hit(sk))
     {
      _defender->sub_def_addtion(1);
     }
   }
   else if(sk->get_name() == "咬住")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r = rand()%20;    
     if(r>=70)
       _defender->set_buff("畏惧");
   }
   else if(sk->get_name()== "叫声")
   {
      sk->sub_cur_pp();
      if(is_Hit(sk))
      {
      if(_defender->in_buff("白雾"))
      {
      _defender->remove_buff("白雾");
      }
      else
      _defender->sub_ack_addtion(1);
      }
   }
   else if(sk->get_name()=="吼叫")
   {
     if(_attcker->get_lv() > _defender -> get_lv())
       return;
     else 
     {
       sk->sub_cur_pp();
       _defender->set_buff("吼叫");
     }
   }
   else if(sk->get_name() == "唱歌")
   {
    sk->sub_cur_pp();
    if(is_Hit(sk))
    {
      _defender->set_stus("睡眠");
    }
   }
   else if(sk->get_name()=="超音波")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
       _defender->in_buff("混乱");
     }
   }
   else if(sk->get_name()=="音爆")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
       _defender->sub_hp(20);
     }
   }
   else if(sk->get_name()=="定身法")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
       _defender->get_last_use_Skill()->set_buff("定身法");
       _defender->get_last_use_Skill()->set_buff("定身法");
       _defender->get_last_use_Skill()->set_buff("定身法");
       _defender->get_last_use_Skill()->set_buff("定身法");
     }
   }
   else if(sk->get_name()=="溶解液")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r=get_rand();
     if(r>=90)
     {
       _defender->set_buff("溶解液");
     }
   }
   else if(sk->get_name()=="火花")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r = get_rand();
     if(r>=90)
     {
       _defender->set_stus("灼伤");
     }
   }
   else if(sk->get_name()=="喷射火焰")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r = get_rand();
     if(r>=90)
     {
       _defender->set_stus("灼伤");
     }
   }
   else if(sk->get_name() == "白雾")
   {
     sk->sub_cur_pp();
     _attcker->set_buff("白雾");
     _attcker->set_buff("白雾");
     _attcker->set_buff("白雾");
     _attcker->set_buff("白雾");
     _attcker->set_buff("白雾");
   }
   else if(sk->get_name()=="水枪")
   {
      sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name()=="水炮")
   {
       sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name()=="冲浪")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk)&&_defender->in_buff("潜水"))
     {
        _defender->sub_hp(2*base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name()=="冰冻光束")
   {
     sk->sub_cur_pp();
    if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
    int r= get_rand();
    if(r>=90)
    {
      _defender->set_stus("冰冻",2);
    }
   }
   else if(sk->get_name()=="暴风雪")
   {
    sk->sub_cur_pp();
    if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
    int r= get_rand();
    if(r>=90)
    {
      _defender->set_stus("冰冻",2);
    }
   }
   else if(sk->get_name()=="幻象光线")
   {
    sk->sub_cur_pp();
    if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
    int r= get_rand();
    if(r>=90)
    {
      _defender->set_buff("混乱");
    }
   }
   else if(sk->get_name()=="泡沫光线")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
    int r= get_rand();
    if(r>=90)
    {
      _defender->set_buff("泡沫光线");
    }
   }
   else if(sk->get_name()=="极光束")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
    int r= get_rand();
    if(r>=90)
    {
      if(_defender->in_buff("白雾"))
      {
        _defender->remove_buff("白雾");
      }
      else
      _defender->sub_ack_addtion(1);
    }
   }
   else if(sk->get_name()=="破坏光线")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
      _defender->set_buff("破坏光线");
   }
   else if(sk->get_name()=="啄")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name()=="啄钻")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name()=="地狱翻滚")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
        _attcker->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro())/4);
     }
   }
   else if(sk->get_name()=="踢倒")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
        _attcker->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro())/4);
     }
   }
   else if(sk->get_name()=="双倍奉还")
   {
     
   }
   else if(sk->get_name()=="地球上投")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(_defender->get_lv());
     }
   }
   else if(sk->get_name()=="怪力")
   {
      sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name()=="吸取")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
        _attcker->add_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro())/2);
     }
   }
   else if(sk->get_name() == "超级汲取")
   {
      sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
        _attcker->add_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro())/2);
     }
   }
   else if(sk->get_name() == "寄生种子")
   {
     vector<string>pro = _defender-> get_all_pro();
     bool is_can_hit = true;
     for(int i=0;i<pro.size();i++)
     {
       if(pro[i]=="草")
       {
        is_can_hit=false;
       }
     }
     if(is_can_hit)
     {
       _defender->set_buff("寄生种子");
       _attcker->set_buff("吸取寄生种子");
     }
   }
   else if(sk->get_name()=="生长")
   {
      sk->sub_cur_pp();
      _attcker->add_ack_addtion(1);
      _attcker->add_s_ack_addtion(1);
   }
   else if(sk->get_name()=="飞叶快刀")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(sp_hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name() == "日光束")
   {
     sk->sub_cur_pp();
     if(_attcker->in_buff("日光束")) 
     {
        _defender->sub_hp(base_ack*(sp_hit_main()?1.5:1)*pro_restant(sk->get_pro()));
        _attcker->remove_buff("日光束");
     }
     else 
     {
        _attcker->set_buff("日光束");
     }
   }
   else if(sk->get_name() == "毒粉")
   {
     sk->sub_cur_pp(); 
     if(_defender->in_pro("草"))
     {
       return;
     }
     else 
     {
       if(is_Hit(sk))
       _defender->set_stus("中毒");
     }
   }
   else if(sk->get_name()== "麻痹粉")
   {
    sk->sub_cur_pp(); 
     if(_defender->in_pro("草"))
     {
       return;
     }
     else 
     {
       if(is_Hit(sk))
       _defender->set_stus("麻痹");
     }
   }
   else if(sk->get_name() == "催眠粉")
   {
     sk->sub_cur_pp(); 
     if(_defender->in_pro("草"))
     {
       return;
     }
     else 
     {
       if(is_Hit(sk))
       _defender->set_stus("睡眠");
     }
   }
   else if(sk->get_name()=="花瓣舞")
   {
    sk->sub_cur_pp();
    if(is_Hit(sk))
    {
       _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
    } 
   }
   else if(sk->get_name() =="吐丝" )
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
       _defender->set_buff("吐丝");
     }
   }
   else if(sk->get_name()== "龙之怒")
   {
      sk->sub_cur_pp();
      if(is_Hit(sk))
      {
        _defender->sub_hp(40);
      }
   }
   else if(sk->get_name()=="火之漩涡")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
       _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     _defender->set_buff("束缚");
   }
   else if(sk->get_name()=="电击")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
       _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r=get_rand();
     if(r>=90)
     _defender->set_stus("麻痹");
   }
   else if(sk->get_name() == "十万福特")
   {
      sk->sub_cur_pp();
     if(is_Hit(sk))
     {
       _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r=get_rand();
     if(r>=90)
     _defender->set_stus("麻痹");
   }
   else if(sk->get_name() == "电磁波")
   {
      sk->sub_cur_pp();
      vector<string>pro= _defender->get_all_pro();
      for(int i=0;i<pro.size() ; i++ )
      {
        if(pro[i]=="地面")
        {
          _defender->set_stus("麻痹");
        }
      }
   }
   else if(sk->get_name() == "打雷")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
       _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r=get_rand();
     if(r>=70)
     _defender->set_stus("麻痹");
   }
   else if(sk->get_name()=="打雷")
   {
     sk->sub_cur_pp();
    if(is_Hit(sk))
    {
    if(is_player)
    {
      for(int i=0;i<_roles->get_pocket().size();i++)
      {
         _roles->get_pocket()[i].sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));     
      }
    }
    else 
    {
      for(int i=0;i<_wild->get_pocket().size();i++)
      {
         _wild->get_pocket()[i].sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));     
      }
    }
    }
   }
   else if(sk->get_name() == "地裂")
   {
     sk->sub_cur_pp();
      _defender->sub_hp(_defender->get_cur_hp() * pro_restant(sk->get_pro()));
   }
   else if(sk->get_name() == "挖洞")
   {
     if(_attcker->in_buff("挖洞"))
     {
     if(is_Hit(sk))
     {
       _attcker->remove_buff("挖洞");
       _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     }
     else 
     {
       sk->sub_cur_pp();
       _attcker->set_buff("挖洞");
     }
   }
   else if(sk->get_name()=="剧毒")
   {
     sk->sub_cur_pp();
     vector<string>pro = _attcker->get_all_pro();
     for(int i=0;i<pro.size();i++)
     {
       if(pro[i]=="毒")
       {
         _defender->set_stus("中毒");
         return;
       }
     }
     if(is_Hit(sk))
     {
      _defender->set_stus("中毒");
     }
   }
   else if(sk->get_name() == "念力")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
       _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r=get_rand();
     if(r>=90)
     {
       _defender->set_stus("麻痹");
     }
   }
   else if(sk->get_name() == "精神强念")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
       _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r = get_rand();
     if(r>=90)
     {
       if(_defender->in_buff("白雾"))
       {
          _defender->remove_buff("白雾");
       }
       else 
       {
         _defender->sub_s_def_addtion(1);
       }
     }
   }
   else if(sk->get_name() == "催眠术")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
       _defender->set_stus("睡眠");
     }
   }
   else if(sk->get_name() == "瑜伽姿势")
   {
     sk->sub_cur_pp();
     _attcker->add_ack_addtion(1);
   }
   else if(sk->get_name() == "高速移动")
   {
    sk->sub_cur_pp();
    _attcker->set_buff("高速移动");
   }
   else if(sk->get_name() == "电光一闪")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
       _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name() == "愤怒")
   {
    sk->sub_cur_pp();
    if(is_Hit(sk))
    {
    _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
    }
   }
   else if(sk->get_name() == "瞬间移动")
   {
     if(is_player)
       _attcker->set_buff("瞬间移动");
   }
   else if(sk->get_name()== "黑夜魔影")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
     _defender->sub_hp(_defender->get_lv());
     }
   }
   else if(sk->get_name() == "刺耳声")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
       _defender->sub_def_addtion(2);
     }
   }
   else if(sk->get_name() == "影子分身")
   {
     sk->sub_cur_pp();
     _attcker->add_dodge_per(1);
   }
   else if(sk->get_name() == "自我再生")
   {
     sk->sub_cur_pp();
     _attcker->add_hp(_attcker->get_max_hp()/2);
   }
   else if(sk->get_name() == "变硬")
   {
     sk->sub_cur_pp();
     _attcker->add_def_addtion(1);
   }
   else if(sk->get_name() == "变小")
   {
    sk->sub_cur_pp();
    _attcker->add_dodge_per(1);
   }
   else if(sk->get_name() == "烟幕")
   {
    sk->sub_cur_pp();
    if(_defender->in_buff("白雾"))
    {
      _defender->remove_buff("白雾");
    }
    else
    _defender->sub_hit_per(1);
   }
   else if(sk->get_name() == "奇异之光")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
       _defender->set_buff("混乱");
     }
   }
   else if(sk->get_name()=="缩入壳中")
   {
     sk->sub_cur_pp();
     _attcker->add_def_addtion(1);
   } 
   else if(sk->get_name() == "变圆")
   {
     sk->sub_cur_pp();
     _attcker->add_def_addtion(1);
   }
   else if(sk->get_name() == "屏障")
   {
     sk->sub_cur_pp();
     _attcker->add_def_addtion(2);
   }
   else if(sk->get_name() == "光墙")
   {
    _defender->set_buff("光墙"); 
    _defender->set_buff("光墙"); 
    _defender->set_buff("光墙"); 
    _defender->set_buff("光墙"); 
    _defender->set_buff("光墙"); 
   }
   else if(sk->get_name() == "黑雾")
   {
     sk->sub_cur_pp();
     for(int i=0;i<_roles->get_pocket().size();i++)
     {
       _roles->get_pocket()[i].restore_addtion();
       _roles->get_pocket()[i].restroe_hit_dodge_lv();
     }
     for(int i=0;i<_wild->get_pocket().size();i++)
     {
       _wild->get_pocket()[i].restore_addtion();
       _wild->get_pocket()[i].restroe_hit_dodge_lv();
     }
   }
   else if(sk->get_name() == "反射壁")
   {
   }
   else if(sk->get_name() == "聚气")
   {
     sk->sub_cur_pp();
     _defender->set_buff("易中要害");
   }
   else if(sk->get_name()=="忍耐")
   {
     _attcker->set_buff("忍耐");
   }
   else if(sk->get_name() == "指挥")
   {
   }
   else if(sk->get_name() == "自爆")
   {
     _attcker->sub_hp(_attcker->get_cur_hp());
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
    _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name() == "炸蛋")
   {
    sk->sub_cur_pp();
     if(is_Hit(sk))
     {
    _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name() == "舌舔")
   {
    sk->sub_cur_pp();
     if(is_Hit(sk))
     {
    _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r = get_rand();
     if(r>=70)
     {
       _defender->set_stus("麻痹");
     }
   }
   else if(sk->get_name() == "浊雾")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
    _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r = get_rand();
     if(r>=60)
     {
       _defender->set_stus("中毒");
     }
   }
   else if(sk->get_name() == "污泥攻击")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
    _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r = get_rand();
     if(r>=70)
     {
       _defender->set_stus("中毒");
     }
   }
   else if(sk->get_name() == "鼓棒")
   {
      sk->sub_cur_pp();
     if(is_Hit(sk))
     {
    _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r = get_rand();
     if(r>=90)
     {
       _defender->set_buff("畏缩");
     }
   }
   else if(sk->get_name() == "大字爆炎")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
    _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r = get_rand();
     if(r>=90)
     {
       _defender->set_stus("灼伤");
     }
   }
   else if(sk->get_name() == "攀爆")
   {
    sk->sub_cur_pp();
     if(is_Hit(sk))
     {
    _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r = get_rand();
     if(r>=80)
     {
       _defender->set_buff("畏缩");
     }
   }
   else if(sk->get_name() == "贝壳夹击")
   {
     _defender->set_buff("束缚");
     _defender->set_buff("束缚");
     _defender->set_buff("束缚");
   }
   else if(sk->get_name() == "高速星星")
   {
     sk->sub_cur_pp();
    _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
   }
   else if(sk->get_name() == "火箭头锤")
   {
    if(!_attcker->in_buff("火箭头锤"))
    {
    sk->sub_cur_pp();
    _attcker->add_def_addtion(1);
    }
    else 
    {
      sk->sub_cur_pp();
      _attcker->remove_buff("火箭头锤");
      _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
    }
   }
   else if(sk->get_name() == "尖刺加农炮")
   {
     sk->sub_cur_pp();
     int r= get_rand();
     if(r>=60)
     {
       int c = rand()%1+2;
       base_ack*=c;
     }
     else if(r>=85)
     {
       int c=rand()%1+4;
       base_ack*=c;
     }
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(sp_hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name() == "缠绕")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
    _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r = get_rand();
     if(r>=90)
     {
       _defender->set_buff("缠绕");
     }
   }
   else if(sk->get_name() == "瞬间失忆")
   {
     sk->sub_cur_pp();
      _defender->set_buff("瞬间失忆");
   }
   else if(sk->get_name() == "折弯钥匙")
   {
     sk->sub_cur_pp();
     if(_defender->in_buff("白雾"))
     {
       _defender->remove_buff("白雾");
     }
     else 
     {
     _defender->sub_hit_per(1);
     }
   }
   else if(sk->get_name() == "生蛋")
   {
     sk->sub_cur_pp();
     _attcker->add_hp(_attcker->get_max_hp()/2);
   }
   else if(sk->get_name() == "飞膝踢")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
    _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     else 
     {
       _attcker->sub_hp(_attcker->get_max_hp()/2);
     }
   }
   else if(sk->get_name() == "大蛇瞪眼")
   {
     sk->sub_cur_pp();
     _defender->set_stus("麻痹");
   }
   else if(sk->get_name() == "食梦")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
    _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
    _attcker->add_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro())/2);
     }
   }
   else if(sk->get_name() == "毒瓦斯")
   {
     sk->sub_cur_pp();
     _defender->set_stus("中毒");
   }
   else if(sk->get_name() == "投球")
   {
     sk->sub_cur_pp();
     int r= get_rand();
     if(r>=77)
     {
       int c = rand()%1+2;
       base_ack*=c;
     }
     else if(r>=85)
     {
       int c=rand()%1+4;
       base_ack*=c;
     }
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(sp_hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name() == "吸血")
   {
    sk->sub_cur_pp();
     if(is_Hit(sk))
     {
    _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
    _attcker->add_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro())/2);
     }
   }
   else if(sk->get_name() == "恶魔之吻")
   {
     sk->sub_cur_pp();
     _defender->set_stus("睡眠");
   }
   else if(sk->get_name() == "神鸟猛击")
   {
     if(_attcker->in_buff("神鸟猛击"))
     {
     _attcker->remove_buff("神鸟猛击");
     if(is_Hit(sk))
     {
       _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }  
     }
     else 
     {
     if(is_Hit(sk))
     {
       sk->sub_cur_pp();
       _defender->set_buff("神鸟猛击");
     } 
     }
   }
   else if(sk->get_name() == "变身")
   {
     sk->sub_cur_pp();
     _attcker->in_buff("变身");
   }
   else if(sk->get_name() == "泡沫")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
       _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     } 
     _defender->set_buff("泡沫");
   }
   else if(sk->get_name() == "迷昏拳")
   {
     sk->sub_cur_pp();
   if(is_Hit(sk))
     {
       _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     } 
     int r = get_rand();
     if(r>=80)
     {
       _defender->set_buff("混乱");
     } 
   }
   else if(sk->get_name() == "蘑菇孢子")
   {
     vector<string> pro = _defender->get_all_pro();
     for(int i =0 ;i<pro.size() ;++i)
     {
       if(pro[i]=="草")
       {
          return;
       }
     }
     _defender->set_buff("草");
   }
   else if(sk->get_name() == "闪光")
   {
     sk->sub_cur_pp();
     if(_defender->in_buff("白雾"))
     {
       _defender->remove_buff("白雾");
     }
     else
     _defender->sub_hit_per(1);
   }
   else if(sk->get_name() == "精神波")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
       int r = get_rand()/100;
       _defender->sub_hp((double)(r+0.5)*_attcker->get_lv());
     }
   }
   else if(sk->get_name() == "跃起")
   {
     return;
   }
   else if(sk->get_name() == "溶化")
   {
     sk->sub_cur_pp();
      _attcker->add_def_addtion(2);
   }
   else if(sk->get_name() == "蟹钳锤")
   {
    sk->sub_cur_pp();
    if(is_Hit(sk))
    _defender->sub_hp(base_ack*(sp_hit_main()?1.5:1)*pro_restant(sk->get_pro()));
   }
   else if(sk->get_name() == "大爆炸")
   {
     _attcker->sub_hp(_attcker->get_cur_hp());
     if(is_Hit(sk))
     {
    _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name() == "乱抓")
   {
     sk->sub_cur_pp();
     int r= get_rand();
     if(r>=77)
     {
       int c = rand()%1+2;
       base_ack*=c;
     }
     else if(r>=85)
     {
       int c=rand()%1+4;
       base_ack*=c;
     }
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(sp_hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   } 
   else if(sk->get_name() == "骨头回力镖")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(sp_hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(sp_hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name() == "睡觉")
   {
     sk->sub_cur_pp();
     _attcker->add_hp(_attcker->get_max_hp());
     _attcker->set_stus("睡眠");
     _attcker->set_stus("睡眠");
   }
   else if(sk->get_name() == "岩崩")
   {
    sk->sub_cur_pp();
    if(is_Hit(sk))
    {
      _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
    }
    int r =get_rand();
    if(r>=70)
    {
      _defender->set_buff("畏缩");
    }
   }
   else if(sk->get_name() == "必杀门牙")
   {
    sk->sub_cur_pp();
    if(is_Hit(sk))
    {
      _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
    }
    int r =get_rand();
    if(r>=70)
    {
      _defender->set_buff("畏缩");
    }
   }
   else if(sk->get_name() == "棱角化")
   {
   sk->sub_cur_pp();
   _attcker->add_ack_addtion(1);
   }
   else if(sk->get_name() == "三重攻击")
   {
   sk->sub_cur_pp();
    if(is_Hit(sk))
    {
      _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
    }
    int r = rand()%3;
    if(r==0)
    {
    _defender->set_stus("灼伤");
    }
    else if(r==1)
    {
    _defender->set_stus("冰冻",2);
    }
    if(r==2)
    {
    _defender->set_stus("麻痹");
    }
   }
   else if(sk->get_name() == "愤怒门牙")
   {
    sk->sub_cur_pp();
    if(is_Hit(sk))
    {
      int s = _defender->get_cur_hp()/2;
      if(s<1)
      s=1;
      _defender->sub_hp(s);
    }
   }
   else if(sk->get_name() == "劈开")
   {
    sk->sub_cur_pp();
    if(is_Hit(sk))
    {
      _defender->sub_hp(base_ack*(sp_hit_main()?1.5:1)*pro_restant(sk->get_pro()));
    }
   }
   else if(sk->get_name() == "挣扎")
   {
    sk->sub_cur_pp();
    if(is_Hit(sk))
    {
      _defender->sub_hp(base_ack*(sp_hit_main()?1.5:1)*pro_restant(sk->get_pro()));
      _attcker->sub_hp(base_ack*(sp_hit_main()?1.5:1)*pro_restant(sk->get_pro())/4);
    }
   }
   return;
}
double fight_Sys::pro_restant(string s)
{
  vector<string>pro = _defender->get_all_pro();
  if(pro.size()==1)
  {
    return restrant(s,pro[0]);
  }
  else 
  {
    return restrant(s,pro[0])*restrant(s,pro[1]);
  }
}
