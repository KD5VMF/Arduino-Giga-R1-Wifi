#include <Arduino_GigaDisplay_GFX.h>

GigaDisplay_GFX tft;

// --- Screen / Layout (GIGA Display: 800x480) ---
const int SCREEN_WIDTH  = 800;
const int SCREEN_HEIGHT = 480;

// Scoreboard strip on the left; grid is centered in remaining area.
const int SCOREBOARD_WIDTH = 160;

// Tic-Tac-Toe grid
const int GRID_SIZE  = 3;
const int CELL_SIZE  = 120;  // 3 * 120 = 360 px grid
int gridOriginX;             // computed in setup()
int gridOriginY;             // computed in setup()

// Game speed (0=slow, 10=fast)
int gameSpeed = 4;

// Game data
char board[GRID_SIZE][GRID_SIZE];
int playerScore = 0;
int aiScore = 0;
int drawCount = 0;

// Symbols
#define PLAYER_SYMBOL 'X'
#define AI_SYMBOL     'O'

// Single bright green everywhere
uint16_t GREEN;
inline uint16_t bg() { return tft.color565(0, 0, 0); }

// Who moves this turn / who starts this round
bool xStartsThisRound = true;
bool xToMove = true;

// Winning line cache for highlight
struct WinLine {
  bool has;
  int r[3], c[3];
} lastWin = {false, {0,0,0}, {0,0,0}};

// ---------- Opening variety via "bags" ----------
static uint8_t openingBagX[9][2];
static uint8_t openingBagO[9][2];
static int bagIdxX = 0;
static int bagIdxO = 0;

void fillSequentialBag(uint8_t bag[9][2]) {
  int k=0;
  for (int r=0;r<3;r++)
    for (int c=0;c<3;c++) {
      bag[k][0]=r; bag[k][1]=c; k++;
    }
}

void shuffleBag(uint8_t bag[9][2]) {
  for (int i=8;i>0;i--) {
    int j = random(0, i+1);
    uint8_t tr = bag[i][0], tc = bag[i][1];
    bag[i][0]=bag[j][0]; bag[i][1]=bag[j][1];
    bag[j][0]=tr;        bag[j][1]=tc;
  }
}

bool takeNextOpeningFromBag(uint8_t bag[9][2], int& idx, int& outR, int& outC) {
  if (idx >= 9) { shuffleBag(bag); idx = 0; }
  for (int step=0; step<9; ++step) {
    int i = (idx + step) % 9;
    int rr = bag[i][0], cc = bag[i][1];
    if (board[rr][cc] == ' ') {
      outR = rr; outC = cc;
      idx = i + 1;
      return true;
    }
  }
  return false;
}

// --------- Forward Decls ----------
void drawGrid();
void drawGridLinesOnly();
void clearBoardCells();
void drawScoreboard();
void resetBoard();
bool isBoardFull();
bool isGameOver();
bool checkWinFor(char symbol, WinLine* out);
void showWinner();
void outlineWinningCells(const WinLine& wl);
void drawWinLine(const WinLine& wl);
void cellCenter(int r, int c, int& x, int& y);
void drawSymbol(int row, int col, char symbol);
void drawXInCell(int row, int col);
void drawOInCell(int row, int col);
void drawThickLine(int x0, int y0, int x1, int y1, int thickness);
void drawThickRect(int x, int y, int w, int h, int thickness);

// Move selection
void playerMove(); // X (near-perfect + variety)
void aiMove();     // O (near-perfect + variety)

// Helpers for openings / board state
int  countSymbol(char sym);
bool firstMoveFor(char sym);

// Minimax bits (same for both for fairness)
int  evaluateBoard();                  // +100 O win, -100 X win, 0 otherwise
bool hasMovesLeft();
int  heuristicScore();
int  lineScore(char a, char b, char c, char me, char opp);
int  minimax(int depth, bool isMax, int alpha, int beta);
void bestMoveFor(char symbol, int& outR, int& outC, int maxDepth, int secondBestPct);
void pickRandomAmongBest(int scores[], int moves[][2], int n, int targetScore, int& outR, int& outC);

