#include<unistd.h>
int main()
{
   chdir("./src/Map/");
   execl("game.sh",NULL);
}
