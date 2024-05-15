#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stack>

using namespace std;

int** initialize(int** board, int size);

void display(int** board, int size);
void assignPosition(int** board, int x, int y, int value);
void sortBoard(int** board, stack<int> *r, stack<int> *c, int size);
void backtracking(int** board, int &x, int &y, int size);

bool conflictBoard(int** board, int size, int x, int y);
bool testPositions(int** board, int &x, int &y, int z, int size);

int filled(int** board, int size);

stack<int> r;
stack<int> c;

int main(){

	int size = 8;
	int** board = initialize(board, size);

//	stack<int> r;
//	stack<int> c;

	sortBoard(board, &r, &c, size);
}

int** initialize(int** board, int size){

	board = new int*[size];

	for(int i = 0; i < size; i++){

		board[i] = new int[size];

		for(int j = 0; j < size; j++){

			board[i][j] = 0;
		}
	}

	return board;
}

void display(int** board, int size){

	for(int i = 0; i < size; i++){

		for(int j = 0; j < size; j++){

			if(board[j][i] == 0){

				cout << "0" << "|";
			}

			else{

				cout << "1" << "|";
			}
		}

		cout << endl;
	}
}

void assignPosition(int** board, int x, int y, int value){

	board[x][y] = value;
}

void sortBoard(int** board, stack<int> *r, stack<int> *c, int size){

	int x = 0;
	int y = 0;

	c->push(x);
	r->push(y);

	assignPosition(board, x, y, 1);

	display(board, size);

	cout << endl;

	while(conflictBoard(board, size, x, y) || filled(board, size) != (size*size)){

		if(!conflictBoard(board, size, x, y)){

			y = r->top() + 1;
			x = c->top() + 2;

			c->push(x);
			r->push(y);

			assignPosition(board, x, y, 1);
			display(board, size);

			cout << x << endl;
			cout << y << endl;
		}

		else if(conflictBoard(board, size, x, y) && x+2 >= size || y+1 >= size - 1){

			cout << x << endl;

			cout << y << endl;

			c->push(x+2);
			r->push(y+1);

			int a = 0;
			if(x+2  >= size - 1 || y+1 >= size - 1){

				r->pop();
				c->pop();

				x = c->top();
				y = r->top();

				a++;
			}

			y = r->top() + 2;
			x = c->top() + 1;

			if(x >= size || board[x][y] == 1){

				x = c->top() - 1;

				if(board[x][y] == 1){

					x = c->top() - 2;
					y = r->top() + 1;
				}
			}

			if(y >= size){

				if(r->top() < size - 1 && c->top() > 1){

					y = r->top() + 1;	
					x = c->top() - 2;

					if(board[x][y] == 1){

						x = c->top() - 1;
						y = r->top() - 2;
					}
					
				}

				else if(c->top() < 1){

					x = c->top() + 1;
					y = r->top() - 2;

					if(board[x][y] == 1){

						int counter = 1;
						
						cout << "NOTICE ME" << endl;
						while(board[x][y] == 1){

							x = c->top();
							y = r->top();
							
							cout << x << endl;
							cout << y << endl;

							assignPosition(board, x, y, 0);

							c->pop();
							r->pop();

							while(counter < 9){

								if(testPositions(board, x, y, counter, size)){

									counter++;
								}
								else{

									counter = 10;
								}

							}

							counter = 1;
						}

						cout << x << endl;
						cout << y << endl;
					}
				}

				else if(c->top() == 1){

					x = c->top() - 1;
					y = r->top() - 2;
				}

				else{

					y = r->top() - 1;
					x = c->top() - 2;

					if(board[x][y] == 1){

						x = c->top() - 1;
						y = r->top() - 2;
					}

					if(board[x][y] == 1){

						x = c->top() + 1;
						y = r->top() - 2;

						if(board[x][y] == 1){

							cout << "ENTERED" << endl;

							backtracking(board, x, y, size);

							cout << x << endl;
							cout << y << endl;
						}
					}
					
				}
			}

			assignPosition(board, x, y, 1);
			display(board,size);

			r->push(y);
			c->push(x);
		}

		else{

			x = c->top() - 2;
			y = r->top() - 1;

			if(x < 0){

				x = c->top() + 1;
				y = r->top() + 2;
			}

			if(board[x][y] == 1){

				x = c->top() - 1;
				y = r->top() + 2;

				if(board[x][y] == 1){

					int counter = 1;

					while(board[x][y] == 1){

						x = c->top();
						y = r->top();

						assignPosition(board, x, y, 0);

						c->pop();
						r->pop();

						while(counter < 9){

							if(testPositions(board, x, y, counter, size)){

								counter++;
							}

							else{

								counter = 10;
							}
						}

						counter = 1;
					}
				}
			}

			assignPosition(board, x, y, 1);
			display(board,size);

			c->push(x);
			r->push(y);

			cout << "conflict" << endl;

			cout << x << endl;

			cout << y << endl;

		}

/*		else if(conflictBoard(board, size, x, y) && y+2 >= size - 1){

			c->push(x+1);
			r->push(y+2);

			if(y+2 >= size - 1){

				r->pop();
				c->pop();
			}

			x = 
		}
*/
		cout << endl;
	}

}

