#pragma once

#include <LangtonAnts/core/Grid.hpp>
#include <LangtonAnts/utilities/Utils.hpp>

#include <SDL3/SDL_render.h>

namespace JJ0o0::LangtonAnts {
struct Ant {
  int x, y;
  Utils::Direction direction = Utils::Direction::West;

  Ant(const Grid &grid);
  void step(Grid &grid);
  void render(SDL_Renderer *renderer, int gridWidth, int gridHeight,
              int screenWidth, int screenHeight, int cellSize) const;
};
} // namespace JJ0o0::LangtonAnts