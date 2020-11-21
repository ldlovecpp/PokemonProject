#pragma  once
#include"../Roles/roles.h"
#include<unordered_map>
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<jsoncpp/json/json.h>
using namespace std;
struct Arc_Info
{
  string name;
  string introduce;
  int price;
};
class Store 
{
public:
  Store(Roles* rols);
private:
  //读取物品信息
  void read_file();
public:
  //选择物品
  void choice_arc();
private:
  //购买物品
  void buy_arc(string name);  
private:
  vector<Arc_Info>info;
  Roles* _roles;
};

