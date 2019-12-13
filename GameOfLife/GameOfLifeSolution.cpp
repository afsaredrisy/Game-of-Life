#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
using namespace std;
static const int DEAD = 0;
static const int LIVE = 1;
static const int ROWS = 5;
static const int COLS =5;
static int input [ROWS][COLS] = {{DEAD, DEAD, DEAD, DEAD, DEAD},
                    	{LIVE, LIVE, LIVE, DEAD, DEAD},
                         {DEAD, DEAD, DEAD, DEAD, DEAD},
                         {DEAD, DEAD, DEAD, DEAD, DEAD},
                         {DEAD, DEAD, DEAD, DEAD, DEAD}};
class InputReader{
	ifstream myReadFile;
	char *str;
	public: InputReader(char* fileName){
		this->str = fileName;
	}
	//InputReader();
	public: void readInput(){
		std::string line;
		myReadFile.open(str);
		 if (myReadFile.is_open()) {
		 	int i,j;
		 	while(std::getline( myReadFile, line)){
 			std::istringstream iss(line);
 			iss >> i;
 			iss >> j;
 			input[i][j] = LIVE;
 			}
		 
	}
		myReadFile.close();
	}
	
};

class GameOfLife{
	
	
	
	public: void solve(){
		for (int i = 0 ; i < ROWS ; i++) {
			getNextBoard();
		}
		printOutput();
	}
	
	public: void printOutput(){
		for(int i=0;i<ROWS;i++){
			for(int j=0;j<COLS;j++){
				if(input[i][j] == LIVE){
					cout<<i<<"  "<<j<<endl;
				}
				//cout<<input[i][j];
			}
			//cout<<endl;
		}
	}
	
	private:  getNextBoard(){
		
		int nrRows = ROWS;
		int nrCols = COLS;
		int temp [ROWS][COLS];
		
		 for (int row = 0 ; row < nrRows ; row++) {
	
            for (int col = 0 ; col < nrCols ; col++) {
                temp[row][col] = getNewCellState(input[row][col], getLiveNeighbours(row, col));
            }
        }  
		
		for(int i=0; i<ROWS; i++){
			for(int j=0;j<COLS;j++){
				input[i][j] = temp [i][j];
			}
		} 
		
	}
	
	private: int getNewCellState(int curState, int liveNeighbours) {
		
		int newState = curState;
		
		switch (curState) {
			case LIVE:
				 if (liveNeighbours < 2) {
                newState = DEAD;
            }
            if (liveNeighbours == 2 || liveNeighbours == 3) {
                newState = LIVE;
            }
            
             if (liveNeighbours > 3) {
                newState = DEAD;
            }
            break;
             case DEAD:
            if (liveNeighbours == 3) {
                newState = LIVE;
            }
            break;		
		
		}
		return newState;
	}
	
	 private: int getLiveNeighbours(int cellRow, int cellCol) {
	
        int liveNeighbours = 0;
        int rowEnd = min(ROWS , cellRow + 2);
        int colEnd = min(COLS, cellCol + 2);

        for (int row = max(0, cellRow - 1) ; row < rowEnd ; row++) {
            for (int col = max(0, cellCol - 1) ; col < colEnd ; col++) {
                if ((row != cellRow || col != cellCol) && input[row][col] == LIVE) {
                    liveNeighbours++;
                }
            }
        }
        //cout<<"returning "<<liveNeighbours;
        return liveNeighbours;
    }
    
    private: int min(int x, int y){
    	return (x>y)?y:x;
	}

	private: int max(int x, int y){
		return (x>y)?x:y;
	}
	
};


class Test{
	
	private: char *fileName;
	
	public: Test(char * fileName){
		this->fileName = fileName;	
	}
	
	public: bool testFileInput(){
		InputReader rder(fileName);
		rder.readInput();
		GameOfLife game;
		game.solve();
	}
	
};
int main(){
		InputReader rder();
		Test test("/input1.txt");
		test.testFileInput();
		return 0;
	}