// ---------------- Setup / Loop ----------------
void setup() {
  tft.begin();
  tft.setRotation(1); // landscape
  GREEN = tft.color565(0, 255, 0);
  tft.fillScreen(bg());

  randomSeed(analogRead(A0)); // variety

  // Compute centered grid origin inside the right pane
  const int playAreaW = SCREEN_WIDTH - SCOREBOARD_WIDTH;     // 640
  const int gridW = GRID_SIZE * CELL_SIZE;                   // 360
  const int gridH = GRID_SIZE * CELL_SIZE;                   // 360
  gridOriginX = SCOREBOARD_WIDTH + (playAreaW - gridW) / 2;  // centered in right pane
  gridOriginY = (SCREEN_HEIGHT - gridH) / 2;                 // centered vertically

  // Init opening bags
  fillSequentialBag(openingBagX);
  fillSequentialBag(openingBagO);
  shuffleBag(openingBagX);
  shuffleBag(openingBagO);
  bagIdxX = 0; bagIdxO = 0;

  drawGrid();
  drawScoreboard();
  resetBoard();
}

void loop() {
  if (!isGameOver()) {
    delay(map(gameSpeed, 0, 10, 1000, 30));
    if (xToMove) playerMove(); else aiMove();
    xToMove = !xToMove;
  } else {
    showWinner();
    delay(1800);
    resetBoard();
    clearBoardCells();   // keep scoreboard, just refresh grid area
    drawScoreboard();    // scores already updated
    lastWin.has = false;
  }
}

// ---------------- Drawing ----------------
void drawGrid() {
  tft.fillScreen(bg());
  tft.fillRect(0, 0, SCOREBOARD_WIDTH, SCREEN_HEIGHT, bg());
  drawGridLinesOnly();
}

void drawGridLinesOnly() {
  // Grid border
  drawThickRect(gridOriginX - 3, gridOriginY - 3, GRID_SIZE*CELL_SIZE + 6, GRID_SIZE*CELL_SIZE + 6, 3);
  // Grid lines (thicker)
  for (int i = 1; i < GRID_SIZE; i++) {
    int x = gridOriginX + i * CELL_SIZE;
    drawThickLine(x, gridOriginY, x, gridOriginY + GRID_SIZE * CELL_SIZE, 3);
  }
  for (int i = 1; i < GRID_SIZE; i++) {
    int y = gridOriginY + i * CELL_SIZE;
    drawThickLine(gridOriginX, y, gridOriginX + GRID_SIZE * CELL_SIZE, y, 3);
  }
}

void clearBoardCells() {
  tft.fillRect(gridOriginX, gridOriginY, GRID_SIZE*CELL_SIZE, GRID_SIZE*CELL_SIZE, bg());
  drawGridLinesOnly();
}

void drawScoreboard() {
  tft.fillRect(0, 0, SCOREBOARD_WIDTH, SCREEN_HEIGHT, bg());
  tft.setTextColor(GREEN);
  tft.setTextSize(2);

  int y = 24;
  tft.setCursor(12, y);   tft.print("Tic-Tac-Toe"); y += 36;

  tft.setCursor(12, y);   tft.print("Player (X):"); y += 26;
  tft.setCursor(12, y);   tft.print(playerScore);  y += 34;

  tft.setCursor(12, y);   tft.print("Player (O):");     y += 26;
  tft.setCursor(12, y);   tft.print(aiScore);      y += 34;

  tft.setCursor(12, y);   tft.print("Draws:");     y += 26;
  tft.setCursor(12, y);   tft.print(drawCount);    y += 34;

  tft.setCursor(12, y);   tft.print("Speed:");     y += 26;
  tft.setCursor(12, y);   tft.print(gameSpeed);    y += 34;

  tft.setCursor(12, y);   tft.print("Starts:");    y += 26;
  tft.setCursor(12, y);   tft.print(xStartsThisRound ? "X" : "O");
}

