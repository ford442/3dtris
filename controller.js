"use strict";
/* globals Game, window */

function GameController() {
    this.game = new Game();
    this.t = 0;

    this.autoDownInterval = 1.0;
    this.timeSinceDown = 0.0;
}

GameController.prototype.notifyChanged = function() {
    if (this.changedCallback) {
        this.changedCallback(this.game);
    }
};

GameController.prototype.nextFrame = function(dt) {
    this.t += dt;
    this.timeSinceDown += dt;
    if (this.timeSinceDown > this.autoDownInterval) {
        this.moveDown();
    }
};

GameController.prototype.moveDown = function() {
    this.timeSinceDown = 0.0;
    this.game.controls.moveDown();
    this.notifyChanged();
};

GameController.prototype.run = function() {

    const that = this;
    let prevTime;

    function animationStep(timestamp) {
      if (!prevTime) prevTime = timestamp;
      const dt = timestamp - prevTime;

      that.nextFrame(dt * 1e-3);

      if (!that.game.isOver()) {
        window.requestAnimationFrame(animationStep);
      }
      prevTime = timestamp;
    }

    window.requestAnimationFrame(animationStep);
};
