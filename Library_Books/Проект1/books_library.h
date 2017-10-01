#define _CRT_SECURE_NO_WARNINGS
#pragma once
#ifndef BOOKSLIBRARY_H
#define BOOKSLIBRARY_H

#include <iostream>
#include <string.h>
#include <conio.h>

#define SEPARATOR "-"
#define MAX_LEN_NAME 20
#define DATE_STR_LEN 11

using namespace std;

enum CompareCondition
{
	IS_EQUAL,//For search
	IS_MORE, //For sort Descenning
	IS_LESS  //For sort Ascenning
};

struct Date
{
	unsigned day;
	unsigned month;
	unsigned year;
};

struct Autor
{
	int id;
	char name[MAX_LEN_NAME];
};

struct Genre
{
	int id;
	char name[MAX_LEN_NAME];
};

struct Book
{
	int id;
	char name[MAX_LEN_NAME];
	int autorId;
	int genreId;

	int dataEdit;
	int rate;
	int price;

};

struct Reader
{
	int id;
	char name[MAX_LEN_NAME];
	char surname[MAX_LEN_NAME];
	char patronic[MAX_LEN_NAME];
	char dataBirth[DATE_STR_LEN];

	int idPasp;
	int numReadBook;
	int amountBook;

};


struct RequestResult
{
	unsigned size = 0;
	unsigned *result = nullptr;
};

struct BooksOnHands
{
	int idReader;
	int idBook;

	Date dataIssueBook;
	Date dataReturnBook;
};

//***************************************  TOOLS   ***************************************
template<typename T>
void copyArray(const T* src, T* dst, unsigned size);

template<typename T>
void parseIdName(T &dataStruct, char* str);

CompareCondition compare(char const* str1, char const* str2);
CompareCondition compare(const int num1, const int num2);

void parseDate(const char *str, Date& date);

int input(const char* title, int from = 0, int to = 0);
void input(const char* title, char* buffer, unsigned size);

//***************************************  FILES   ***************************************

void loadAutors();
void loadGenres();
void loadBooks();
void loadReaders();

void loadBookOnHand();

void loadData();
// *************************************** SAVE  **************************************
void saveData();
void saveAutors();
void saveGenres();
void saveBooks();
void saveReaders();

void saveBookOnHand();

// *************************** BOOKS ************************
void menu();
void menuHandler(int menuItem);

void menuBooks();
void menuBooksHandler(int menuItem);

void subEditingBookMenu();
void subEditingBookMenuHandler(int menuItem);

void editingBookFull();
void editingBookPart();

void menuReaders();
void menuReadersHandler(int menuItem);

void subMenu();

void submenuSortBook();
void subMenuSearchBook();

void subMenuBooksHandler(int menuItem);
void subMenuSortHandler(int menuItem);
void subMenuSearchBooksHandler(int menuItem);

void menuBooksHandler(int menuItem);

//void submenuBook();
// *********************************************************  READERS *********************

void menuReadHandler(int menuItem);

void subEditingReadMenu();
void subEditingReadMenuHandler(int menuItem);

void editingPartRearder();
void editingFullRearder();

void subMenuReaders();

void subMenuSearchReaders();
void subMenuSearchReadHandler(int menuItem);

void subMenuSortReaders();
void subMenuSortReadHandler(int menuItem);

void subMenuReadersHandler(int menuItem);


void delay();

//Action by library books
void showLibBooks();
void addBook();
void addBookLib();
void removeBook();
void editBook();
void searchSortBook();
void givBook();
void returnBook();
void showPopGenr();
void bookHendRead();
void penStitch();

void addAutor();

// ********************************************************
// Sub menu Book
void searchBookAutor();
void searchBookName();
void searchBookGenre();
void searchRatingBook();

//Search books on hand
void searchBooksOnHands(int readerId);
void showListBooksOnHand(int readerId);
//---------------------------------

void showDateBookSearch(int i);
void showListSearchBook(int i);

void showDateBookSearch();
void showListSearchBook();

void sortBookAutor();
void sortBookName();
void sortBookGenre();
void sortRatingBook();

// Sub menu READER
void searchReaderSurNamePatr();
void searchNumRead();
void searchIdPasp();

void showDateReaderSearch(int i);
void showListSearchRead(int i);

void showDateReaderSearch();
void showListSearchRead();

void sortReadSurNamePatr();
void sortNumRead();
void sortIdPasport();

// ***********************************************************
//Action by readers
void showReaders();
void addRead();
void addReadsLib();
void removeRead();
void editRed();
void activeRed();
void showReadersStitch();

void exitFromMenu();

// ************************* SORT **************************************************************
CompareCondition bookNameCondition(int i, int j);
CompareCondition bookAutorCondition(int i, int j);
CompareCondition bookGenreCondition(int i, int j);
CompareCondition bookRatingCondition(int i, int j);

CompareCondition readSurNameCondition(int i, int j);
CompareCondition readNumCondition(int i, int j);
CompareCondition readIdPaspCondition(int i, int j);

void doSortBook(CompareCondition(*conditionFunct)(int, int), CompareCondition condition = IS_LESS);
void doSortRead(CompareCondition(*conditionFunct)(int, int), CompareCondition condition = IS_LESS);

RequestResult* doSearch(CompareCondition(*conditionFunct)(int, int), CompareCondition condition = IS_EQUAL);

// ************************* CATALOG   *********************************************************

template<typename T>
void showCatalog(const T* catalog, int count);

//**************************************
template<typename T>
const char* getName(const int id, T catalogue, int count)
{
	const char* result = { "Not found!" };
	for (int i = 0; i < count; i++)
	{
		if (catalogue[i].id == id)
		{
			result = catalogue[i].name;
			break;
		}
	}
	return result;
}

//}

#endif // BOOKSLIBRARY_H
