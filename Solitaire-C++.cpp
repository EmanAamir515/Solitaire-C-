#include<iostream>
#include<string>
#include <Windows.h>
#include <ctime>
#include <cmath>
#include<cstdio>
#include <windows.h> 
using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
template <class T>
class Card
{
	char rank;
	char suit;
	bool isMoved;
public:
	Card(char r = ' ', char s = ' ', bool m = false)
	{
		rank = r;
		suit = s;
		isMoved = m;
	}
	char getRank()
	{
		return rank;
	}
	bool isRed()
	{
		if (this == nullptr)
		{
			return false;
		}
		return (suit == 'H' || suit == 'D');
	}
	bool isBlack()
	{
		if (this == nullptr)
		{
			return false;
		}
		return (suit == 'S' || suit == 'C');
	}
	char checkColor()
	{
		if (isRed())
			return 'R';
		else if (isBlack())
			return 'B';
		return ' ';
	}
	void setIsMoved(bool mov = true)//comment it and check 
	{
		//if()
		isMoved = mov;
	}

	bool getisMoved()
	{
		return isMoved;
	}
	void printCard()
	{
		//if(isMoved)
		{
			if (isRed())
			{
				SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED);
				cout << rank;
				if (suit == 'H')
					cout << "\u2665";
				else if (suit == 'D')
					cout << "\u2666";
				cout << " ";
			}
			else
			{
				cout << rank;
				if (suit == 'C')
					cout << "\u2663";
				else if (suit == 'S')
					cout << "\u2660";
				cout << " ";
			}
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
		/*else
		{
			SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
			cout << "[]";
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}*/
	}
};
template <class T>
class DLL	//tableau
{
	template <class T>
	class Node
	{
	public:
		T data;
		Node* next;
		Node* prev;
		Node(T d) : data(d), next(nullptr), prev(nullptr) {}
	};
	Node<T>* head;
	Node<T>* tail;
	Node<T>* current;
	int count = 0;
	class ListIterator
	{
	private:
		Node<T>* iptr;
	public:
		typedef ListIterator Iterator;
		ListIterator(Node<T>* ptr = NULL)
		{
			iptr = ptr;
		};
		T& operator*()
		{
			return iptr->data;
		}
		bool operator==(const ListIterator& l) const
		{

			return iptr == l.iptr;

		}
		bool operator!=(const ListIterator& l)
		{

			return !(iptr == l.iptr);

		}
		Node<T>* operator->()	//Card<char>
		{
			return current;
		}
	};
public:
	DLL()
	{
		head = nullptr;
		tail = nullptr;
	}
	ListIterator begin()
	{
		ListIterator I = head;
		return I;
	}
	ListIterator end()
	{
		ListIterator I = tail;
		return I;
	}
	bool isEmpty()
	{
		if (!head)
			return true;
		else
			return false;
	}
	void insertinList(T cards)
	{
		Node<T>* newNode = new Node<T>(cards);

		if (tail == nullptr)
		{
			head = tail = newNode;
		}
		else
		{
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
		count++;
	}
	T removefromList()
	{

		if (tail == nullptr)
		{
			head = nullptr;
			cout << "List is Empty!!!!!" << endl;
			return T();
		}

		Node<T>* temp = tail;
		T deletedData = tail->data;
		if (tail->prev == nullptr)
		{
			head = tail = nullptr;
		}
		else
		{
			tail = tail->prev;
			tail->next = nullptr;
		}
		delete temp;
		count--;
		return deletedData;
	}
	T getTop()
	{
		if (tail != nullptr)
		{
			return tail->data;
		}
		else
		{
			return T();
		}
	}
	void setisMoved(bool m = true)
	{
		if (tail != nullptr)
		{
			tail->data.setIsMoved(m);
		}
	}
	int countCards()
	{
		return count;
	}
	void colPrint(DLL<Card<char>> tableau[], int numColumns)
	{
		bool moreElements = true;
		int row = 0;
		while (moreElements)
		{
			moreElements = false;
			for (int i = 0; i < numColumns; i++)
			{
				Node<T>* temp = tableau[i].head;
				int count = 0;
				while (temp != nullptr && count < row)// to move down the column, one card at a time, until we reach the rowth card in the current column.
				{
					temp = temp->next;
					count++;
				}
				if (temp != nullptr)
				{

					if (temp->next == nullptr || temp->data.getisMoved())
					{
						temp->data.printCard();
					}
					else
					{
						SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
						cout << "[]";
						SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					}

					cout << "\t\t   ";
					moreElements = true;  // There's at least one more element to display in the next row of this column/list
				}
				else
				{
					cout << "\t\t   ";  // Blank space if no more cards in this list 
				}
			}
			cout << endl;
			row++;  // Move to the next row
		}
	}
};
template <class T>
class stack		//foundations, draw, wastepile ,undo
{
	DLL<T> obj; //implementation using DLL
public:
	void push(T card)
	{
		obj.insertinList(card);
	}
	T pop()
	{
		return obj.removefromList();
	}
	T top()
	{
		return obj.getTop();
	}
	bool isEmpty() {
		return obj.isEmpty();
	}
	void setisMoved(bool m = true)
	{
		obj.setisMoved(m);
	}
	/*void setdestAdd()
	{

	}*/
	void print() {
		if (!isEmpty())
		{
			obj.getTop().printCard();
		}
		else
		{
			SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
			cout << "[] ";
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
	}
	void printCount()
	{
		cout << "(" << obj.countCards() << " cards)";
	}
	int getCount()
	{
		return obj.countCards();
	}

};
template <class T>
class command
{
	char type;
	char source;
	int sourceAdd;
	char destination;
	int destAdd;
	int number;

public:
	command(char t = ' ', char src = ' ', int sCol = 0, char dest = ' ', int dCol = 0, int  nCards = 0)
	{
		type = t;
		source = src;
		sourceAdd = sCol;
		destination = dest;
		destAdd = dCol;
		number = nCards;
	}
	char getType()
	{
		return type;
	}
	char getSource()
	{
		return source;
	}
	char getDestination()
	{
		return destination;
	}
	int getSourceAdd()
	{
		return sourceAdd;
	}
	int getdestAdd()
	{
		return destAdd;
	}
	int getNumbers()
	{
		return number;
	}
};
class Game
{
	DLL<Card<char>> tableau[7];		//28 cards in start 
	stack<Card<char>> foundations[4];
	stack<Card<char>> stock;		//24 cards at start
	stack<Card<char>> wastepile;
	stack<command<char>> undoStack;
	bool isOver = false;//if user wants to quit game
public:
	void startGame()
	{
		Card<char> deck[52];
		initialize(deck);
		shuffle(deck, 52);

		int deckIndex = 0;
		for (int col = 0; col < 7; col++)
		{
			for (int row = 0; row <= col; row++)
			{
				tableau[col].insertinList(deck[deckIndex++]);
			}
		}
		for (int i = deckIndex; i < 52; i++)
		{
			stock.push(deck[i]);
		}
	}
	void instructions()
	{
		SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
		cout << "\nGame started!\n Type 's' to draw a card from stock\n Type 'm' for move the (source, destination and number(for number of cards))\n Type 'z' for undo a move or draw operation\n Type 'q' for quitting The Game" << endl;
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	}
	void initialize(Card<char> deck[52])
	{
		const char suits[4] = { 'H', 'D', 'S', 'C' }; // Hearts, Diamonds, Spades, Clubs
		const char ranks[13] = { 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K' };//for ten using T
		int index = 0;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 13; j++)
			{
				deck[index] = Card<char>(ranks[j], suits[i]);
				index++;
			}
		}
	}
	void shuffle(Card<char>deck[52], int total)
	{
		srand(time(0));
		for (int i = 0; i < total; i++)
		{
			int r = i + rand() % (total - i);
			swap(deck[i], deck[r]); // Swap the current card with a randomly chosen one
		}

	}
	void PerformMove(const string data)
	{
		if (data == "s")
		{
			drawCardFromStock();
		}
		else if (data == "z")
		{
			undoMove();
		}
		else if (data == "q")
		{
			isOver = true;
			cout << "\nYou Quitted the Game\n";
		}
		else if (data[0] == 'm')
		{
			char type = data[0];
			char source = data[1];
			int srcAdd = data[2] - '0';
			char destination = data[3];
			int destAdd = data[4] - '0';
			int number = data[5] - '0';
			moveCards(source, srcAdd, destination, destAdd, number);
		}

		else
		{
			cout << "\nInvalid Input!!\n";
		}

	}
	int rankToInt(char rank)//for making ranks easy to compare 
	{
		if (rank >= '2' && rank <= '9')
		{
			return rank - '0';  // Converts '2'-'9' to integer values 2-9
		}
		else if (rank == 'A')
		{
			return 1;
		}
		else if (rank == 'T')
		{
			return 10;
		}
		else if (rank == 'J')
		{
			return 11;
		}
		else if (rank == 'Q')
		{
			return 12;
		}
		else if (rank == 'K')
		{
			return 13;
		}
		return 0;
	}
	void moveMultipleCards(char source, int srcAdd, char destination, int destAdd, int number)
	{
		stack<Card<char>> tempStack;//storing cards temporarily so that they can be put again in correct order
		bool notcorrect = false;
		for (int i = 0; i < number; i++)
		{
			Card<char> movedCard = tableau[srcAdd - 1].removefromList();
			tableau[srcAdd - 1].setisMoved();
			//movedCard.setisMoved(true);
			tempStack.push(movedCard);
		}
		while (!tempStack.isEmpty())//cards that were in tempstack are now push in correct order in destination
		{
			Card<char> destTop = tableau[destAdd - 1].getTop();
			Card<char> movedCard = tempStack.pop();
			if (tableau[destAdd - 1].isEmpty())
			{
				if (movedCard.getRank() == 'K')
				{
					tableau[destAdd - 1].insertinList(movedCard); // Store move to foundation
				}
				else
				{
					cout << "\nCannot Put Anything except K in New Column!!!\n";
				}
			}
			else if ((movedCard.checkColor() != destTop.checkColor()) && (rankToInt(movedCard.getRank()) == (rankToInt(destTop.getRank()) - 1)))
			{
				tableau[destAdd - 1].insertinList(movedCard);
			}
			else
			{
				notcorrect = true;
			}
		}
		if (notcorrect)
		{
			for (int i = 0; i < number; i++)
			{
				Card<char> movedCard = tempStack.pop();
				tableau[srcAdd - 1].insertinList(movedCard);
				tempStack.setisMoved(true);
				tableau[srcAdd - 1].setisMoved(true);
			}
		}
		undoStack.push(command<char>('m', source, srcAdd, destination, destAdd, number));
	}
	void moveCards(char source, int srcAdd, char destination, int destAdd, int  number)
	{
		if (source == 'c' && destination == 'c')
		{
			if (tableau[srcAdd - 1].countCards() >= number)
			{
				Card<char> srcTop = tableau[srcAdd - 1].getTop();
				Card<char> destTop = tableau[destAdd - 1].getTop();
				tableau[destAdd - 1].setisMoved();
				if (number > 1)
				{
					moveMultipleCards(source, srcAdd, destination, destAdd, number);
				}
				else if (tableau[destAdd - 1].isEmpty())
				{
					if (srcTop.getRank() == 'K')///if the top card is K only then it can placed in the empty tableau
					{
						undoStack.push(command<char>('m', source, srcAdd, destination, destAdd, number));
						Card<char> movedCard = tableau[srcAdd - 1].removefromList();
						tableau[srcAdd - 1].setisMoved();
						tableau[destAdd - 1].insertinList(movedCard);
						tableau[destAdd - 1].setisMoved();

					}
					else
					{
						cout << "\nCannot Put Anything except K in New Column!!!\n";
					}
				}
				else if ((srcTop.checkColor() != destTop.checkColor()) && (rankToInt(srcTop.getRank()) == (rankToInt(destTop.getRank()) - 1)))
				{
					undoStack.push(command<char>('m', source, srcAdd, destination, destAdd, number));
					for (int i = 0; i < number; i++)
					{
						Card<char> movedCard = tableau[srcAdd - 1].removefromList();
						tableau[srcAdd - 1].setisMoved();
						tableau[destAdd - 1].insertinList(movedCard);  // Store move to foundation
					}
				}
				else
				{
					cout << "Invalid Input! Cards must alternate in color and one less in rank.\n";
				}
			}
		}
		else if (source == 'w' && destination == 'c')
		{
			if (wastepile.getCount() >= number)
			{
				Card<char> srcTop = wastepile.top();
				Card<char> destTop = tableau[destAdd - 1].getTop();
				tableau[destAdd - 1].setisMoved();
				if (number > 1)
				{
					cout << "\n Cannot move more than one Cards\n";
				}
				if (tableau[destAdd - 1].isEmpty())
				{
					if (srcTop.getRank() == 'K')
					{
						undoStack.push(command<char>('m', source, srcAdd, destination, destAdd, number));
						Card<char> movedCard = wastepile.pop();
						wastepile.setisMoved(true);
						tableau[destAdd - 1].insertinList(movedCard);
						tableau[destAdd - 1].setisMoved();
					}
					else
					{
						cout << "\nCannot Put Anything except K in New Column!!!\n";
					}

				}
				else if ((srcTop.checkColor() != destTop.checkColor()) && (rankToInt(srcTop.getRank())) == (rankToInt(destTop.getRank()) - 1))
				{
					undoStack.push(command<char>('m', source, srcAdd, destination, destAdd, number));
					Card<char> movedCard = wastepile.pop();
					wastepile.setisMoved();
					tableau[destAdd - 1].insertinList(movedCard);
					tableau[destAdd - 1].setisMoved();
				}
				else
				{
					cout << "Invalid Input! Cards must alternate in color and one less in rank.\n";
				}
			}
		}
		else if (source == 'c' && destination == 'f')
		{
			if (tableau[srcAdd - 1].countCards() >= number)
			{
				bool put = false;
				Card<char> srcTop = tableau[srcAdd - 1].getTop();
				Card<char> destTop = foundations[destAdd - 1].top();
				tableau[srcAdd - 1].setisMoved();
				//foundations[destAdd - 1].setisMoved();
				if (number > 1)
				{
					cout << "\n Cannot move more than one Cards\n";
				}
				if ((srcTop.getRank()) == 'A')//empty foundation can be filled with A only then in ascending order
				{
					Card<char> movedCard = tableau[srcAdd - 1].removefromList();
					for (int i = 0; i < (destAdd - 1); i++)//if the intital foundations are empty they should be filled first 
					{
						if (!put)
						{
							if (foundations[i].isEmpty())
							{
								foundations[i].push(movedCard);
								foundations[i].setisMoved();
								destAdd = i + 1;
								put = true;
							}
						}
					}
					if (!put && foundations[destAdd - 1].isEmpty())//if no preivous foundation is empty and the selected one is also not empty chose another
					{
						foundations[destAdd - 1].push(movedCard);
						foundations[destAdd - 1].setisMoved();
					}
					undoStack.push(command<char>('m', source, srcAdd, destination, destAdd, number));
				}
				else if ((rankToInt(srcTop.getRank()) == rankToInt(destTop.getRank()) + 1 && srcTop.checkColor() == destTop.checkColor()))
				{
					undoStack.push(command<char>('m', source, srcAdd, destination, destAdd, number));
					Card<char> movedCard = tableau[srcAdd - 1].removefromList();
					tableau[srcAdd - 1].setisMoved();
					foundations[destAdd - 1].setisMoved();
					foundations[destAdd - 1].push(movedCard);
				}

				else
				{
					cout << "Invalid Input! Cards must alternate in color and one more in rank.\n";
				}
			}
		}
		else if (source == 'w' && destination == 'f')
		{
			if (wastepile.getCount() >= number)
			{
				bool put = false;
				Card<char> srcTop = wastepile.top();
				Card<char> destTop = foundations[destAdd - 1].top();
				if (number > 1)
				{
					cout << "\n Cannot move more than one Cards\n";
				}
				if ((srcTop.getRank() == 'A' && destTop.getRank() == ' '))
				{

					Card<char> movedCard = wastepile.pop();
					wastepile.setisMoved();
					for (int i = 0; i < (destAdd - 1); i++)
					{
						if (!put)
						{
							if (foundations[i].isEmpty())
							{
								foundations[i].push(movedCard);
								foundations[i].setisMoved();
								destAdd = i + 1;
								put = true;
							}
						}
					}
					if ((!put) && foundations[destAdd - 1].isEmpty())
					{
						foundations[destAdd - 1].push(movedCard);
						foundations[destAdd - 1].setisMoved();
					}
					undoStack.push(command<char>('m', source, srcAdd, destination, destAdd, number));
				}
				else if ((rankToInt(srcTop.getRank()) == rankToInt(destTop.getRank()) + 1 && srcTop.checkColor() == destTop.checkColor()))
				{
					undoStack.push(command<char>('m', source, srcAdd, destination, destAdd, number));
					Card<char> movedCard = wastepile.pop();
					wastepile.setisMoved();
					foundations[destAdd - 1].push(movedCard);
					foundations[destAdd - 1].setisMoved();
					cout << "Move successful!\n";
				}
				else
				{
					cout << "Invalid Input! Cards must alternate in color and follow in rank.\n";
				}
			}
		}
		else if (source == 'f' && destination == 'c')  // Move from foundation back to tableau
		{
			if (foundations[srcAdd - 1].getCount() >= number)
			{
				Card<char> srcTop = foundations[srcAdd - 1].top();
				foundations[srcAdd - 1].setisMoved();
				Card<char> destTop = tableau[destAdd - 1].getTop();
				tableau[destAdd - 1].setisMoved();

				if ((srcTop.checkColor() != destTop.checkColor()) && (rankToInt(srcTop.getRank()) == rankToInt(destTop.getRank()) - 1))
				{
					undoStack.push(command<char>('m', source, srcAdd, destination, destAdd, number));
					Card<char> movedCard = foundations[srcAdd - 1].pop();
					foundations[srcAdd - 1].setisMoved();
					tableau[destAdd - 1].insertinList(movedCard);
				}
				else
				{
					cout << "Invalid move! Cards must alternate in color and one more in rank.\n";
				}
			}
		}
		else
		{
			cout << "\nInvalid move!\n" << endl;
		}

	}
	void drawCardFromStock()
	{
		if (!stock.isEmpty())
		{
			Card<char> drawnCard = stock.top();
			stock.setisMoved();
			wastepile.push(drawnCard);
			stock.pop();
			undoStack.push(command<char>('s'));
		}
		else if (stock.isEmpty() && !gameWon())//if the stock is empty and game is still not finished the refill the stock with elements of wastepile
		{
			Card<char> srcTop = wastepile.top();
			Card<char> destTop = stock.top();
			int total = wastepile.getCount();
			for (int i = 0; i < total; i++)
			{
				Card<char> movedCard = wastepile.pop();
				stock.push(movedCard);
			}
			//after being set again
			if (!stock.isEmpty())
			{
				Card<char> drawnCard = stock.top();
				stock.setisMoved();
				wastepile.push(drawnCard);
				stock.pop();
				undoStack.push(command<char>('s'));
			}
		}
		else
		{
			cout << "\nStock is empty!\n" << endl;
		}


	}

