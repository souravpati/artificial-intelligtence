You will be provided sample inputs and outputs (see below). Please understand that the goal of the samples is to check that you can correctly parse the problem definitions, and generate a correctly formatted output. The samples are very simple and it should not be assumed that if your program works on the samples it will work on all test cases. There will be more complex test cases and it is your task to make sure that your program will work correctly on any valid input. 
<br />

Rules of the game
The Fruit Rage is a two player game in which each player tries to maximize his/her share from a batch of fruits randomly placed in a box. The box is divided into cells and each cell is either empty or filled with one fruit of a specific type.
At the beginning of each game, all cells are filled with fruits. Players play in turn and can pick a cell of the box in their own turn and claim all fruit of the same type, in all cells that are connected to the selected cell through horizontal and vertical paths. For each selection or move the agent is rewarded a numeric value which is the square of the number of fruits claimed in that move. Once an agent picks the fruits from the cells, their empty place will be filled with other fruits on top of them (which fall down due to gravity), if any. In this game, no fruit is added during game play. Hence, players play until all fruits have been claimed.
Another big constraint of this game is that every agent has a limited amount of time to spend for thinking during the whole game. Spending more than the original allocated time will be penalized harshly. Each player is allocated a fixed total amount of time. When it is your turn to play, you will also be told how much remaining time you have. The time you take on each move will be subtracted from your total remaining time. If your remaining time reaches zero, your agent will automatically lose the game. Hence you should think about strategies for best use of your time (spend a lot of time on early moves, or on later moves?)
The overall score of each player is the sum of rewards gained for every turn. The game will terminate when there is no fruit left in the box or when a player has run out of time.
Game setup and examples
<br />
<br />

Input: The file input.txt in the current directory of your program will be formatted as follows:
First line: Second line: Third line: Next n lines:
integer n, the width and height of the square board (0 < n £ 26)
integer p, the number of fruit types (0 < p £ 9)
strictly positive floating point number, your remaining time in seconds
the n x n board, with one board row per input file line, and n characters (plus end- of-line marker) on each line. Each character can be either a digit from 0 to p-1, or a * to denote an empty cell. Note: for ease of parsing, the extra horizontal and vertical lines shown in figures 1 – 5 will not be present in the actual input.txt (see below for examples).
Output: The file output.txt which your program creates in the current directory should be formatted as follows:
First line:
Next n lines:
your selected move, represented as two characters:
A letter from A to Z representing the column number (where A is the leftmost column, B is the next one to the right, etc), and
A number from 1 to 26 representing the row number (where 1 is the top row, 2 is the row below it, etc).
the n x n board just after your move and after gravity has been applied to make any fruits fall into holes created by your move taking away some fruits.


<br />
For this input.txt:<br />
2<br />
3 123.6<br /> 
01<br />
21<br />
one possible correct output.txt is:<br />
B1<br />
0*<br />
2*<br />
