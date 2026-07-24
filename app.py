from flask import Flask, render_template, request, jsonify
import subprocess


app = Flask(__name__)


# Initial board
board = [
    "1", "2", "3",
    "4", "5", "6",
    "7", "8", "9"
]


# Current game mode
game_mode = 0


# Current player
current_player = "X"


# Game status
game_over = False


def reset_board():

    global board
    global current_player
    global game_over

    board = [
        "1", "2", "3",
        "4", "5", "6",
        "7", "8", "9"
    ]

    current_player = "X"

    game_over = False


def run_c_game(action, position=None, player=None):

    board_string = "".join(board)


    command = [
        "TicTacToe_Web.exe",
        board_string,
        action
    ]


    if position is not None:
        command.append(str(position))


    if player is not None:
        command.append(player)


    result = subprocess.run(
        command,
        capture_output=True,
        text=True
    )


    return result.stdout.strip()


@app.route("/")
def home():

    return render_template("index.html")


@app.route("/api/start", methods=["POST"])
def start_game():

    global game_mode

    data = request.get_json()

    game_mode = int(data.get("mode", 1))


    reset_board()


    return jsonify({
        "board": board,
        "message": "Player 1 (X) turn",
        "game_over": False
    })


@app.route("/api/move", methods=["POST"])
def make_move():

    global board
    global current_player
    global game_over


    if game_over:

        return jsonify({
            "error": "Game is already over."
        }), 400


    data = request.get_json()

    position = int(data.get("position"))


    # -----------------------------------------
    # PLAYER VS PLAYER
    # -----------------------------------------

    if game_mode == 1:

        result = run_c_game(
            "move",
            position,
            current_player
        )


        parts = result.split("|")


        status = parts[0]


        if status == "INVALID":

            return jsonify({
                "error": "Invalid move."
            }), 400


        # Get updated board
        board = list(parts[2])


        # Player won
        if status == "WIN":

            game_over = True


            if current_player == "X":

                message = "Player 1 (X) wins!"

            else:

                message = "Player 2 (O) wins!"


            return jsonify({
                "board": board,
                "message": message,
                "game_over": True
            })


        # Draw
        if status == "DRAW":

            game_over = True


            return jsonify({
                "board": board,
                "message": "It's a draw!",
                "game_over": True
            })


        # Switch player
        if current_player == "X":

            current_player = "O"

            message = "Player 2 (O) turn"

        else:

            current_player = "X"

            message = "Player 1 (X) turn"


        return jsonify({
            "board": board,
            "message": message,
            "game_over": False
        })


    # -----------------------------------------
    # PLAYER VS COMPUTER
    # -----------------------------------------

    if game_mode == 2:

        # Player X move
        result = run_c_game(
            "move",
            position,
            "X"
        )


        parts = result.split("|")


        status = parts[0]


        if status == "INVALID":

            return jsonify({
                "error": "Invalid move."
            }), 400


        # Update board
        board = list(parts[2])


        # Player wins
        if status == "WIN":

            game_over = True


            return jsonify({
                "board": board,
                "message": "Congratulations! You win!",
                "game_over": True
            })


        # Draw
        if status == "DRAW":

            game_over = True


            return jsonify({
                "board": board,
                "message": "It's a draw!",
                "game_over": True
            })


        # -----------------------------------------
        # COMPUTER MOVE
        # -----------------------------------------

        computer_result = run_c_game(
            "computer"
        )


        computer_parts = computer_result.split("|")


        computer_status = computer_parts[0]


        # Update board after computer move
        board = list(computer_parts[3])


        # Computer wins
        if computer_status == "WIN":

            game_over = True


            return jsonify({
                "board": board,
                "message": "Computer wins!",
                "game_over": True
            })


        # Draw
        if computer_status == "DRAW":

            game_over = True


            return jsonify({
                "board": board,
                "message": "It's a draw!",
                "game_over": True
            })


        return jsonify({
            "board": board,
            "message": "Your turn (X)",
            "game_over": False
        })


    return jsonify({
        "error": "Please select a game mode first."
    }), 400


@app.route("/api/reset", methods=["POST"])
def reset_game():

    reset_board()


    return jsonify({
        "board": board,
        "message": "Game reset.",
        "game_over": False
    })


if __name__ == "__main__":

    app.run(debug=True)