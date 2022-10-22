#pragma once

#include <unordered_map>

#define NUM_PIECES 7

#define NUM_ORIENTATIONS 4
#define PIECE_GRID_SIZE 4

#define PIECE_CENTER_COL 1
#define PIECE_CENTER_ROW 1

enum class PieceType {
    T,
    S,
    Z,
    I,
    J,
    L,
    O
};

struct PieceData {
    char m_BlockGridPositions[NUM_ORIENTATIONS][PIECE_GRID_SIZE * PIECE_GRID_SIZE];

    //PieceData(bool blockLocations[4][16]) {
    //    m_BlockLocations = blockLocations;
    //}
};

//I used a global variable, I'm sorry.
extern const std::unordered_map<PieceType, const char*> pieceTypeString;
extern const std::unordered_map<PieceType, PieceData> pieceData;