void resetBoard() {
  for (int r = 0; r < GRID_SIZE; r++)
    for (int c = 0; c < GRID_SIZE; c++)
      board[r][c] = ' ';

  // Alternate who starts each round
  xStartsThisRound = !xStartsThisRound;
  xToMove = xStartsThisRound;
}

bool isBoardFull() {
  for (int r = 0; r < GRID_SIZE; r++)
    for (int c = 0; c < GRID_SIZE; c++)
      if (board[r][c] == ' ') return false;
  return true;
}

bool isGameOver() {
  WinLine tmp;
  if (checkWinFor(PLAYER_SYMBOL, &tmp)) { playerScore++; drawScoreboard(); lastWin = tmp; return true; }
  if (checkWinFor(AI_SYMBOL, &tmp))     { aiScore++;     drawScoreboard(); lastWin = tmp; return true; }
  if (isBoardFull())                    { drawCount++;   drawScoreboard(); lastWin.has=false; return true; }
  return false;
}

bool checkWinFor(char symbol, WinLine* out) {
  // rows
  for (int r = 0; r < GRID_SIZE; r++) {
    if (board[r][0] == symbol && board[r][1] == symbol && board[r][2] == symbol) {
      if (out) { out->has = true; out->r[0]=r; out->c[0]=0; out->r[1]=r; out->c[1]=1; out->r[2]=r; out->c[2]=2; }
      return true;
    }
  }
  // cols
  for (int c = 0; c < GRID_SIZE; c++) {
    if (board[0][c] == symbol && board[1][c] == symbol && board[2][c] == symbol) {
      if (out) { out->has = true; out->r[0]=0; out->c[0]=c; out->r[1]=1; out->c[1]=c; out->r[2]=2; out->c[2]=c; }
      return true;
    }
  }
  // diagonals
  if (board[0][0]==symbol && board[1][1]==symbol && board[2][2]==symbol) {
    if (out) { out->has = true; out->r[0]=0; out->c[0]=0; out->r[1]=1; out->c[1]=1; out->r[2]=2; out->c[2]=2; }
    return true;
  }
  if (board[0][2]==symbol && board[1][1]==symbol && board[2][0]==symbol) {
    if (out) { out->has = true; out->r[0]=0; out->c[0]=2; out->r[1]=1; out->c[1]=1; out->r[2]=2; out->c[2]=0; }
    return true;
  }
  if (out) out->has = false;
  return false;
}

void showWinner() {
  tft.fillRect(SCOREBOARD_WIDTH, SCREEN_HEIGHT - 48, SCREEN_WIDTH - SCOREBOARD_WIDTH, 48, bg());
  tft.setTextColor(GREEN);
  tft.setTextSize(2);
  tft.setCursor(SCOREBOARD_WIDTH + 12, SCREEN_HEIGHT - 40);

  WinLine wl;
  if (checkWinFor(PLAYER_SYMBOL, &wl)) {
    tft.print("Player (X) wins!");
    outlineWinningCells(wl);
    drawWinLine(wl);
  } else if (checkWinFor(AI_SYMBOL, &wl)) {
    tft.print("AI (O) wins!");
    outlineWinningCells(wl);
    drawWinLine(wl);
  } else {
    tft.print("It's a draw.");
  }
}

void outlineWinningCells(const WinLine& wl) {
  if (!wl.has) return;
  for (int i = 0; i < 3; i++) {
    int r = wl.r[i], c = wl.c[i];
    int x = gridOriginX + c * CELL_SIZE;
    int y = gridOriginY + r * CELL_SIZE;
    drawThickRect(x+3, y+3, CELL_SIZE-6, CELL_SIZE-6, 3);
  }
}

