#pragma once

#include <LangtonAnts/core/Ant.hpp>
#include <LangtonAnts/core/Grid.hpp>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_video.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <vector>

namespace JJ0o0::LangtonAnts {
class App {
public:
  App(const char *title, int width, int height);
  ~App();

  void run();

private:
  SDL_Window *m_window;
  SDL_Renderer *m_renderer;
  TTF_Font *m_font;

  Uint64 m_last;

  Grid m_grid;
  std::vector<Ant> m_ants;

  int m_width, m_height, m_generation;
  float m_deltatime, m_accumulator, m_interval;
  bool m_running, m_paused;

  void update();
  void render();
  void handleEvents(const SDL_Event &event);
};
} // namespace JJ0o0::LangtonAnts