void backtracking(int** board, int &x, int &y, int size){

	int counter = 1;

	cout << "GOING IN" << endl;
	while(board[x][y] == 1){

		x = c.top();
		y = r.top();

		assignPosition(board, x, y, 0);

		display(board, size);

		c.pop();
		r.pop();
//Last left off board gets changed at 3,7 to zero but somehow gets changed back to 1 thus resulting in an infinite loop
//
		while(counter < 9){

			if(testPositions(board, x, y, counter, size)){

				counter++;
			}

			else{

				counter = 10;
			}
		}

		counter = 1;
	}
}

bool conflictBoard(int** board, int size, int x, int y){

	if(x+2 >= size || y+1 >= size || board[x+2][y+1] == 1){

		return true;
	}

	return false;
}

bool testPositions(int** board, int &x, int &y, int z, int size){

	if(z == 1){

		x = c.top() + 2;
		y = r.top() + 1;

		if(board[x][y] == 1 || y >= size){

			return true;
		}

		else{

			return false;
		}
	}

	else if(z == 2){

		x = c.top() + 1;
		y = r.top() + 2;

		if(board[x][y] == 1 || y >= size){
			
			return true;
		}

		else{
			return false;
		}
	}

	else if(z == 3){

		x = c.top() + 2;
		y = r.top() - 1;

		if(board[x][y] == 1){

			return true;
		}

		else{

			return false;
		}
	}

	else if(z == 4){

		x = c.top() - 1;
		y = r.top() + 2;
		
		if(board[x][y] == 1 || y >= size || x < 0){

			return true;
		}

		else{

			return false;
		}
	}

	else if(z == 5){

		x = c.top() - 2;
		y = r.top() + 1;

		if(board[x][y] == 1 || y >= size || x < 0){

			return true;
		}

		else{

			return false;
		}
	}

	else if(z == 6){

		x = c.top() + 1;
		y = r.top() - 2;

		if(board[x][y] == 1){

			return true;
		}

		else{

			return false;
		}
	}

	else if(z == 7){

		x = c.top() - 2;
		y = r.top() - 1;

		if(board[x][y] == 1 || x < 0){

			return true;
		}

		else{

			return false;
		}
	}

	else if(z == 8){

		x = c.top() - 2;
		y = r.top() - 1;

		if(board[x][y] == 1 || x < 0){

			return true;
		}

		else{

			return false;
		}
	}

	else{

		return false;
	}
}

/*bool c_r(int** board, int r, int size){

	int a = 0;

	for(int j = 0; j < size; j++){

		if(board[r][j] == 1)

			a++;
	}
}*/

int filled(int** board, int size){

	int a = 0;

	for(int r = 0; r < size; r++){

		for(int c = 0; c < size; c++){

			if(board[r][c] == 1){

				a++;
			}
		}
	}

	return a;
}
