#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>

int evaluateBoard(const std::vector<std::vector<std::string>>& board) {
    int score = 0;
    std::unordered_map<std::string, int> piece_values = {
        {"w_pawn", 1}, {"b_pawn", -1},
        {"w_knight", 3}, {"b_knight", -3},
        {"w_bishop", 3}, {"b_bishop", -3},
        {"w_rook", 5}, {"b_rook", -5},
        {"w_queen", 9}, {"b_queen", -9},
        {"w_king", 1000}, {"b_king", -1000}
    };

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            std::string piece = board[row][col];
            if (piece != "") {
                score += piece_values[piece];
            }
        }
    }

    return score;
}

std::vector<std::string> generateLegalMoves(std::vector<std::vector<std::string>>& board, const std::string& player) {
    // This should generate legal moves for the player (either "w" or "b")
    std::vector<std::string> moves;
    // Placeholder for generating legal moves (this needs to be implemented)
    return moves;
}

std::vector<std::vector<std::string>> simulateMove(std::vector<std::vector<std::string>>& board, const std::string& move) {
    // This should apply a move to the board and return the new board
    std::vector<std::vector<std::string>> newBoard = board;
    // Placeholder for applying the move (this needs to be implemented)
    return newBoard;
}

int minimax(std::vector<std::vector<std::string>>& board, int depth, bool isMaximizingPlayer, int alpha, int beta) {
    if (depth == 0) {
        return evaluateBoard(board);
    }

    if (isMaximizingPlayer) {  // Maximizing for Black
        int maxEval = -INT_MAX;
        for (auto& move : generateLegalMoves(board, "b")) {
            std::vector<std::vector<std::string>> newBoard = simulateMove(board, move);
            int eval = minimax(newBoard, depth - 1, false, alpha, beta);
            maxEval = std::max(maxEval, eval);
            alpha = std::max(alpha, eval);
            if (beta <= alpha) {
                break; // Beta cut-off
            }
        }
        return maxEval;
    } else {  // Minimizing for White (Player-controlled)
        int minEval = INT_MAX;
        for (auto& move : generateLegalMoves(board, "w")) {
            std::vector<std::vector<std::string>> newBoard = simulateMove(board, move);
            int eval = minimax(newBoard, depth - 1, true, alpha, beta);
            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval);
            if (beta <= alpha) {
                break; // Alpha cut-off
            }
        }
        return minEval;
    }
}

std::string chooseBestMove(std::vector<std::vector<std::string>>& board) {
    int bestScore = -INT_MAX;
    std::string bestMove;

    // Loop through all legal moves for Black and choose the best one based on Minimax
    for (auto& move : generateLegalMoves(board, "b")) {
        std::vector<std::vector<std::string>> newBoard = simulateMove(board, move);
        int score = minimax(newBoard, 3, false, -INT_MAX, INT_MAX); // Depth 3
        if (score > bestScore) {
            bestScore = score;
            bestMove = move;
        }
    }

    return bestMove;
}

void gameLoop() {
    std::vector<std::vector<std::string>> board(8, std::vector<std::string>(8, ""));
    bool isWhiteTurn = true;  // White starts the game
    bool gameOver = false;

    // Initialize the board with pieces (simplified for the example)
    board[0] = {"b_rook", "b_knight", "b_bishop", "b_queen", "b_king", "b_bishop", "b_knight", "b_rook"};
    board[1] = {"b_pawn", "b_pawn", "b_pawn", "b_pawn", "b_pawn", "b_pawn", "b_pawn", "b_pawn"};
    board[6] = {"w_pawn", "w_pawn", "w_pawn", "w_pawn", "w_pawn", "w_pawn", "w_pawn", "w_pawn"};
    board[7] = {"w_rook", "w_knight", "w_bishop", "w_queen", "w_king", "w_bishop", "w_knight", "w_rook"};

    while (!gameOver) {
        if (isWhiteTurn) {
            std::cout << "Player's (White) move:" << std::endl;
            // Placeholder for player move logic (you would handle user input here)
            // For example, by clicking or pressing keys to choose a move
            // After the player makes a move, it switches to Black's turn
            // isWhiteTurn = false; // Switch to Black's turn
        } else {
            std::cout << "AI's (Black) move (Minimax):" << std::endl;
            std::string bestMove = chooseBestMove(board);
            std::cout << "AI chooses: " << bestMove << std::endl;
            // Apply the AI's move here (you would update the board)
            // After the AI moves, switch to White's turn
            isWhiteTurn = true;
        }

        // Check if the game is over (checkmate, stalemate, etc.)
        // gameOver = checkGameOver(board);
    }
}

int main() {
    gameLoop();
    return 0;
}
