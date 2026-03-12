#include "raylib.h"
#include "raymath.h"
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

struct GuiBox
{
      Vector2 top_left;
      Vector2 top_right;
      Vector2 bottom_left;
};

struct node
{
      float x;
      float y;
};

void uv_to_screen(const Vector2 p00,
                  const Vector2 p10,
                  const Vector2 p01,
                  float* uv,
                  Vector2& outP)
{
      glm::mat2 A;
      A[0] = glm::vec2(p10.x - p00.x, p10.y - p00.y);
      A[1] = glm::vec2(p01.x - p00.x, p01.y - p00.y);

      glm::vec2 local = A * glm::vec2(uv[0], uv[1]);
      glm::vec2 world = local + glm::vec2(p00.x, p00.y);

      outP.x = world[0];
      outP.y = world[1];
}

int main()
{
      int screen_width = 1920;
      int screen_height = 1080;
      InitWindow(screen_width, screen_height, "delaunay_triangulation");

      int box_size = 800;
      Vector2 gui_box_pos = Vector2(screen_width/2 - box_size/2, (int)screen_height/2 - box_size/2);

      

      GuiBox gui_box =
      {
            gui_box_pos,
            gui_box_pos + Vector2{box_size, 0},
            gui_box_pos + Vector2{0, box_size}
      };

      std::vector<node> nodes(6);

      nodes[0] = node{0.2, 0.7};
      nodes[1] = node{0.1, 0.2};
      nodes[2] = node{0.9, 0.8};
      nodes[3] = node{0.4, 0.6};
      nodes[4] = node{0.5, 0.9};
      nodes[5] = node{0.4, 0.1};
      
      while(!WindowShouldClose())
      {
            BeginDrawing();

            ClearBackground(WHITE);

            
            Rectangle rec{(int)screen_width/2 - box_size/2, (int)screen_height/2 - box_size/2, box_size, box_size};
            GuiGroupBox(rec, "Param space");

            for(int i = 0; i < nodes.size(); i++)
            {
                  float in_uv[2];
                  in_uv[0] = nodes[i].x;
                  in_uv[1] = nodes[i].y;
                  Vector2 out_uv;
                  uv_to_screen(gui_box.top_left, gui_box.top_right, gui_box.bottom_left, in_uv, out_uv);
                  DrawCircleV(out_uv, 10, RED);
            }

            
            // DrawCircleV(gui_box.top_left, 10, RED);
            // DrawCircleV(gui_box.top_right, 10, RED);
            // DrawCircleV(gui_box.bottom_left, 10, RED);

            EndDrawing();
            
      }
      return 0;
}
