#include <iostream>
#include "lua.hpp"

void report_errors(lua_State *L, int status) {
  if (status != 0) {
    std::cerr << "-- " << lua_tostring(L, 1) << std::endl;
    lua_pop(L, 1);
  }
}

lua_State* launch_lua() {
  lua_State *L = lua_open();
  luaL_openlibs(L);
  return L;
}

int dhmd_num_particles = 0;
int get_num_particles(lua_State *L) {
  int argc = lua_gettop(L);
  lua_pushnumber(L, dhmd_num_particles);
  return 1;
}

int add_particle(lua_State *L) {
  dhmd_num_particles++;
  return 0;
}

void run_lua_file(lua_State* L, char* filename) {
  std::cerr << "-- Loading Lua file: " << filename << std::endl;

  int s = luaL_loadfile(L, filename);

  if (s == 0) {
    s = lua_pcall(L, 0, LUA_MULTRET, 0);
  }

  report_errors(L, s);
  std::cerr << std::endl;
}

void end_lua(lua_State* L) {
  lua_close(L);
}
  

int main(int argc, char** argv) {
  lua_State* L = launch_lua();
  lua_register(L, "get_num_particles", get_num_particles);
  lua_register(L, "add_particle", add_particle);
  run_lua_file(L, argv[1]);
  end_lua(L);
  return 0;
}
