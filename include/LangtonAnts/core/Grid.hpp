#pragma once

#include <SDL3/SDL_render.h>
#include <vector>

namespace JJ0o0::LangtonAnts {
class Grid {
public:
  Grid(int width, int height, int cellSize);

  void setCell(int x, int y, bool alive);
  bool getCell(int x, int y) const;

  int getWidth() const { return m_width; }
  int getHeight() const { return m_height; }
  int getCellSize() const { return m_cellSize; }

  void update(float deltatime);
  void render(SDL_Renderer *renderer, int screenWidth, int screenHeight) const;

private:
  int m_width, m_height, m_cellSize;

  std::vector<bool> m_cells;

  int index(int x, int y) const { return x + y * m_width; }
  int wrap(int val, int max) const { return ((val % max) + max) % max; }
};
} // namespace JJ0o0::LangtonAnts