// === NEW: draw a bold line through the winning 3-in-a-row ===
void drawWinLine(const WinLine& wl) {
  if (!wl.has) return;

  // Determine orientation and endpoints (cell centers)
  int x1,y1,x2,y2;

  // Check row win (all r equal)
  if (wl.r[0]==wl.r[1] && wl.r[1]==wl.r[2]) {
    int r = wl.r[0];
    cellCenter(r, 0, x1, y1);
    cellCenter(r, 2, x2, y2);
  }
  // Check column win (all c equal)
  else if (wl.c[0]==wl.c[1] && wl.c[1]==wl.c[2]) {
    int c = wl.c[0];
    cellCenter(0, c, x1, y1);
    cellCenter(2, c, x2, y2);
  }
  // Diagonals
  else {
    bool mainDiag = true;
    for (int i=0;i<3;i++) if (wl.r[i] != wl.c[i]) { mainDiag = false; break; }
    if (mainDiag) {
      cellCenter(0, 0, x1, y1);
      cellCenter(2, 2, x2, y2);
    } else {
      cellCenter(0, 2, x1, y1);
      cellCenter(2, 0, x2, y2);
    }
  }

  // Optional: extend slightly beyond centers for flair
  // Move endpoints 8 px outward along the line
  float dx = (float)(x2 - x1);
  float dy = (float)(y2 - y1);
  float len = sqrt(dx*dx + dy*dy);
  if (len > 0.1f) {
    float ux = dx / len, uy = dy / len;
    x1 -= (int)(ux * 12);
    y1 -= (int)(uy * 12);
    x2 += (int)(ux * 12);
    y2 += (int)(uy * 12);
  }

  // Draw bold line
  drawThickLine(x1, y1, x2, y2, 6);
}

void cellCenter(int r, int c, int& x, int& y) {
  x = gridOriginX + c * CELL_SIZE + CELL_SIZE / 2;
  y = gridOriginY + r * CELL_SIZE + CELL_SIZE / 2;
}

void drawSymbol(int row, int col, char symbol) {
  if (symbol == 'X') drawXInCell(row, col);
  else               drawOInCell(row, col);
}

void drawXInCell(int row, int col) {
  int x0 = gridOriginX + col * CELL_SIZE;
  int y0 = gridOriginY + row * CELL_SIZE;
  int pad = 16;
  int thickness = 4;

  // two diagonals, thick
  drawThickLine(x0 + pad,              y0 + pad,               x0 + CELL_SIZE - pad, y0 + CELL_SIZE - pad, thickness);
  drawThickLine(x0 + CELL_SIZE - pad,  y0 + pad,               x0 + pad,             y0 + CELL_SIZE - pad, thickness);
}

void drawOInCell(int row, int col) {
  int cx = gridOriginX + col * CELL_SIZE + CELL_SIZE / 2;
  int cy = gridOriginY + row * CELL_SIZE + CELL_SIZE / 2;
  int r  = (CELL_SIZE / 2) - 18;

  // Thicker circle via three outlines
  tft.drawCircle(cx, cy, r, GREEN);
  tft.drawCircle(cx, cy, r-1, GREEN);
  tft.drawCircle(cx, cy, r+1, GREEN);
}

// Thick primitives
void drawThickLine(int x0, int y0, int x1, int y1, int thickness) {
  if (x0 == x1) {
    for (int dx = -thickness/2; dx <= thickness/2; dx++) {
      tft.drawLine(x0 + dx, y0, x1 + dx, y1, GREEN);
    }
  } else if (y0 == y1) {
    for (int dy = -thickness/2; dy <= thickness/2; dy++) {
      tft.drawLine(x0, y0 + dy, x1, y1 + dy, GREEN);
    }
  } else {
    // diagonal thickness: simple parallel offsets
    for (int k = -thickness/2; k <= thickness/2; k++) {
      tft.drawLine(x0 + k, y0, x1 + k, y1, GREEN);
    }
  }
}

