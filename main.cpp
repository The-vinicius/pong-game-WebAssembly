#include <cstdlib>
#include <raylib.h>
#include <stdlib.h>

struct Ball {
  float x, y;
  float speedX, speedY;
  float radius;

  void Draw() { DrawCircle((int)x, (int)y, radius, WHITE); }
};

struct Paddle {
  float x, y;
  float speed;
  float width, height;

  Rectangle GetRect() {
    return Rectangle{x - width / 2, y - height / 2, 10, 100};
  }

  void Draw() { DrawRectangleRec(GetRect(), WHITE); }
};

int main(int argc, char *argv[]) {

  InitWindow(800, 600, "pong");
  SetWindowState(FLAG_VSYNC_HINT);

  Ball ball;
  ball.x = GetScreenWidth() / 2.0f;
  ball.y = GetScreenHeight() / 2.0f;
  ball.radius = 5;
  ball.speedX = 300;
  ball.speedY = 300;

  Paddle leftPaddle;
  leftPaddle.x = 50;
  leftPaddle.y = GetScreenHeight() / 2.0f;
  leftPaddle.width = 10;
  leftPaddle.height = 100;
  leftPaddle.speed = 500;

  Paddle rightPaddle;
  rightPaddle.x = GetScreenWidth() - 50;
  rightPaddle.y = GetScreenHeight() / 2.0f;
  rightPaddle.width = 10;
  rightPaddle.height = 100;
  rightPaddle.speed = 500;

  const char *winnerText = nullptr;
  int array[] = {40, -40};

  int p1 = 40;
  // int p2 = -40;

  while (!WindowShouldClose()) {
    ball.x += ball.speedX * GetFrameTime();
    ball.y += ball.speedY * GetFrameTime();

    rightPaddle.y = ball.y + p1;
    // leftPaddle.y = ball.y + p2;

    if (ball.y < 0) {
      ball.y = 0;
      ball.speedY *= -1;
    }
    if (ball.y > GetScreenHeight()) {
      ball.y = GetScreenHeight();
      ball.speedY *= -1;
    }

    if (IsKeyDown(KEY_W)) {
      leftPaddle.y -= leftPaddle.speed * GetFrameTime();
    }

    if (IsKeyDown(KEY_S)) {
      leftPaddle.y += leftPaddle.speed * GetFrameTime();
    }

    if (IsKeyDown(KEY_UP)) {
      rightPaddle.y -= rightPaddle.speed * GetFrameTime();
    }

    if (IsKeyDown(KEY_DOWN)) {
      rightPaddle.y += rightPaddle.speed * GetFrameTime();
    }

    if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius,
                                rightPaddle.GetRect())) {
      if (ball.speedX > 0) {
        ball.speedX *= -1.1;
        ball.speedY =
            (ball.y - rightPaddle.y) / (rightPaddle.height / 2) * -ball.speedX;

        // p2 = array[rand() % 2];
      }
    }

    if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius,
                                leftPaddle.GetRect())) {
      if (ball.speedX < 0) {
        ball.speedX *= -1.1f;
        ball.speedY =
            (ball.y - leftPaddle.y) / (leftPaddle.height / 2) * ball.speedX;

        p1 = array[rand() % 2];
      }
    }

    if (ball.x < 0) {
      winnerText = "Right Player Wins!";
    }
    if (ball.x > GetScreenWidth()) {
      winnerText = "Left Player Wins!";
    }
    if (winnerText && IsKeyPressed(KEY_SPACE)) {
      ball.x = GetScreenWidth() / 2.0f;
      ball.y = GetScreenHeight() / 2.0f;
      ball.speedX = 300;
      ball.speedY = 300;
      winnerText = nullptr;
    }

    BeginDrawing();
    ClearBackground(BLACK);
    ball.Draw();
    leftPaddle.Draw();
    rightPaddle.Draw();
    if (winnerText) {
      int textWidth = MeasureText(winnerText, 60);
      DrawText(winnerText, GetScreenWidth() / 2 - textWidth / 2,
               GetScreenHeight() / 2 - 30, 60, YELLOW);
    }
    DrawFPS(10, 10);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
