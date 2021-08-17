#include "game.hpp"
#include <cmath>

std::unique_ptr<Game> buildGame(unsigned int randomSeed) {
    return std::unique_ptr<Game>(new ConcreteGame(randomSeed));
}

namespace game_config {
    static const Pos3d DIMENSIONS { 10, 10, 14 };
    static const int DROP_SCORE_MULTIPLIER = 1;
    static const int REMOVAL_SCORE_MULTIPLIER = 20;
    static const int DROP_INTERVAL_MS = 1000;
}

ConcreteGame::ConcreteGame(unsigned int randomSeed)
:
    gameBox(game_config::DIMENSIONS),
    blockArray(gameBox),
    pieceGenerator(gameBox, randomSeed),
    activePiece(pieceGenerator.nextPiece()),
    score(0),
    alive(true),
    timeToNextDownMs(game_config::DROP_INTERVAL_MS),
    nDroppedPieces(0)
{}

std::vector<Block> ConcreteGame::getActiveBlocks() const {
    if (isOver()) {
        return {};
    }
    return activePiece.getBlocks();
}

std::vector<Block> ConcreteGame::getCementedBlocks() const {
    return blockArray.getNonEmptyBlocks();
}

std::vector<Block> ConcreteGame::getAllBlocks() const {
    auto blocks = getCementedBlocks();
    auto active = getActiveBlocks();
    blocks.insert(blocks.end(), active.begin(), active.end());
    return blocks;
}

bool ConcreteGame::isOver() const {
    return !alive;
}

int ConcreteGame::getScore() const {
    return score;
}

Pos3d ConcreteGame::getDimensions() const {
    return gameBox.dims;
}

// timed events
bool ConcreteGame::tick(int dtMs) {

    if (isOver()) return false;

    timeToNextDownMs -= dtMs;
    if (timeToNextDownMs <= 0) {
        moveDown();
        timeToNextDownMs = game_config::DROP_INTERVAL_MS;
        return true;
    }
    return false;
}

// controls

bool ConcreteGame::moveXY(int dx, int dy) {
    if (isOver()) return false;
    if (abs(dx) + abs(dy) != 1) abort();
    return setActivePieceIfFits(activePiece.translated(Pos3d {dx,dy,0}));
}

bool ConcreteGame::rotate(Axis axis, RotationDirection dir) {
    if (isOver()) return false;
    if (axis != Axis::X && axis != Axis::Y && axis != Axis::Z) abort();
    if (dir != RotationDirection::CW && dir != RotationDirection::CCW) abort();

    return rotate(Rotation{axis, dir});
}

void ConcreteGame::drop() {
    if (isOver()) return;
    int height = 0;
    while (moveDown()) height++;
    score += game_config::DROP_SCORE_MULTIPLIER * height;
}

// private helpers
bool ConcreteGame::rotate(Rotation rot) {
    return setActivePieceIfFits(
        gameBox.translateToBounds(activePiece.rotated(rot)));
}

bool ConcreteGame::moveDown() {
    if (!setActivePieceIfFits(activePiece.translated(Pos3d {0,0,-1}))) {
        blockArray.cementPiece(activePiece);
        nDroppedPieces++;

        // remove empty layers
        int nRemoved = 0;
        for (int z = gameBox.dims.z - 1; z >= 0; --z) {
            if (blockArray.isLayerFull(z)) {
                blockArray.removeLayer(z);
                nRemoved++;
            }
        }
        // (2^nRemoved - 1)*C
        // 0 -> 0, 1 -> C, 2 -> 3C, 3 -> 7C, ...
        score += ((1 << nRemoved) - 1) * game_config::REMOVAL_SCORE_MULTIPLIER;

        // new piece, check if fits
        activePiece = pieceGenerator.nextPiece();
        if (!blockArray.pieceFits(activePiece)) {
            alive = false;
        }
        return false;
    }
    return true;
}

bool ConcreteGame::setActivePieceIfFits(const Piece& candidate) {
    if (!blockArray.pieceFits(candidate)) {
        return false;
    }
    activePiece = candidate;
    return true;
}