void drawThickRect(int x, int y, int w, int h, int thickness) {
  for (int t = 0; t < thickness; t++) {
    tft.drawRect(x - t, y - t, w + 2*t, h + 2*t, GREEN);
  }
}

// ---------------- Helpers ----------------
int countSymbol(char sym) {
  int cnt = 0;
  for (int r=0;r<GRID_SIZE;r++)
    for (int c=0;c<GRID_SIZE;c++)
      if (board[r][c] == sym) cnt++;
  return cnt;
}

bool firstMoveFor(char sym) {
  return countSymbol(sym) == 0;
}

// ---------------- Moves ----------------
void playerMove() {
  int r = -1, c = -1;

  // Varied opening for X's first move using bag (no repeats until 9 used)
  if (firstMoveFor(PLAYER_SYMBOL)) {
    if (takeNextOpeningFromBag(openingBagX, bagIdxX, r, c)) {
      board[r][c] = PLAYER_SYMBOL;
      drawSymbol(r, c, PLAYER_SYMBOL);
      return;
    }
  }

  // Smart but not perfect: depth-limited minimax + 10% second-best for variety
  bool got = false;
  bestMoveFor(PLAYER_SYMBOL, r, c, /*maxDepth=*/5, /*secondBestPct=*/10);
  if (r >= 0 && c >= 0) got = true;

  if (!got) {
    for (int i=0;i<GRID_SIZE && !got;i++)
      for (int j=0;j<GRID_SIZE && !got;j++)
        if (board[i][j]==' ') { r=i; c=j; got=true; }
  }

  board[r][c] = PLAYER_SYMBOL;
  drawSymbol(r, c, PLAYER_SYMBOL);
}

void aiMove() {
  int r=-1, c=-1;

  // Varied opening for O's first move using bag
  if (firstMoveFor(AI_SYMBOL)) {
    if (takeNextOpeningFromBag(openingBagO, bagIdxO, r, c)) {
      board[r][c] = AI_SYMBOL;
      drawSymbol(r, c, AI_SYMBOL);
      return;
    }
  }

  // Smart but not perfect too (fair-ish)
  bool got = false;
  bestMoveFor(AI_SYMBOL, r, c, /*maxDepth=*/5, /*secondBestPct=*/10);
  if (r >= 0 && c >= 0) got = true;

  if (!got) {
    for (int i=0;i<GRID_SIZE && !got;i++)
      for (int j=0;j<GRID_SIZE && !got;j++)
        if (board[i][j]==' ') { r=i; c=j; got=true; }
  }

  board[r][c] = AI_SYMBOL;
  drawSymbol(r, c, AI_SYMBOL);
}

// --------------- Minimax ---------------
int evaluateBoard() {
  WinLine dummy;
  if (checkWinFor(AI_SYMBOL, &dummy))     return  100;
  if (checkWinFor(PLAYER_SYMBOL, &dummy)) return -100;
  return 0;
}

bool hasMovesLeft() {
  for (int r=0;r<GRID_SIZE;r++)
    for (int c=0;c<GRID_SIZE;c++)
      if (board[r][c]==' ') return true;
  return false;
}

int heuristicScore() {
  // Light heuristic to rank non-terminal positions: sum of line potentials
  int score = 0;
  // rows
  for (int r=0;r<3;r++) score += lineScore(board[r][0], board[r][1], board[r][2], AI_SYMBOL, PLAYER_SYMBOL);
  // cols
  for (int c=0;c<3;c++) score += lineScore(board[0][c], board[1][c], board[2][c], AI_SYMBOL, PLAYER_SYMBOL);
  // diags
  score += lineScore(board[0][0], board[1][1], board[2][2], AI_SYMBOL, PLAYER_SYMBOL);
  score += lineScore(board[0][2], board[1][1], board[2][0], AI_SYMBOL, PLAYER_SYMBOL);
  return score;
}

