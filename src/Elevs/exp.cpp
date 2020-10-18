#include"../../include/Elevs/exp.h"
int Exp::get_lv()
{
  return lv;
}
bool Exp::add_exp(int x)
{
  if(lv==100)
    return false;
  cur_exp+=x;
  if(cur_exp>exp_table[level][99])
    cur_exp=exp_table[level][99];
  updata_lv();
  return true;
}
bool Exp::updata_lv()
{
   if(lv==100)
     return false;
   int i;
   for(i=1;i<=100;i++)
   {
     if(exp_table[level][i-1]>=cur_exp)
     {
        break;
     }
   }
   lv=i;
   return true;
}
bool Exp::is_full_lv()
{
  return lv==100;
}
void Exp::init_exp(int c)
{
  cur_exp=c;
  updata_lv();
}
void Exp::set_exp_lever(string s)
{
    level = s;
    read_file();
}

void Exp::read_file()
{
  Json::Value root; 
  Json::Reader reader;
  ifstream in("../../resource/exp_lever.json",ios::binary);
  if(!in.is_open())
  {
   cerr << "open file err"<<endl; 
   exit(-1);
  }
  if(reader.parse(in,root))
  {
    for(int i=0;i<100;i++)
    {
      exp_table[level].push_back(root[level][i].asInt());
    }
  }
  else 
  {
    cerr << "json reader err " <<endl;
    exit(-1);
  }
  in.close();
}
