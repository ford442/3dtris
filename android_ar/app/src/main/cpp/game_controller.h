
#ifndef C_GAME_CONTROLLER_H_
#define C_GAME_CONTROLLER_H_

#include <glm.h>
#include "api.hpp"

class GameController {
public:
  enum class State {
    WAITING_FOR_PLANE,
    WAITING_FOR_BOX,
    RUNNING, // includes game over state
    PAUSED_TRACKING_LOST
  };

  GameController();
  ~GameController() = default;

  const Game& getGame() const { return *game; }
  const State getState() const { return state; }

  bool getTrackingState() const;
  bool hasStarted() const;

  bool onFrame(uint64_t timestamp);
  void onTrackingState(bool isTracking);
  void onBoxFound();

  void setScene(glm::mat4x4 projection, glm::mat4x4 view, glm::mat4x4 model, int w, int h);
  void onTap(float x, float y);
  void onScroll(float x1, float y1, float x2, float y2, float dx, float dy);

private:
  std::unique_ptr<Game> game;
  State state;

  uint64_t prevTimestamp;
  bool changed_by_controls;

  glm::mat4x4 projection_mat, view_mat, model_mat;
  int screen_width, screen_height;

  // controls
  void moveXY(int dx, int dy);
};


#endif