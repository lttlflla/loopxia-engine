#include "loopxia/math.h"

namespace loopxia
{
    class Grid
    {
        Vector2 index;
    };

    class HexgaonGrid
    {
        Vector2 WorldPositionToGridIndex(Vector2);
        Vector2 GridIndexToWorldPosition(Vector2);

        float GridSize();


        // generate hexagon grid, given grid size and plane for the grid
        //static HexagonGrid GenerateHexagonGrid(int gridSize, const Plane& p);

    };
}
