import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ChessGame extends JFrame {
    private final Board board = new Board();
    private final BoardPanel boardPanel = new BoardPanel();
    private final JLabel statusLabel = new JLabel("백 차례");
    private final Map<String, BufferedImage> pieceImages = new HashMap<>();

    public ChessGame() {
        setTitle("Java Chess - Drag & Drop PNG");
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        loadPieceImages();

        statusLabel.setBorder(BorderFactory.createEmptyBorder(8, 12, 8, 12));
        add(boardPanel, BorderLayout.CENTER);
        add(statusLabel, BorderLayout.SOUTH);

        setSize(760, 820);
        setLocationRelativeTo(null);
        setVisible(true);

        updateStatus();
    }

    private void updateStatus() {
        if (board.gameOver) {
            statusLabel.setText(board.gameOverMessage);
            return;
        }

        String turnText = board.turn == PieceColor.WHITE ? "백" : "흑";
        String text = turnText + " 차례";
        if (board.isKingInCheck(board.turn)) {
            text += " · 체크 상태";
        }
        statusLabel.setText(text);
    }

    private void loadPieceImages() {
        String[] colors = {"white", "black"};
        String[] names = {"king", "queen", "rook", "bishop", "knight", "pawn"};

        for (String color : colors) {
            for (String name : names) {
                String key = color + "_" + name;
                try {
                    BufferedImage img = ImageIO.read(new File("pieces/" + key + ".png"));
                    pieceImages.put(key, img);
                } catch (IOException e) {
                    System.out.println("이미지 로드 실패: pieces/" + key + ".png");
                }
            }
        }
    }

    private PieceType askPromotion() {
        Object[] options = {"Queen", "Rook", "Bishop", "Knight"};
        int choice = JOptionPane.showOptionDialog(
                this,
                "프로모션할 말을 선택해줘",
                "Pawn Promotion",
                JOptionPane.DEFAULT_OPTION,
                JOptionPane.QUESTION_MESSAGE,
                null,
                options,
                options[0]
        );

        return switch (choice) {
            case 1 -> PieceType.ROOK;
            case 2 -> PieceType.BISHOP;
            case 3 -> PieceType.KNIGHT;
            default -> PieceType.QUEEN;
        };
    }

    private class BoardPanel extends JPanel implements MouseListener, MouseMotionListener {
        private static final int BOARD_SIZE = 8;
        private int tileSize;

        private int selectedRow = -1;
        private int selectedCol = -1;
        private List<Move> legalMoves = new ArrayList<>();

        private boolean dragging = false;
        private int dragMouseX;
        private int dragMouseY;
        private int dragOffsetX;
        private int dragOffsetY;

        BoardPanel() {
            addMouseListener(this);
            addMouseMotionListener(this);
            setPreferredSize(new Dimension(760, 760));
        }

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);

            tileSize = Math.min(getWidth(), getHeight()) / BOARD_SIZE;
            Graphics2D g2 = (Graphics2D) g.create();

            drawBoard(g2);
            drawHighlights(g2);
            drawPieces(g2);

            g2.dispose();
        }

        private void drawBoard(Graphics2D g2) {
            for (int r = 0; r < 8; r++) {
                for (int c = 0; c < 8; c++) {
                    if ((r + c) % 2 == 0) {
                        g2.setColor(new Color(240, 217, 181));
                    } else {
                        g2.setColor(new Color(181, 136, 99));
                    }
                    g2.fillRect(c * tileSize, r * tileSize, tileSize, tileSize);
                }
            }
        }

        private void drawHighlights(Graphics2D g2) {
            if (selectedRow != -1 && selectedCol != -1) {
                g2.setColor(new Color(246, 246, 105, 180));
                g2.fillRect(selectedCol * tileSize, selectedRow * tileSize, tileSize, tileSize);
            }

            for (Move m : legalMoves) {
                Piece target = board.get(m.toRow, m.toCol);
                if (target == null && !m.enPassant) {
                    g2.setColor(new Color(80, 180, 80, 140));
                    int cx = m.toCol * tileSize + tileSize / 2;
                    int cy = m.toRow * tileSize + tileSize / 2;
                    int radius = tileSize / 6;
                    g2.fillOval(cx - radius, cy - radius, radius * 2, radius * 2);
                } else {
                    g2.setColor(new Color(220, 80, 80, 120));
                    g2.fillRect(m.toCol * tileSize, m.toRow * tileSize, tileSize, tileSize);
                }
            }
        }

        private void drawPieces(Graphics2D g2) {
            for (int r = 0; r < 8; r++) {
                for (int c = 0; c < 8; c++) {
                    Piece p = board.get(r, c);
                    if (p == null) continue;

                    if (dragging && r == selectedRow && c == selectedCol) continue;

                    drawPieceImage(g2, p, c * tileSize, r * tileSize, tileSize, tileSize);
                }
            }

            if (dragging && selectedRow != -1 && selectedCol != -1) {
                Piece p = board.get(selectedRow, selectedCol);
                if (p != null) {
                    drawPieceImage(g2, p, dragMouseX - dragOffsetX, dragMouseY - dragOffsetY, tileSize, tileSize);
                }
            }
        }

        private void drawPieceImage(Graphics2D g2, Piece piece, int x, int y, int w, int h) {
            BufferedImage img = pieceImages.get(piece.imageKey());
            if (img != null) {
                int margin = Math.max(4, w / 12);
                g2.drawImage(img, x + margin, y + margin, w - margin * 2, h - margin * 2, null);
            } else {
                g2.setColor(piece.color == PieceColor.WHITE ? Color.WHITE : Color.BLACK);
                g2.setFont(new Font("SansSerif", Font.PLAIN, h - 12));
                FontMetrics fm = g2.getFontMetrics();
                String text = piece.unicode();
                int tx = x + (w - fm.stringWidth(text)) / 2;
                int ty = y + ((h - fm.getHeight()) / 2) + fm.getAscent();
                g2.drawString(text, tx, ty);
            }
        }

        private Point toBoardCell(int x, int y) {
            int col = x / tileSize;
            int row = y / tileSize;
            if (row < 0 || row >= 8 || col < 0 || col >= 8) return null;
            return new Point(col, row);
        }

        private Move findMoveTo(int row, int col) {
            for (Move m : legalMoves) {
                if (m.toRow == row && m.toCol == col) return m;
            }
            return null;
        }

        @Override
        public void mousePressed(MouseEvent e) {
            if (board.gameOver) return;

            Point p = toBoardCell(e.getX(), e.getY());
            if (p == null) return;

            int row = p.y;
            int col = p.x;

            Piece piece = board.get(row, col);
            if (piece == null || piece.color != board.turn) return;

            selectedRow = row;
            selectedCol = col;
            legalMoves = board.getLegalMovesForPiece(row, col);

            if (legalMoves.isEmpty()) {
                selectedRow = -1;
                selectedCol = -1;
                return;
            }

            dragging = true;
            dragMouseX = e.getX();
            dragMouseY = e.getY();
            dragOffsetX = e.getX() - col * tileSize;
            dragOffsetY = e.getY() - row * tileSize;

            repaint();
        }

        @Override
        public void mouseDragged(MouseEvent e) {
            if (!dragging) return;
            dragMouseX = e.getX();
            dragMouseY = e.getY();
            repaint();
        }

        @Override
        public void mouseReleased(MouseEvent e) {
            if (!dragging) return;

            Point p = toBoardCell(e.getX(), e.getY());
            Move chosen = null;

            if (p != null) {
                chosen = findMoveTo(p.y, p.x);
            }

            if (chosen != null) {
                if (chosen.promotion) {
                    PieceType promoted = askPromotion();
                    if (promoted == null) promoted = PieceType.QUEEN;
                    chosen.promotionType = promoted;
                }
                board.applyMove(chosen);

                if (board.gameOver) {
                    JOptionPane.showMessageDialog(ChessGame.this, board.gameOverMessage);
                }
            }

            dragging = false;
            selectedRow = -1;
            selectedCol = -1;
            legalMoves.clear();
            updateStatus();
            repaint();
        }

        @Override public void mouseMoved(MouseEvent e) {}
        @Override public void mouseClicked(MouseEvent e) {}
        @Override public void mouseEntered(MouseEvent e) {}
        @Override public void mouseExited(MouseEvent e) {}
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(ChessGame::new);
    }

    enum PieceColor {
        WHITE, BLACK;
        PieceColor opposite() {
            return this == WHITE ? BLACK : WHITE;
        }
    }

    enum PieceType {
        KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN
    }

    static class Piece {
        PieceType type;
        PieceColor color;
        boolean moved;

        Piece(PieceType type, PieceColor color) {
            this.type = type;
            this.color = color;
        }

        Piece copy() {
            Piece p = new Piece(type, color);
            p.moved = moved;
            return p;
        }

        String unicode() {
            return switch (type) {
                case KING -> color == PieceColor.WHITE ? "♔" : "♚";
                case QUEEN -> color == PieceColor.WHITE ? "♕" : "♛";
                case ROOK -> color == PieceColor.WHITE ? "♖" : "♜";
                case BISHOP -> color == PieceColor.WHITE ? "♗" : "♝";
                case KNIGHT -> color == PieceColor.WHITE ? "♘" : "♞";
                case PAWN -> color == PieceColor.WHITE ? "♙" : "♟";
            };
        }

        String imageKey() {
            String c = color == PieceColor.WHITE ? "white" : "black";
            String t = switch (type) {
                case KING -> "king";
                case QUEEN -> "queen";
                case ROOK -> "rook";
                case BISHOP -> "bishop";
                case KNIGHT -> "knight";
                case PAWN -> "pawn";
            };
            return c + "_" + t;
        }
    }

    static class Move {
        int fromRow, fromCol, toRow, toCol;
        boolean enPassant;
        boolean castleKingSide;
        boolean castleQueenSide;
        boolean promotion;
        PieceType promotionType;
        int capturedRow = -1;
        int capturedCol = -1;

        Move(int fromRow, int fromCol, int toRow, int toCol) {
            this.fromRow = fromRow;
            this.fromCol = fromCol;
            this.toRow = toRow;
            this.toCol = toCol;
        }
    }

    static class Board {
        Piece[][] grid = new Piece[8][8];
        PieceColor turn = PieceColor.WHITE;
        int enPassantRow = -1;
        int enPassantCol = -1;
        boolean gameOver = false;
        String gameOverMessage = "";

        Board() {
            setup();
        }

        Board(Board other) {
            for (int r = 0; r < 8; r++) {
                for (int c = 0; c < 8; c++) {
                    this.grid[r][c] = other.grid[r][c] == null ? null : other.grid[r][c].copy();
                }
            }
            this.turn = other.turn;
            this.enPassantRow = other.enPassantRow;
            this.enPassantCol = other.enPassantCol;
            this.gameOver = other.gameOver;
            this.gameOverMessage = other.gameOverMessage;
        }

        void setup() {
            for (int c = 0; c < 8; c++) {
                grid[1][c] = new Piece(PieceType.PAWN, PieceColor.BLACK);
                grid[6][c] = new Piece(PieceType.PAWN, PieceColor.WHITE);
            }

            PieceType[] back = {
                    PieceType.ROOK, PieceType.KNIGHT, PieceType.BISHOP, PieceType.QUEEN,
                    PieceType.KING, PieceType.BISHOP, PieceType.KNIGHT, PieceType.ROOK
            };

            for (int c = 0; c < 8; c++) {
                grid[0][c] = new Piece(back[c], PieceColor.BLACK);
                grid[7][c] = new Piece(back[c], PieceColor.WHITE);
            }
        }

        Piece get(int row, int col) {
            if (!inBounds(row, col)) return null;
            return grid[row][col];
        }

        void set(int row, int col, Piece piece) {
            if (inBounds(row, col)) {
                grid[row][col] = piece;
            }
        }

        boolean inBounds(int row, int col) {
            return row >= 0 && row < 8 && col >= 0 && col < 8;
        }

        List<Move> getLegalMovesForPiece(int row, int col) {
            Piece piece = get(row, col);
            List<Move> result = new ArrayList<>();
            if (piece == null || piece.color != turn) return result;

            List<Move> pseudo = getPseudoLegalMoves(row, col, true);
            for (Move m : pseudo) {
                Board copy = new Board(this);
                copy.applyMoveInternal(m);
                if (!copy.isKingInCheck(piece.color)) {
                    result.add(m);
                }
            }
            return result;
        }

        List<Move> getAllLegalMoves(PieceColor color) {
            List<Move> result = new ArrayList<>();
            for (int r = 0; r < 8; r++) {
                for (int c = 0; c < 8; c++) {
                    Piece p = get(r, c);
                    if (p != null && p.color == color) {
                        List<Move> pseudo = getPseudoLegalMoves(r, c, true);
                        for (Move m : pseudo) {
                            Board copy = new Board(this);
                            copy.applyMoveInternal(m);
                            if (!copy.isKingInCheck(color)) {
                                result.add(m);
                            }
                        }
                    }
                }
            }
            return result;
        }

        List<Move> getPseudoLegalMoves(int row, int col, boolean includeCastling) {
            Piece piece = get(row, col);
            List<Move> moves = new ArrayList<>();
            if (piece == null) return moves;

            switch (piece.type) {
                case PAWN -> addPawnMoves(row, col, piece, moves);
                case ROOK -> addSlidingMoves(row, col, piece, moves, new int[][]{{1,0},{-1,0},{0,1},{0,-1}});
                case BISHOP -> addSlidingMoves(row, col, piece, moves, new int[][]{{1,1},{1,-1},{-1,1},{-1,-1}});
                case QUEEN -> addSlidingMoves(row, col, piece, moves, new int[][]{{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}});
                case KNIGHT -> addKnightMoves(row, col, piece, moves);
                case KING -> addKingMoves(row, col, piece, moves, includeCastling);
            }
            return moves;
        }

        void addPawnMoves(int row, int col, Piece piece, List<Move> moves) {
            int dir = piece.color == PieceColor.WHITE ? -1 : 1;
            int startRow = piece.color == PieceColor.WHITE ? 6 : 1;
            int promotionRow = piece.color == PieceColor.WHITE ? 0 : 7;

            int oneStep = row + dir;
            if (inBounds(oneStep, col) && get(oneStep, col) == null) {
                Move m = new Move(row, col, oneStep, col);
                if (oneStep == promotionRow) m.promotion = true;
                moves.add(m);

                int twoStep = row + dir * 2;
                if (row == startRow && get(twoStep, col) == null) {
                    moves.add(new Move(row, col, twoStep, col));
                }
            }

            for (int dc : new int[]{-1, 1}) {
                int nr = row + dir;
                int nc = col + dc;
                if (!inBounds(nr, nc)) continue;
                Piece target = get(nr, nc);
                if (target != null && target.color != piece.color) {
                    Move m = new Move(row, col, nr, nc);
                    if (nr == promotionRow) m.promotion = true;
                    moves.add(m);
                }
            }

            for (int dc : new int[]{-1, 1}) {
                int nr = row + dir;
                int nc = col + dc;
                if (nr == enPassantRow && nc == enPassantCol) {
                    Move m = new Move(row, col, nr, nc);
                    m.enPassant = true;
                    m.capturedRow = row;
                    m.capturedCol = nc;
                    moves.add(m);
                }
            }
        }

        void addSlidingMoves(int row, int col, Piece piece, List<Move> moves, int[][] dirs) {
            for (int[] d : dirs) {
                int nr = row + d[0];
                int nc = col + d[1];
                while (inBounds(nr, nc)) {
                    Piece target = get(nr, nc);
                    if (target == null) {
                        moves.add(new Move(row, col, nr, nc));
                    } else {
                        if (target.color != piece.color) {
                            moves.add(new Move(row, col, nr, nc));
                        }
                        break;
                    }
                    nr += d[0];
                    nc += d[1];
                }
            }
        }

        void addKnightMoves(int row, int col, Piece piece, List<Move> moves) {
            int[][] jumps = {{2,1},{2,-1},{-2,1},{-2,-1},{1,2},{1,-2},{-1,2},{-1,-2}};
            for (int[] j : jumps) {
                int nr = row + j[0];
                int nc = col + j[1];
                if (!inBounds(nr, nc)) continue;
                Piece target = get(nr, nc);
                if (target == null || target.color != piece.color) {
                    moves.add(new Move(row, col, nr, nc));
                }
            }
        }

        void addKingMoves(int row, int col, Piece piece, List<Move> moves, boolean includeCastling) {
            for (int dr = -1; dr <= 1; dr++) {
                for (int dc = -1; dc <= 1; dc++) {
                    if (dr == 0 && dc == 0) continue;
                    int nr = row + dr;
                    int nc = col + dc;
                    if (!inBounds(nr, nc)) continue;
                    Piece target = get(nr, nc);
                    if (target == null || target.color != piece.color) {
                        moves.add(new Move(row, col, nr, nc));
                    }
                }
            }

            if (!includeCastling || piece.moved || isKingInCheck(piece.color)) return;

            int homeRow = piece.color == PieceColor.WHITE ? 7 : 0;
            if (row != homeRow || col != 4) return;

            Piece rookKingSide = get(homeRow, 7);
            if (rookKingSide != null && rookKingSide.type == PieceType.ROOK &&
                    rookKingSide.color == piece.color && !rookKingSide.moved) {
                if (get(homeRow, 5) == null && get(homeRow, 6) == null) {
                    if (!isSquareAttacked(homeRow, 5, piece.color.opposite())
                            && !isSquareAttacked(homeRow, 6, piece.color.opposite())) {
                        Move m = new Move(row, col, homeRow, 6);
                        m.castleKingSide = true;
                        moves.add(m);
                    }
                }
            }

            Piece rookQueenSide = get(homeRow, 0);
            if (rookQueenSide != null && rookQueenSide.type == PieceType.ROOK &&
                    rookQueenSide.color == piece.color && !rookQueenSide.moved) {
                if (get(homeRow, 1) == null && get(homeRow, 2) == null && get(homeRow, 3) == null) {
                    if (!isSquareAttacked(homeRow, 3, piece.color.opposite())
                            && !isSquareAttacked(homeRow, 2, piece.color.opposite())) {
                        Move m = new Move(row, col, homeRow, 2);
                        m.castleQueenSide = true;
                        moves.add(m);
                    }
                }
            }
        }

        boolean isSquareAttacked(int row, int col, PieceColor byColor) {
            int pawnDir = byColor == PieceColor.WHITE ? -1 : 1;
            int pawnRow = row - pawnDir;

            for (int dc : new int[]{-1, 1}) {
                int pc = col + dc;
                if (inBounds(pawnRow, pc)) {
                    Piece p = get(pawnRow, pc);
                    if (p != null && p.color == byColor && p.type == PieceType.PAWN) {
                        return true;
                    }
                }
            }

            int[][] knightJumps = {{2,1},{2,-1},{-2,1},{-2,-1},{1,2},{1,-2},{-1,2},{-1,-2}};
            for (int[] j : knightJumps) {
                int nr = row + j[0];
                int nc = col + j[1];
                if (!inBounds(nr, nc)) continue;
                Piece p = get(nr, nc);
                if (p != null && p.color == byColor && p.type == PieceType.KNIGHT) {
                    return true;
                }
            }

            int[][] rookDirs = {{1,0},{-1,0},{0,1},{0,-1}};
            for (int[] d : rookDirs) {
                int nr = row + d[0];
                int nc = col + d[1];
                while (inBounds(nr, nc)) {
                    Piece p = get(nr, nc);
                    if (p != null) {
                        if (p.color == byColor && (p.type == PieceType.ROOK || p.type == PieceType.QUEEN)) {
                            return true;
                        }
                        break;
                    }
                    nr += d[0];
                    nc += d[1];
                }
            }

            int[][] bishopDirs = {{1,1},{1,-1},{-1,1},{-1,-1}};
            for (int[] d : bishopDirs) {
                int nr = row + d[0];
                int nc = col + d[1];
                while (inBounds(nr, nc)) {
                    Piece p = get(nr, nc);
                    if (p != null) {
                        if (p.color == byColor && (p.type == PieceType.BISHOP || p.type == PieceType.QUEEN)) {
                            return true;
                        }
                        break;
                    }
                    nr += d[0];
                    nc += d[1];
                }
            }

            for (int dr = -1; dr <= 1; dr++) {
                for (int dc = -1; dc <= 1; dc++) {
                    if (dr == 0 && dc == 0) continue;
                    int nr = row + dr;
                    int nc = col + dc;
                    if (!inBounds(nr, nc)) continue;
                    Piece p = get(nr, nc);
                    if (p != null && p.color == byColor && p.type == PieceType.KING) {
                        return true;
                    }
                }
            }

            return false;
        }

        boolean isKingInCheck(PieceColor color) {
            for (int r = 0; r < 8; r++) {
                for (int c = 0; c < 8; c++) {
                    Piece p = get(r, c);
                    if (p != null && p.color == color && p.type == PieceType.KING) {
                        return isSquareAttacked(r, c, color.opposite());
                    }
                }
            }
            return false;
        }

        void applyMove(Move move) {
            applyMoveInternal(move);
            turn = turn.opposite();
            updateGameOverState();
        }

        void applyMoveInternal(Move move) {
            Piece piece = get(move.fromRow, move.fromCol);
            if (piece == null) return;

            enPassantRow = -1;
            enPassantCol = -1;

            if (move.enPassant) {
                set(move.capturedRow, move.capturedCol, null);
            }

            if (move.castleKingSide) {
                Piece rook = get(move.fromRow, 7);
                set(move.fromRow, 5, rook);
                set(move.fromRow, 7, null);
                if (rook != null) rook.moved = true;
            }

            if (move.castleQueenSide) {
                Piece rook = get(move.fromRow, 0);
                set(move.fromRow, 3, rook);
                set(move.fromRow, 0, null);
                if (rook != null) rook.moved = true;
            }

            set(move.toRow, move.toCol, piece);
            set(move.fromRow, move.fromCol, null);

            if (piece.type == PieceType.PAWN && Math.abs(move.toRow - move.fromRow) == 2) {
                enPassantRow = (move.toRow + move.fromRow) / 2;
                enPassantCol = move.fromCol;
            }

            piece.moved = true;

            if (piece.type == PieceType.PAWN && move.promotion) {
                piece.type = move.promotionType != null ? move.promotionType : PieceType.QUEEN;
            }
        }

        void updateGameOverState() {
            List<Move> moves = getAllLegalMoves(turn);
            if (moves.isEmpty()) {
                gameOver = true;
                if (isKingInCheck(turn)) {
                    gameOverMessage = (turn == PieceColor.WHITE ? "백" : "흑")
                            + " 체크메이트! "
                            + (turn.opposite() == PieceColor.WHITE ? "백" : "흑")
                            + " 승리";
                } else {
                    gameOverMessage = "스테일메이트! 무승부";
                }
            } else {
                gameOver = false;
                gameOverMessage = "";
            }
        }
    }
}
