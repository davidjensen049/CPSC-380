#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <pthread.h>
#include <sstream>
#include <string>
#include <ctime>
#include <algorithm>
//#include <omp.h>



using namespace std;

//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//pthread_cond_t cond[THREAD_LIMIT];
void thisisSudoku();
bool isGood(int grid[] [9]);
void printGrid(int grid[9] [9]);
//bool find(int grid[9] [9]);
bool readFile(string file_Name, int grid[9][9]);
bool checkRow(int grid [9][9]);
bool checkColumns(int grid [9][9]);
bool subSquare(int grid[9][9]);
void printOptions();
int smallColumn();
int smallRow();
int successorColumn();
int successorRow();
//int repeat;
//bool validate = "";
bool status,statusB,statusC;
//int column;
//int row;
//string container[9];


string file_Name;




int main(int argc, char** argv)
{

	int grid [9][9];

	char decision = '*';
	while (decision != 'B')
	{
		printOptions();
		cin >> decision;
		switch (toupper (decision))
		{
			case 'C': if (!subSquare(grid))
			break;

			case 'E': if (!checkColumns(grid))
			break;

			else;
				
			case'A': cout << "Please enter the files name" << endl;
			cin >> file_Name; //files name
			if (!readFile(file_Name, grid))
				cout << "sorry, but that is an invalid input!" << endl;
			break;

			case 'F': printGrid (grid);
			break;



			case 'G': if(checkColumns(grid), checkRow(grid))
			cout <<'D' << 'E' <<'F' << endl;
			break;

			case 'D': if(!checkRow(grid))
			break;

			else

			cout << "Congratulations, all of the rows are correct " << endl;

			case 'B': break;
			default: 
			cout << "Sorry, but that isnt valid " << endl;
		
		}
	}
	return 0;
	}

//#pragma omp parallel set_num_threads(3)


	
	bool readFile(string file_Name, int grid[9][9]) {
	string line;	
	int lineCount = 0;
	int row_c = 0;
	int col_c = 0;
	ifstream myFile (file_Name);
	if(myFile.is_open())
	cout << file_Name << endl;
	//fileRoot.open(file_Name);

	if(!myFile){
		cout << "error " << endl;
		return false;
	
		}

		while(getline(myFile, line)) {
			for(int i = 0; i < line.size(); ++i)
			{
				if(line[i] != ',')
				{
					grid[row_c][col_c] = line[i];
					++col_c;
				}
			}
			++row_c;
			col_c = 0;
			
			}
	return true;
}


		/*if (!fileRoot.eof())
		{
			while(fileRoot >>grid[i][j])
		{
		for(int i = 0; i < 9; ++i) 
		
		for (int j = 0; j < 9; ++j)
				cout << i + j << endl;
				//>> grid[i][j];
				//cout << fileRoot << endl;
			cout << "Processed file Sucessfully; Please select an option from below now." << endl;
		}
		return true;

	}

*/



	/*if (isGood(grid))

	cout << "This works: " << endl;

	else 
		cout << "no good: " << endl;
	cout << "Accepted the file" << endl;
	return 0;
}
*/
	


	
//#pragma omp parallel for 
	void printGrid(int grid [9] [9]) 
	{
		#pragma omp parallel num_threads(10)
		for (int row = 0; row < 9; ++row) 
		{
			for (int col = 0; col < 9; ++col)
			{
				cout << grid[row][col] << ""; //fill rows with spaces
		}
		cout << endl;
			//cout << "made it this far " << endl;
			//clear();
		}
	}
	
	
	void printOptions()
	{
		cout << "\n\tWelcome - This is the Sudoku Solution Validator, Please make a selection from the chat selection below " << endl << endl;
		cout << "\tA\t Load file" << endl;
		cout << "\tB\t Terminate the program " << endl;
		cout << "\tC\t Check Subsquare" << endl;
		cout << "\tD\t Check Rows" << endl;
		cout << "\tE\t Check columns" << endl;
		cout << "\tF\t Display the grid" << endl;
		cout << "\tG\t Check Grid, Columns & Subsquare" << endl;
		cout << "\n\tPlease be mindful, the hierarchical listing above is case sensitive " << endl;
		cout << endl;
	}



