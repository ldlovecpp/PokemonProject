#include"../../include/Map/map.h"
void meau()
{
  system("clear");
  cout << "你好,欢迎来到激烈的宝可梦世界!!"<<endl; 
  sleep(3);
  system("clear");
  cout<<  "###################################游戏提示#######################################" <<endl;
  cout << "#'训'代表训练师                                                                  #" <<endl;
  cout << "#'草'代表野生宝可梦的地点!!                                                      #" <<endl;
  cout << "#'商'代表商店,你可以在商店里边找到售台来买物品                                   #" <<endl;
  cout << "#'路'代表玩家可以在其上移动                                                      #" <<endl;
  cout << "#'树'或者'墙'代表障碍物,玩家不可在其上移动                                       #" <<endl;
  cout << "#'W':上                                                                          #" <<endl;
  cout << "#'S':下                                                                          #" <<endl;
  cout << "#'A':左                                                                          #" <<endl;
  cout << "#'D':右                                                                          #" <<endl;
  cout << "##################################################################################" <<endl;
  sleep(10);
}
int main()
{
  meau();
  Roles ros;
  ros.add_Elevs("皮卡丘");
  Game game(&ros);
  game.create_map();
  game.run();
  return 0;
}
