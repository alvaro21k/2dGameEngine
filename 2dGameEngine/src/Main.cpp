#include "./Game/Game.h"
#include "sol/sol.hpp"
#include <iostream>

void TestLua(){
    sol::state lua;
    lua.open_libraries(sol::lib::base);

    lua.script_file("./assets/scripts/myscript.lua");
    

    int someVariableInsideCpp = lua["some_variable"];
    std::cout << "The valuable of some_variable in C++ is " << someVariableInsideCpp << std::endl;

    bool isFullScreen = lua["config"]["fullscreen"];
}

int main(int argc, char* argv[]) {
    // TODO
    /*Game game;

    game.Initialize();
   
    game.Run();

    game.Destroy();*/

    TestLua();
    return 0;
}