//#pragma omp parallel for 

	bool checkRow(int grid[][9])
	{


#pragma omp parallel num_threads(10)
		bool status = true;
		int row;
		int column;
		for (int row = 0; row < 9; ++row)
		{
			for(int validate = 1; validate < 9; ++validate)
			{
				int repeat = 0;
			for (int column = 0; column < 9; ++column)
			{
				if (grid[row][column] == validate)
				{
					++repeat;
				}
			}
			if(repeat > 1)
			{
				cout << "Row " << row  <<" Is wrong, please fix " << endl;
				status = false;
			}
		}
	}
		return status;
		//clear();
}


//#pragma omp parallel for 
	bool checkColumns(int grid [][9])
	{
		//#pragma omp parallel num_threads(10)
		bool statusB = true;
		int column_b;
		int row_b;

		for (int column_b = 0; column_b < 9; ++ column_b)
		{
			for (int validate =1  ; validate < 9; ++validate)
			{
				int repeat = 0;
			for (int row_b = 0; row_b < 9; ++row_b)
			{
				if(grid[row_b][column_b] == validate)
				{
					++repeat;
				}
			}
			if (repeat > 1)
			{
				cout << "Column " << column_b << " not correct " << endl;
				statusB = false;
			}
		}
	}
	return statusB;
	//clear();
}

bool subSquare(int grid[][9]){
	#pragma omp parallel num_threads(10)
	bool statusC = true;
	int array[9];

	for (int row = 0; row < 9; ++row){
		for (int column = 0; column < 9; ++column){
			int repeat = 0;
			int smallRow = (row/3)*3;
			int smallColumn =(column/3)*3;

			for (int successorColumn = 0; successorColumn < smallColumn; ++successorColumn){
				for (int successorRow = 0; successorRow < smallRow; ++successorRow){
					array[8] = grid[row][column];
					if(grid[successorRow][successorColumn] == array[8])
					{
						++repeat;
					}
				}
			}
			if(repeat > 1){
				cout <<"Sorry, the Subsquare is incorrect: row " << row << " column " << column <<"." << endl;
				statusC = false;
			}
		}
	}
	return statusC;
}


 




/*
	//bool checkColumns(int grid [][9]);


	 bool isGood(int grid [] [9])

	 {
		int j, i;
		bool run;
		run = true;
		cout << " made it to the isgood constructor" << endl;
		for (int column = 0; column < 9; ++column)
			if (column != j && grid[i] [column] == grid[i] [j])
				run = false;

			cout << "This was the first run: " << run << endl;
			
		

		for (int i = 0; i < 9; ++i)
		
			for (int j = 0; j < 9; ++j)
				if ((grid [i][j] > 9) || (grid [i][j] < 0))
					run = false;

				cout << "made it to the last loop" << endl;

				return run;
		
	}




	


while (true)
	{
		
		if (fileRoot == "0")
		{
			cout << "Thank you for using Solver, Goodbye: " << endl;
			return 0;
			
		}
		

			else
			{
				cout << "File undable to open, please try again: " << endl;

				return 0;
			}

	void numRows(fileRoot, result);
	{
		int list = newList;
		ofstream fileRoot;
		fileRoot.is_open();

		for line in fileRoot;
			for i in line;
			if (i = "," || i = "\n") 
			{
				
				continue;
				
				else
				{
					newList.append(int(i))
					return (newList);

				}

			}
		}
	}
}






(if(argc == 2){
	grid.open(argv[1], ios::in);
	if (grid.is_open()){
		for (int i = 0; i < design; ++ i)
			for (int j = 0; i < design ++ j)
				grid >> sudoku[i][j];
			cout << sudoku << endl;
	}


	cout << "Please enter the name of your file: " endl;
	cin >> file;
	int grid = new int [9][9];
	

	while (file.hasNext()){
		try{
			for (int i = 0; i < 9; ++i)
			{
				for (int j = 0; j < 9 ++j)
				{
					grid[i][j] = file.hasNext();
					cout << grid[i][j] + "" << endl;

				}
			}
		}
	}
	*/