int lineScore(char a, char b, char c, char me, char opp) {
  int meCnt  = (a==me) + (b==me) + (c==me);
  int oppCnt = (a==opp) + (b==opp) + (c==opp);
  if (meCnt>0 && oppCnt>0) return 0;  // blocked
  if (meCnt==3) return 50;
  if (meCnt==2) return 10;
  if (meCnt==1) return 1;
  if (oppCnt==2) return -9; // prefer blocking
  if (oppCnt==1) return -1;
  return 0;
}

int minimax(int depth, bool isMax, int alpha, int beta) {
  int eval = evaluateBoard();
  if (eval == 100 || eval == -100) return eval;
  if (!hasMovesLeft() || depth == 0) return heuristicScore();

  if (isMax) { // maximizing = O (AI)
    int best = -10000;
    for (int r=0;r<GRID_SIZE;r++) {
      for (int c=0;c<GRID_SIZE;c++) {
        if (board[r][c]==' ') {
          board[r][c] = AI_SYMBOL;
          int val = minimax(depth-1, false, alpha, beta);
          board[r][c] = ' ';
          if (val > best) best = val;
          if (best > alpha) alpha = best;
          if (beta <= alpha) return best;
        }
      }
    }
    return best;
  } else {     // minimizing = X (Player)
    int best = 10000;
    for (int r=0;r<GRID_SIZE;r++) {
      for (int c=0;c<GRID_SIZE;c++) {
        if (board[r][c]==' ') {
          board[r][c] = PLAYER_SYMBOL;
          int val = minimax(depth-1, true, alpha, beta);
          board[r][c] = ' ';
          if (val < best) best = val;
          if (best < beta) beta = best;
          if (beta <= alpha) return best;
        }
      }
    }
    return best;
  }
}

void bestMoveFor(char symbol, int& outR, int& outC, int maxDepth, int secondBestPct) {
  int bestScore = (symbol==AI_SYMBOL) ? -10000 : 10000;
  int moves[9][2];   // possible move list
  int scores[9];
  int mCount = 0;

  // Collect and score moves
  for (int r=0;r<GRID_SIZE;r++) {
    for (int c=0;c<GRID_SIZE;c++) {
      if (board[r][c]==' ') {
        board[r][c] = symbol;
        int score;
        if (symbol==AI_SYMBOL) {
          score = minimax(maxDepth, /*isMax*/false, -10000, 10000);
          if (score > bestScore) bestScore = score;
        } else {
          score = minimax(maxDepth, /*isMax*/true, -10000, 10000);
          if (score < bestScore) bestScore = score;
        }
        board[r][c] = ' ';
        moves[mCount][0]=r; moves[mCount][1]=c; scores[mCount]=score; mCount++;
      }
    }
  }

  // Pick among best-scored moves randomly
  pickRandomAmongBest(scores, moves, mCount, bestScore, outR, outC);

  // Occasionally pick second-best to keep it fun/fair-ish
  if (mCount > 1 && random(0,100) < secondBestPct) {
    int secondScore = (symbol==AI_SYMBOL) ? -10000 : 10000;
    if (symbol==AI_SYMBOL) {
      for (int i=0;i<mCount;i++) { int sc=scores[i]; if (sc<bestScore && sc>secondScore) secondScore=sc; }
      if (secondScore != -10000) pickRandomAmongBest(scores, moves, mCount, secondScore, outR, outC);
    } else {
      for (int i=0;i<mCount;i++) { int sc=scores[i]; if (sc>bestScore && sc<secondScore) secondScore=sc; }
      if (secondScore != 10000) pickRandomAmongBest(scores, moves, mCount, secondScore, outR, outC);
    }
  }
}

void pickRandomAmongBest(int scores[], int moves[][2], int n, int targetScore, int& outR, int& outC) {
  int idxs[9]; int k=0;
  for (int i=0;i<n;i++) if (scores[i]==targetScore) idxs[k++]=i;
  int pick = (k>0) ? idxs[random(0,k)] : 0;
  outR = moves[pick][0];
  outC = moves[pick][1];
}
