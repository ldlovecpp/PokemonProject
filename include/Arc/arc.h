#include<unordered_map>
#include<string>
#include"../Roles/roles.h"
using namespace std;
class Arc
{
public:
  Arc(Roles* ros,Elevs* to_catch=nullptr)
    :_roles(ros),
    catch_elevs(to_catch)
  {}
public:
  //处理物品的总接口
  bool deal_arc(string name);
  //处理捕获型物品(精灵球)
  bool deal_catch(string name);
  //处理其他的物品(比如增加属性型的技能)
  void deal_other(string name);
  // 选择精灵
  Elevs* choice_elevs();
  //选择精灵(用的物品是未技能回复pp值的)
  Skill* choice_skill(Elevs* elvs);
private:
  //当前所要使用物品的角色
 Roles* _roles; 
 //当前要对哪个精灵施加药品
 Elevs* catch_elevs;
};
