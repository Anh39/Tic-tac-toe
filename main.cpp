#include <iostream>
#include <vector>
using namespace std;
//state representation
typedef vector<vector<char> > State;
int const size=3;

//isFinalState: check if game is end
//input:State
//output:true if end | false if not-end
bool isFinalState(State game)
{
    //check rows
    for (int i=0;i<size;i++)
    {
        if (game[i][0] == game[i][1] && game[i][0] == game[i][2] && game[i][0] !=' ' ) return true;

    }
    //check columns
    for (int i=0;i<size;i++)
    {
        if (game[0][i] == game[1][i] && game[0][i] == game[2][i] && game[0][i] !=' ' ) return true;

    }
    //check diagonal
    if (game[0][0] == game[1][1] && game[1][1] == game[2][2] && game[1][1] !=' ') return true;
    if (game[0][2] == game[1][1] && game[1][1] == game[2][0] && game[1][1] !=' ') return true;
    //check fulls
    for (int i=0;i<size;i++)
    {
        for (int j=0;j<size;j++)
        {
            if (game[i][j]==' ') return false;
        }
    }
    return true;
}
//nextPlayer: check next player
//input:State
//output: X or O
char nextPlayer(State game)
{
    int count_X=0,count_O=0;
    for (int i=0;i<size;i++)
    {
        for (int j=0;j<size;j++)
        {
            if (game[i][j]=='X')
            {
                count_X++;
            }
            else if (game[i][j]=='O')
            {
                count_O++;
            }
        }
    }
    if (count_X>count_O)
    {
        return 'O';
    }
    else return 'X';
}
//winner: check winner
//input:State
//output: X or O if win/lose | ' ' if draw
char winner(State game)
{
    //check rows
    for (int i=0;i<size;i++)
    {
        if (game[i][0] == game[i][1] && game[i][0] == game[i][2] && game[i][0] !=' ' ) return game[i][0];

    }
    //check columns
    for (int i=0;i<size;i++)
    {
        if (game[0][i] == game[1][i] && game[0][i] == game[2][i] && game[0][i] !=' ' ) return game[0][i];

    }
    //check diagonal
    if (game[0][0] == game[1][1] && game[1][1] == game[2][2] && game[1][1] !=' ') return game[1][1];
    if (game[0][2] == game[1][1] && game[1][1] == game[2][0] && game[1][1] !=' ') return game[1][1];
    return 'D'; // draw
}
//render: render game
//input: State
//output: print game to screen
void render(State game)
{
    for (int i=0;i<size;i++)
    {
        cout << '|';
        for (int j=0;j<size;j++)
        {
            cout << game[i][j] << '|';
        }
        cout << endl;
    }
    cout << endl;
}
//getNewState: get a new valid state
//input:state,coordinate,
//output: state
State getNewState(State game,int i,int j)
{
    State newState=game;
    newState[i][j]=nextPlayer(game);
    return newState;
}
//getStates: get all valid states
//input: State
//output: all States available
vector <State> getStates(State game)
{
    vector<State> States;
    for (int i=0;i<size;i++)
    {
        for (int j=0;j<size;j++)
        {
            if (game[i][j]==' ')
            {
                States.push_back(getNewState(game,i,j));
            }
        }
    }
    return States;
}
//finalStateScore: check score of final state
//input: final state
//output: score
int finalStateScore (State game)
{
    //check current player
    int multipler=0;
    if (nextPlayer(game)=='X')
    {
        multipler=-1;
    }
    else
    {
        multipler=1;
    }
    //check rows
    for (int i=0;i<size;i++)
    {
        if (game[i][0] == game[i][1] && game[i][0] == game[i][2] && game[i][0] !=' ' ) return 1*multipler;

    }
    //check columns
    for (int i=0;i<size;i++)
    {
        if (game[0][i] == game[1][i] && game[0][i] == game[2][i] && game[0][i] !=' ' ) return 1*multipler;

    }
    //check diagonal
    if (game[0][0] == game[1][1] && game[1][1] == game[2][2] && game[1][1] !=' ') return 1*multipler;
    if (game[0][2] == game[1][1] && game[1][1] == game[2][0] && game[1][1] !=' ') return 1*multipler;
    //check fulls
    return 0;
}
//getScore: check score of not final state
//input: state
//output: state and score of state
pair <int,State> getScore(State game)
{
    if (isFinalState(game))
    {
        return make_pair(finalStateScore(game),game);
    }
    char player=nextPlayer(game);
    vector<State> States=getStates(game);
    int NO_VALUE=-100;
    int bestScore=NO_VALUE;
    State bestState;
    for (State newState : States)
    {
        int score=getScore(newState).first;
        if (player=='X')
        {
            if (bestScore<score || bestScore==NO_VALUE)
            {
                bestScore=score;
                bestState=newState;
            }
        }
        else
        {
            if (bestScore>score || bestScore==NO_VALUE)
            {
                bestScore=score;
                bestState=newState;
            }
        }
    }
    return make_pair(bestScore,bestState);
}
//machineTurn: make computer play
//input:State
//output:State
State machineTurn(State game)
{
    State bestState=getScore(game).second;
    for (int i=0;i<size;i++)
    {
        for (int j=0;j<size;j++)
        {
            if (game[i][j]!=bestState[i][j])
            {
                game[i][j]=bestState[i][j];
            }
        }
    }
    return game;
}
//playerTurn: player play
//input:State, coordinate from player
//output:State
State playerTurn(State &game)
{
    int i=0,j=0;
    cin >> i >> j;
    if (game[i-1][j-1]=='X' || game[i-1][j-1]=='O')
    {
        cout << "Invalid move" << endl << "Please type again" << endl;
        return playerTurn(game);
    }
    game[i-1][j-1]='X';
    return game;
}
//endGame:
//input: State
//output: show win or lose
void endGame(State game)
{
    if (winner(game)=='X')
    {
        cout << "You win";
    }
    else if (winner(game)=='O')
    {
        cout << "You lose";
    }
    else
    {
        cout << "Draw";
    }
}
int main()
{
    State g(size,vector<char> (size,' '));
    /*g[0][0]=' ';g[0][1]=' ';g[0][2]=' '; // check
    g[1][0]=' ';g[1][1]=' ';g[1][2]=' ';
    g[2][0]=' ';g[2][1]=' ';g[2][2]=' ';*/
    //render (machineTurn(g)); //check render()

    //cout << nextPlayer(g); // check nextPlayer()

    //cout << finalStateScore(g) << endl;  //check finalStateScore()

    //cout << winner(g) << endl; //check winner()

    /*vector <State> States=getStates(g);  //check getStates()
    cout << "start" << endl;
    for (int i=0;i<3;i++)
    {
        render(States[i]);
        cout<< getScore(g).first << endl;  //check getScore()
    }*/
    //render(getScore(g).second);
    cout << "Let's start." << endl;
    render(g);
    loop:
    while (true)
    {
        cout << "Your turn: " << endl;
        g=playerTurn(g);
        render(g);
        if (isFinalState(g))
        {
            endGame(g);
            return 0;
        }
        cout << "I play: " << endl;
        g=machineTurn(g);
        render(g);
        if (isFinalState(g))
        {
            endGame(g);
            return 0;
        }
    }
}
