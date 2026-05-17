#include "LangtonAnts/utilities/Utils.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <LangtonAnts/core/App.hpp>
#include <LangtonAnts/utilities/Colors.hpp>
#include <LangtonAnts/utilities/UI.hpp>
#include <algorithm>

namespace JJ0o0::LangtonAnts {
App::App(const char *title, int width, int height)
    : m_width(width), m_height(height), m_running(true), m_paused(false),
      m_accumulator(0.0f), m_interval(0.01f), m_generation(0),
      m_grid(width / 10, height / 10, 10) {
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();

  m_window = SDL_CreateWindow(title, width, height, 0);
  m_renderer = SDL_CreateRenderer(m_window, NULL);
  m_font = TTF_OpenFont("assets/fonts/FiraCode-Regular.ttf", 16);
}

App::~App() {
  SDL_DestroyRenderer(m_renderer);
  SDL_DestroyWindow(m_window);
  TTF_Quit();
  SDL_Quit();
}

void App::run() {
  SDL_Event event;

  m_last = SDL_GetTicks();
  while (m_running) {
    while (SDL_PollEvent(&event)) {
      handleEvents(event);
    }

    update();

    SDL_SetRenderDrawColor(m_renderer, Colors::BACKGROUND.r,
                           Colors::BACKGROUND.g, Colors::BACKGROUND.b,
                           Colors::BACKGROUND.a);
    SDL_RenderClear(m_renderer);

    render();

    SDL_RenderPresent(m_renderer);
  }
}

void App::update() {
  Uint64 now = SDL_GetTicks();
  m_deltatime = (now - m_last) / 1000.0f;
  m_last = now;

  if (m_paused || m_ants.empty())
    return;

  m_accumulator += m_deltatime;

  if (m_accumulator >= m_interval) {
    for (auto &ant : m_ants)
      ant.step(m_grid);

    m_accumulator = 0.0f;
    m_generation++;
  }
}

void App::render() {
  m_grid.render(m_renderer, m_width, m_height);

  for (auto &ant : m_ants)
    ant.render(m_renderer, m_grid.getWidth(), m_grid.getHeight(), m_width,
               m_height, 10);

  std::string speedText =
      "speed: " + Utils::FloatToString(1.0f / m_interval, 0) + " steps/s";
  auto speedTextSize = UI::getTextSize(m_font, speedText);
  UI::renderText(m_renderer, m_font, speedText,
                 m_width - speedTextSize.first - 10,
                 m_height - speedTextSize.second - 50, Colors::TEXT);

  std::string generationText =
      "generation: " + Utils::IntToString(m_generation);
  auto generationTextSize = UI::getTextSize(m_font, generationText);
  UI::renderText(m_renderer, m_font, generationText,
                 m_width - generationTextSize.first - 10,
                 m_height - generationTextSize.second - 30, Colors::TEXT);

  std::string pausedText = m_paused ? "paused" : "running";
  auto pausedTextSize = UI::getTextSize(m_font, pausedText);
  UI::renderText(m_renderer, m_font, pausedText,
                 m_width - pausedTextSize.first - 10,
                 m_height - pausedTextSize.second - 10, Colors::TEXT);
}

void App::handleEvents(const SDL_Event &event) {
  switch (event.type) {
  case SDL_EVENT_QUIT:
    m_running = false;
    break;
  case SDL_EVENT_KEY_DOWN:
    if (event.key.scancode == SDL_SCANCODE_ESCAPE) {
      m_running = false;
    } else if (event.key.scancode == SDL_SCANCODE_SPACE) {
      m_paused = !m_paused;
    } else if (event.key.scancode == SDL_SCANCODE_R) {
      m_ants.clear();
      m_grid = Grid(m_width / 10, m_height / 10, 10);
      m_generation = 0;
    } else if (event.key.scancode == SDL_SCANCODE_M) {
      m_interval = std::max(0.001f, m_interval - 0.005f);
    } else if (event.key.scancode == SDL_SCANCODE_N) {
      m_interval += 0.005f;
    }

    break;
  case SDL_EVENT_MOUSE_BUTTON_DOWN: {
    if (event.button.button == SDL_BUTTON_LEFT) {
      float offsetX = (m_width - m_grid.getWidth() * 10) / 2.0f;
      float offsetY = (m_height - m_grid.getHeight() * 10) / 2.0f;

      int gridX = (event.button.x - offsetX) / 10;
      int gridY = (event.button.y - offsetY) / 10;

      if (gridX >= 0 && gridX < m_grid.getWidth() && gridY >= 0 &&
          gridY < m_grid.getHeight()) {
        bool occupied =
            std::any_of(m_ants.begin(), m_ants.end(), [&](const Ant &a) {
              return a.x == gridX && a.y == gridY;
            });

        if (occupied)
          m_ants.erase(std::remove_if(m_ants.begin(), m_ants.end(),
                                      [&](const Ant &a) {
                                        return a.x == gridX && a.y == gridY;
                                      }),
                       m_ants.end());
        else
          m_ants.push_back(Ant(gridX, gridY));
      }
    }
    break;
  }
  }
}

} // namespace JJ0o0::LangtonAnts