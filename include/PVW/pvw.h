#include"../Roles/roles.h"
#include"../fight_Sys/fight_Sys.h"
#include"../Arc/arc.h"
#include<unistd.h>
#include<stdlib.h>
//对战的逻辑

class Player_Vs_Wild
{
public:
Player_Vs_Wild(Roles* role,Roles* wild,bool triner = false)
  :_role(role)
   ,_wild(wild)
   ,is_triner(triner)
  {}
// 更换当前对战精灵
Elevs* change_player_elevs();
//打印对战双方的信息
void dis_play(Elevs* elvs,Elevs* elvs2);
//对战
void Fight();
//与玩家进行交互(是否要更换精灵,使用药剂)
bool talk_with_player(Elevs*& player);
//判断野怪/训练师是否死亡
bool wild_is_die();
//处理胜利的信息
void deal_success_info();
//处理失败的信息
void deal_fail_info();
//判断玩家是否死亡
bool role_is_die();
//处理玩家身上的部分技能buff
void deal_player_buff();
//处理野怪身上的部分buff
void deal_wild_buff();
bool is_Roar();
//玩家对野怪造成伤害
void player_ack_wild(Elevs* player,Elevs* wild);
//野怪对玩家造成伤害
void wild_ack_player(Elevs* player,Elevs* wild);
//玩家是否率先出击
bool player_fist_hit(Elevs* player,Elevs* wild);
//处理使用物品信息
bool deal_arc();
//移除玩家身上的所用异常buff
void remove_all_buff();
//判断玩家是否可以使用技能j
bool attaker_can_use_skill(Elevs* elvs);
//改变野怪的场上精灵
Elevs* change_wild_elevs();
void deal_buff_in_end_type(Roles* role);
bool player_have_other_elevs();
bool wild_have_other_elevs();
bool player_have_save_arc();
bool player_use_save_arc(Elevs* player);
bool player_can_hit(Elevs* player);
bool wild_can_hit(Elevs* wild);
private:
 Roles* _role;
 Roles* _wild;
 bool is_triner;
};