	void undoMove()
	{
		if (!undoStack.isEmpty())
		{
			command<char> lastCommand = undoStack.top();
			undoStack.pop();
			char type = lastCommand.getType();
			char source = lastCommand.getSource();
			char destination = lastCommand.getDestination();
			int srcAdd = lastCommand.getSourceAdd();
			int destAdd = lastCommand.getdestAdd();
			int number = lastCommand.getNumbers();
			if (type == 's')
			{
				Card<char> movedCard = wastepile.pop();
				wastepile.setisMoved(false);
				stock.push(movedCard);
			}
			else if (type == 'm')
			{
				Card<char> temp = tableau[srcAdd - 1].getTop();
				tableau[srcAdd - 1].setisMoved(false);
				if (source == 'c' && destination == 'c')
				{
					stack<Card<char>> tempStack;
					for (int i = 0; i < number; i++)//using tempstack again for correct order 
					{
						Card<char> movedCard = tableau[destAdd - 1].removefromList();
						tempStack.push(movedCard);
					}
					if (!tableau[destAdd - 1].isEmpty())
					{
						tableau[srcAdd - 1].setisMoved(false);

					}
					while (!tempStack.isEmpty())
					{
						Card<char> movedCard = tempStack.pop();
						tableau[srcAdd - 1].insertinList(movedCard);
					}
					tableau[srcAdd - 1].setisMoved(true);
				}
				else if (source == 'w' && destination == 'c')
				{
					Card<char> movedCard = tableau[destAdd - 1].removefromList();
					wastepile.push(movedCard);
					wastepile.setisMoved();
					if (!tableau[destAdd - 1].isEmpty())
					{
						tableau[destAdd - 1].setisMoved(false);
					}
				}
				else if (source == 'c' && destination == 'f')
				{
					tableau[srcAdd - 1].setisMoved(false);
					foundations[destAdd - 1].setisMoved(false);
					Card<char> movedCard = foundations[destAdd - 1].pop();
					tableau[srcAdd - 1].insertinList(movedCard);
					tableau[srcAdd - 1].setisMoved(true);
				}
				else if (source == 'w' && destination == 'f')
				{
					Card<char> movedCard = foundations[destAdd - 1].pop();
					foundations[destAdd - 1].setisMoved(false);
					wastepile.push(movedCard);
					wastepile.setisMoved();

				}
				else if (source == 'f' && destination == 'c')
				{
					Card<char> movedCard = tableau[destAdd - 1].removefromList();
					foundations[srcAdd - 1].push(movedCard);
					foundations[srcAdd - 1].setisMoved(true);
					if (!tableau[destAdd - 1].isEmpty())
					{
						Card<char> newTailCard = tableau[destAdd - 1].getTop();
						tableau[destAdd - 1].setisMoved(false);
					}
				}
			}
		}
		else
		{
			cout << "\nNo previous move to undo!\n";
		}
	}
	bool foundationIsEmpty()
	{
		for (int i = 0; i < 4; i++)
		{
			if (foundations[i].isEmpty() || foundations[i].getCount() != 13)
			{
				return false;
			}
		}
		return true;
	}
	bool gameWon()
	{
		int count = 0;
		for (int i = 0; i < 7; i++)
		{
			if (tableau[i].isEmpty())
				count++;
		}
		if (foundationIsEmpty() && stock.isEmpty() && wastepile.isEmpty() && count == 7)
		{
			SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN);
			cout << "\nYou have won the Game\n";
			SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			return true;
		}
		return false;
	}
	bool isGameOver()
	{
		if (gameWon() || isOver == true)//isOver if user quits the game
		{
			return true;
		}
		return false;
	}
	void printState()
	{
		SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED);
		cout << "Stock \t\t Waste \t\t\t\t Foundation 1 \t Foundation 2 \t Foundation 3 \t Foundation 4\n";
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
		cout << "  []";
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout << "\t\t   ";
		wastepile.print();
		cout << "\t\t\t\t\t";
		for (int i = 0; i < 4; i++)
		{
			foundations[i].print();
			cout << "\t\t";
		}
		cout << endl;
		stock.printCount();
		cout << " \t ";
		wastepile.printCount();
		cout << "\t\t\t ";
		for (int i = 0; i < 4; i++)
		{
			foundations[i].printCount();
			cout << "\t  ";
		}
		cout << endl << endl;
		for (int i = 0; i < 7; i++)
		{
			SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			cout << "Column " << i + 1 << " \t";
		}
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout << endl;
		for (int i = 0; i < 7; i++)
		{
			cout << "(" << tableau[i].countCards() << " cards) \t";

		}
		cout << endl;
		tableau->colPrint(tableau, 7);
	}
};
int main()
{
	Game Solitaire;

	SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN);
	cout << "\t\t\t\t\t    SOLITAIRE  :  \n\n";
	SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	Solitaire.startGame();
	SetConsoleOutputCP(65001);
	Solitaire.instructions();
	string Move;
	while (!Solitaire.isGameOver())//printing the game and taking input until user quits or winsGame
	{
		Solitaire.printState();
		cout << "\nEnter your Move : ";
		cin >> Move;
		cout << endl;
		Solitaire.PerformMove(Move);
	}
}