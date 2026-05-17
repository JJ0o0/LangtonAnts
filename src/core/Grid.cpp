#include <LangtonAnts/core/Grid.hpp>
#include <LangtonAnts/utilities/Colors.hpp>

namespace JJ0o0::LangtonAnts {
Grid::Grid(int width, int height, int cellSize)
    : m_width(width), m_height(height), m_cellSize(cellSize) {
  m_cells.resize(m_width * m_height);
}

void Grid::update(float deltatime) {}

void Grid::render(SDL_Renderer *renderer, int screenWidth,
                  int screenHeight) const {
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

  float offsetX = (screenWidth - m_width * m_cellSize) / 2.0f;
  float offsetY = (screenHeight - m_height * m_cellSize) / 2.0f;

  for (int x = 0; x < m_width; x++) {
    for (int y = 0; y < m_height; y++) {
      if (!getCell(x, y))
        continue;

      float screenX = (x * m_cellSize) + offsetX;
      float screenY = (y * m_cellSize) + offsetY;
      float size = m_cellSize;

      SDL_FRect gridCell = {screenX, screenY, size, size};

      SDL_SetRenderDrawColor(renderer, Colors::GRID_COLOR.r,
                             Colors::GRID_COLOR.g, Colors::GRID_COLOR.b,
                             Colors::GRID_COLOR.a);
      SDL_RenderRect(renderer, &gridCell);

      float padding = 2.0f;
      SDL_FRect cell = {screenX + padding, screenY + padding,
                        size - padding * 2, size - padding * 2};

      SDL_SetRenderDrawColor(renderer, Colors::CELL_COLOR.r,
                             Colors::CELL_COLOR.g, Colors::CELL_COLOR.b,
                             Colors::CELL_COLOR.a);
      SDL_RenderFillRect(renderer, &cell);
    }
  }
}

void Grid::setCell(int x, int y, bool alive) {
  m_cells[index(wrap(x, m_width), wrap(y, m_height))] = alive;
}

bool Grid::getCell(int x, int y) const {
  return m_cells[index(wrap(x, m_width), wrap(y, m_height))];
}
} // namespace JJ0o0::LangtonAnts