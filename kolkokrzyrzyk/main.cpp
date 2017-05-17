#include <iostream>
// diagram klas
// singleplayer z randomem
// potem graficznie
// logowac ruchy( plik txt ) i potem ewentualnie wczytac
// nie dodaje wyniku dla graczy

using namespace std;

class Player{
    string nick;
    char playersChar;
    int numOfwins = 0;
    int numOfloses = 0;
    int numOfDraws = 0;

    public:
    void set_nick(string playerNick ){
        this->nick = playerNick;
    }

    int get_num_of_wins(){
        return numOfwins;
    }

    int get_num_of_loses(){
        return numOfloses;
    }

    int get_num_of_draws(){
        return numOfDraws;
    }

    char get_players_char(){
        return playersChar;
    }

    string get_nick(){
        return nick;
    }

    void set_players_char(char playersChar){
        this->playersChar = playersChar;
    }

    void round_won(){
        this->numOfwins++;
    }

    void round_lost(){
        this->numOfloses++;
    }

    void round_drawn(){
        this->numOfDraws++;
    }
};

class Board{
    char boardData[9];
    string correctMoves[9] = {"a1", "a2", "a3", "b1", "b2", "b3", "c1", "c2", "c3"};

    int get_int_move(string moveLocation){
        int moveInt;
        char moveLocationLetter = moveLocation[0];
        if ( moveLocationLetter == 'a' ) {
            moveInt = (int)moveLocation[1] - '0' -1;
        }
        else if ( moveLocationLetter == 'b'){
            moveInt = ((int)moveLocation[1] - '0') + 2;
        }
        else if ( moveLocationLetter == 'c'){
            moveInt = ((int)moveLocation[1] - '0') + 5;
        }

        return moveInt;
    }

    void set_move_on_board(int moveInt, char playersChar){
        boardData[ moveInt ] = playersChar;
    }

    public:
    void fill_board(){
        for (int i = 0; i < 9; i++ ){
            boardData[i] = '_';
        }
    }

    bool is_full_board(){
        bool fullBoard = true;
        for (int i = 0; i < 9; i++){
            if (boardData[i] == '_'){
                fullBoard = false;
                break;
            }
        }
        return fullBoard;
    }

    void draw_board(){
        cout << endl << "  1 2 3 " << endl;
        cout << "A ";
        for (int i = 0; i < 3; i++){
            cout << boardData[i] << " ";
        }
        cout << endl;
        cout << "B ";
        for (int i = 3; i < 6; i++){
            cout << boardData[i] << " ";
        }
        cout << endl;
        cout << "C ";
        for (int i = 6; i < 9; i++){
            cout << boardData[i] << " ";
        }
        cout << endl << endl;
    }

    // returns true if moveLocation is correct
    bool check_move(string moveLocation){
        bool correctMove = false;
        for (int i = 0; i < 9; i++){
            if ( moveLocation == correctMoves[i]){
                if ( boardData[i] == '_'){
                    correctMove = true;
                    break;
                }
            }
        }
        return correctMove;
    }

    void move(string moveLocation, char playersChar){
        int moveInt = get_int_move( moveLocation );
        set_move_on_board( moveInt, playersChar );
    }

    bool is_win( char playersChar ){
        bool win = false;

        if ( (boardData[0] == playersChar && boardData[1] == playersChar && boardData[2] == playersChar) ||
             (boardData[3] == playersChar && boardData[4] == playersChar && boardData[5] == playersChar) ||
             (boardData[6] == playersChar && boardData[7] == playersChar && boardData[8] == playersChar) ||

             (boardData[0] == playersChar && boardData[3] == playersChar && boardData[6] == playersChar) ||
             (boardData[1] == playersChar && boardData[4] == playersChar && boardData[7] == playersChar) ||
             (boardData[2] == playersChar && boardData[5] == playersChar && boardData[8] == playersChar) ||

             (boardData[0] == playersChar && boardData[4] == playersChar && boardData[8] == playersChar) ||
             (boardData[2] == playersChar && boardData[4] == playersChar && boardData[6] == playersChar)
            )
            {
                win = true;
            }
        return win;
    }

};

Player new_player(char playersChar){
    Player p;
    string nick;
    cout << "Podaj swoj nick: " << endl;
    cin >> nick;
    cout << endl;
    p.set_nick( nick );
    p.set_players_char( playersChar );

    return p;
}

void new_round(Player playerTab[2], Board b1, int startingPlayer){ // przekazac tablice playerow jako argument
    b1.draw_board();
    bool win = false;
    int numOfMoves = 0;
    bool fullBoard = false;
    while ( !win && !fullBoard ){
        Player player = playerTab[ (numOfMoves + startingPlayer -1)  % 2 ];

        cout << "Gracz: " << player.get_nick() << endl << "Znak: " << player.get_players_char() << endl;

        string playersMove;
        cout << "Miejsce postawienia znaku: ";
        cin >>  playersMove;

        bool correctMove = b1.check_move( playersMove );
        if (correctMove){
            char playersChar = player.get_players_char();
            b1.move(playersMove, playersChar);
            b1.draw_board();
            if (b1.is_win(playersChar)){
                cout << "Gracz " << player.get_nick() << " wygrywa!" << endl;
                player.round_won();
                Player player2 = playerTab[ (numOfMoves + startingPlayer )  % 2 ];
                player2.round_lost();
                win = true;
            }
            fullBoard = b1.is_full_board();
            if (fullBoard){
                cout << "Koniec gry. Remis" << endl;
                player.round_drawn();
                Player player2 = playerTab[ (numOfMoves + startingPlayer )  % 2 ];
                player2.round_drawn();
            }
            numOfMoves++;
        } else { cout << "Podales zla lokacje" << endl; }
    }
}

void show_start_game_info(){
    cout << "Gra w kolko i krzyzyk" << endl << endl;
    cout << "Wstawiaj znaki wpisujac pozycje znaku np.: a1, b2, c1, c3, itd..." << endl;
}

Board init_board(){
    Board b1;
    b1.fill_board();

    return b1;
}

void show_player_scores(Player p){
    cout << "Wins: " << p.get_num_of_wins() << endl;
    cout << "Loses: " << p.get_num_of_loses() << endl;
    cout << "Draws: " << p.get_num_of_draws() << endl;
}

void show_all_scores(Player playersTab[2]){
    Player p1 = playersTab[0];
    cout << p1.get_nick() << endl;
    show_player_scores( p1 );

    Player p2 = playersTab[1];
    cout << p2.get_nick() << endl;
    show_player_scores( p2 );
}

void start_game( Player playersTab[2], Board b1 ){
    bool game = true;
    int round = 0;
    while (game){
        round++;
        cout << "Runda " << round << endl;
        new_round( playersTab, b1, round);
        cout << "Nastepna runda? t/n" << endl;
        char nextRound;
        cin >> nextRound;

        if ( nextRound == 'n'){
            game = false;
        }
        show_all_scores( playersTab );
    }
}

int main()
{
    show_start_game_info();

    cout << "Gracz 1" << endl;
    Player p1 = new_player( 'X' );

    cout << "Gracz 2" << endl;
    Player p2 = new_player( 'O' );

    Board b1 = init_board();

    Player playerTab[2] = {p1, p2};

    start_game(playerTab, b1);

    return 0;
}
