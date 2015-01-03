#include <iostream>
#include <vector>
#include "lua.hpp"

struct Particle {
  float x;
  float y;
  float z;
  float mass;
};

class ParticleEnsemble {
    std::vector<Particle>* particle_storage;
  public:
    ParticleEnsemble();
    void addParticle(Particle p);
    int numParticles();
};
ParticleEnsemble* gpe; //Global Particle Ensemble

ParticleEnsemble::ParticleEnsemble() {
  particle_storage = new std::vector<Particle>();
}

void ParticleEnsemble::addParticle(Particle p) {
  particle_storage->push_back(p);
}

int ParticleEnsemble::numParticles() {
  return particle_storage->size();
}

void report_errors(lua_State *L, int status) {
  if (status != 0) {
    std::cerr << "-- " << lua_tostring(L, 1) << std::endl;
    lua_pop(L, 1);
  }
}

lua_State* launch_lua() {
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);
  return L;
}

int get_num_particles(lua_State *L) {
  int argc = lua_gettop(L);
  lua_pushnumber(L, gpe->numParticles());
  return 1;
}

int initialize_particle_ensemble(lua_State *L) {
  gpe = new ParticleEnsemble();
  return 0;
}

int add_particle(lua_State *L) {
  int argc = lua_gettop(L);
  Particle p;
  if (argc >= 1) { p.x = lua_tonumber(L, 1); lua_pop(L, 1); }
  if (argc >= 2) { p.y = lua_tonumber(L, 1); lua_pop(L, 1); }
  if (argc >= 3) { p.z = lua_tonumber(L, 1); lua_pop(L, 1); }
  
  gpe->addParticle(p);
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
  lua_register(L, "initialize_particle_ensemble",initialize_particle_ensemble);
  run_lua_file(L, argv[1]);
  end_lua(L);
  return 0;
}
