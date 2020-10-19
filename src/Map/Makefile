.PHONY: clean
game : ../Elevs/elevs.cpp ../Elevs/Ablity.cpp ../Elevs/exp.cpp ../Arc/arc.cpp ../fight/fight_Sys.cpp ../fight/pro_restant.cpp ../Map/map.cpp ../Map/keyboard.cpp ../PVW/pvw.cpp ../Roles/role.cpp ../Skill/skill.cpp ../Skill/pp.cpp ../Store/stroe.cpp main.cpp
	g++ -std=c++11 $^ -L. -ljsoncpp -ogame
clean:
	rm -rf game
