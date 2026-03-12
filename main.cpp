#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cassert>
#include <stdio.h>
#include <iostream>
#include <span>
#include <vector>
#include <string>
#include <iomanip>
#include "common.h"
#include "mat.h"

struct node
{
      float x;
      float y;
};

void uv_to_screen(const Vector2 p00,
                  const Vector2 p10,
                  const Vector2 p01,
                  std::span<float> uv,
                  Vector2* outP)
{
      glm::mat2 A;
      A[0] = glm::vec2(p10.x - p00.x, p10.y - p00.y);
      A[1] = glm::vec2(p01.x - p00.x, p01.y - p00.y);

      glm::vec2 local = A * glm::vec2(uv[0], uv[1]);
      glm::vec2 world = local + glm::vec2(p00.x, p00.y);

      outP->x = world[0];
      outP->y = world[1];
}

int main()
{
      int screen_width = 1920;
      int screen_height = 1080;
      InitWindow(screen_width, screen_height, "delaunay_triangulation");

      
      
      while(!WindowShouldClose())
      {
            BeginDrawing();

            ClearBackground(WHITE);

            int box_size = 800;
            Rectangle rec{(int)screen_width/2 - box_size/2, (int)screen_height/2 - box_size/2, box_size, box_size};
            GuiGroupBox(rec, "Param space");

            EndDrawing();
            
      }
      return 0;
}
