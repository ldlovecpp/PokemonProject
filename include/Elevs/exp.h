#pragma once
#include<iostream>
#include<jsoncpp/json/json.h>
#include<fstream>
#include<string>
#include<vector>
#include<unordered_map>
using namespace std;
class Exp
{
public:
  int get_lv();
  bool add_exp(int x);
  bool is_full_lv();
  void init_exp(int c);
  void set_exp_lever(string l);
private:
  bool updata_lv();
  void read_file();
private:
  int lv;
  int cur_exp;
  int full_exp;
  string level;
  unordered_map<string,vector<int>>exp_table; 
};
