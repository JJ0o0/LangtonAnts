#include <LangtonAnts/core/Ant.hpp>
#include <LangtonAnts/utilities/Colors.hpp>

namespace JJ0o0::LangtonAnts {
Ant::Ant(int x, int y) : x(x), y(y), direction(Utils::Direction::North) {}

void Ant::step(Grid &grid) {
  bool cell = grid.getCell(x, y);

  if (cell) {
    direction =
        static_cast<Utils::Direction>((static_cast<int>(direction) + 1) % 4);
  } else {
    direction =
        static_cast<Utils::Direction>((static_cast<int>(direction) + 3) % 4);
  }

  grid.setCell(x, y, !cell);

  switch (direction) {
  case Utils::Direction::North:
    y--;
    break;
  case Utils::Direction::East:
    x++;
    break;
  case Utils::Direction::South:
    y++;
    break;
  case Utils::Direction::West:
    x--;
    break;
  }

  x = ((x % grid.getWidth()) + grid.getWidth()) % grid.getWidth();
  y = ((y % grid.getHeight()) + grid.getHeight()) % grid.getHeight();
}

void Ant::render(SDL_Renderer *renderer, int gridWidth, int gridHeight,
                 int screenWidth, int screenHeight, int cellSize) const {
  float offsetX = (screenWidth - gridWidth * cellSize) / 2.0f;
  float offsetY = (screenHeight - gridHeight * cellSize) / 2.0f;

  SDL_FRect ant = {x * cellSize + offsetX, y * cellSize + offsetY,
                   (float)cellSize, (float)cellSize};

  SDL_SetRenderDrawColor(renderer, Colors::ANT_COLOR.r, Colors::ANT_COLOR.g,
                         Colors::ANT_COLOR.b, Colors::ANT_COLOR.a);
  SDL_RenderFillRect(renderer, &ant);
}

} // namespace JJ0o0::LangtonAnts