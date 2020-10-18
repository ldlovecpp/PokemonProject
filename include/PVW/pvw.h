#include"../Roles/roles.h"
#include"../fight_Sys/fight_Sys.h"
#include"../Arc/arc.h"
#include<unistd.h>
#include<stdlib.h>
class Player_Vs_Wild
{
public:
Player_Vs_Wild(Roles* role,Roles* wild,bool triner = false)
  :_role(role)
   ,_wild(wild)
   ,is_triner(triner)
  {}
Elevs* change_player_elevs();
void dis_play(Elevs* elvs,Elevs* elvs2);
void Fight();
bool talk_with_player(Elevs*& player);
bool wild_is_die();
void deal_success_info();
void deal_fail_info();
bool role_is_die();
void deal_player_buff();
void deal_wild_buff();
bool is_Roar();
void player_ack_wild(Elevs* player,Elevs* wild);
void wild_ack_player(Elevs* player,Elevs* wild);
bool player_fist_hit(Elevs* player,Elevs* wild);
bool deal_arc();
void remove_all_buff();
bool attaker_can_use_skill(Elevs* elvs);
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
