#include "books_library.h"

int autorsCount = 0;
int genresCount = 0;

int booksCount = 0;
int readsCount = 0;
int bookOnHandsCount = 0;

CompareCondition sortCondition = IS_LESS;//Ascenning

Autor* autors;
Genre* genres;
Book* libBooks;
Reader* libRead;
BooksOnHands* booksOnHands;

RequestResult *searchResult = nullptr;

void(*prevMenu)();
void(*currentMenu)();

void(*ActionBooks[12])() = { showLibBooks, addBook, removeBook, subEditingBookMenu, subMenu, givBook,
returnBook, showPopGenr, bookHendRead, penStitch, addAutor, exitFromMenu };

void(*ActionReaders[8])() = { showReaders, addRead, removeRead, subEditingReadMenu, subMenuReaders, activeRed, showReadersStitch, exitFromMenu };

void(*ActionSubSortAscendBooks[5])() = { sortBookAutor, sortBookName, sortBookGenre, sortRatingBook, exitFromMenu };
void(*ActionSubSortAscendReaders[4])() = { sortReadSurNamePatr, sortNumRead,  sortIdPasport, exitFromMenu };

void(*ActionSubSearchBooks[5])() = { searchBookAutor, searchBookName, searchBookGenre, searchRatingBook, exitFromMenu };
void(*ActionSubSearcheReaders[4])() = { searchReaderSurNamePatr, searchNumRead, searchIdPasp, exitFromMenu };


void menu()
{
	prevMenu = &menu;
	currentMenu = &menu;

	system("cls");
	cout << "\n ------- Menu books -------" << endl;

	cout << "\n =========================" << endl;
	cout << " 1 - Menu books. " << endl;
	cout << " 2 - Menu readers. " << endl;
	cout << " 3 - Save data in file.\n ";
	cout << "==========================" << endl;

	int item = input(" Select action ", 1, 3);

	menuHandler(item);
}

void menuHandler(int menuItem)
{
	switch (menuItem)
	{
	case 1:
	{
		menuBooks();
		break;
	}
	case 2:
	{
		menuReaders();
		break;
	}
	case 3:
	{
		saveData();
	}
	default:
		break;
	}
}

void menuBooks()
{
	prevMenu = &menu;
	currentMenu = &menuBooks;

	system("cls");
	cout << "\n ------- Menu book -------" << endl;

	cout << " =========================" << endl;
	cout << " 1 - libBooks books. " << endl;
	cout << " 2 - Add book. " << endl;
	cout << " 3 - Remove book. " << endl;
	cout << " 4 - Editing. " << endl;
	cout << " 5 - Searching and Sorting: " << endl;

	cout << " 6  - Issuance of the book. " << endl;
	cout << " 7  - Return book. " << endl;
	cout << " 8  - The most popular books in its genre. " << endl;
	cout << " 9  - Books in the hands of readers. " << endl;
	cout << " 10 - Summa accrued interest. " << endl;
	cout << " 11 - Add Autor !\n";
	cout << " 12 - Exit. " << endl;
	cout << " =========================" << endl;

	int item = input(" Selected action : ", 1, 12);

	menuBooksHandler(item);
}

void menuBooksHandler(int menuItem)
{
	(*ActionBooks[menuItem - 1])();
	delay();

}

void subEditingBookMenu()
{
	prevMenu = &menuBooks;
	currentMenu = &subEditingBookMenu;

	system("cls");
	cout << "\n-------  SubMenu readers Editing -------" << endl;

	cout << " =========================" << endl;
	cout << " 1 - Editing. " << endl;
	cout << " 2 - Exit to previous menu. " << endl;
	cout << " =========================" << endl;

	int item = input(" Selected action : ", 1, 2);
	subEditingBookMenuHandler(item);
}

void subEditingBookMenuHandler(int menuItem)

{

	if (menuItem == 1)
	{
		editingBookPart();
	}
	else
	{
		exitFromMenu();
	}
}

void editingBookPart()
{
	subMenuSearchBook();

	//--------------------------  Name  ---------------------------
	char buffer[26];

	unsigned bookIndex = input("\n\nSelect reader for editing : ", 1, searchResult->size);

	Book &editingBook = libBooks[searchResult->result[bookIndex - 1]];

	cout << "\n\n ************** \n";
	cout << "Book name is: " << editingBook.name << endl;
	input("Enter new name: ", buffer, MAX_LEN_NAME);

	cout << endl;

	if (strlen(buffer) != 0)
	{
		strcpy(editingBook.name, buffer);
	}

	//--------------------------  RATING  ---------------------------

	int ratingBuff;

	cout << "\n ************** \n";
	cout << " Book rating is : " << editingBook.rate << endl;
	ratingBuff = input(" Enter new rating : ", 1, 100);

	cout << endl;
	if (ratingBuff != 0)
	{
		editingBook.rate = ratingBuff;
	}

	//--------------------------  Ganre  ---------------------------

	int genreBuff;

	cout << "\n ************** \n";
	cout << " Book ganre is : " << editingBook.genreId << endl;
	showCatalog(genres, genresCount);
	genreBuff = input(" Enter item -  the genre book : ", 1, genresCount);

	cout << endl;
	if (genreBuff != 0)
	{
		editingBook.genreId = genreBuff;
	}

	//--------------------------  Price  ---------------------------

	int priceBuff;
	cout << "\n ************** \n";
	cout << " Book price is : " << editingBook.price << endl;
	" Enter new price : ";
	priceBuff = input(" Enter new price : ", 1, 10000);

	cout << endl;
	if (priceBuff != 0)
	{
		editingBook.price = priceBuff;
	}

	currentMenu = &subEditingBookMenu;
	delay();
}

void subMenu()
{
	prevMenu = &menuBooks;
	currentMenu = &subMenu;
	int item = 0;

	system("cls");
	cout << "\n ------- Sub menu books -------" << endl << endl;

	cout << " =========================" << endl;
	cout << " 1 - Search books. " << endl;
	cout << " 2 - Sort ascending books. " << endl;
	cout << " 3 - Sort descending books. " << endl;
	cout << " 4 - Return to previous menu. " << endl;
	cout << " 5 - Return to menu. " << endl;
	cout << " =========================" << endl;

	item = input(" Selected action : ", 1, 5);

	subMenuBooksHandler(item);
}

void subMenuBooksHandler(int menuItem)
{
	switch (menuItem)
	{
	case 1:
	{
		subMenuSearchBook();
		break;
	}
	case 2:
	{
		sortCondition = IS_LESS;//Ascenning
		submenuSortBook();
		break;
	}
	case 3:
	{
		sortCondition = IS_MORE;//Descenning
		submenuSortBook();
		break;
	}
	case 4:
	{
		exitFromMenu();
		break;
	}
	case 5:
	{
		prevMenu = &menu;
		exitFromMenu();
		break;
	}

	default:
		break;
	}
}

void submenuSortBook()
{
	prevMenu = &subMenu;
	currentMenu = &submenuSortBook;
	int subitem = 0;

	system("cls");
	cout << endl << "\t -------  Menu sort book -------" << endl;

	cout << "\t =========================" << endl;
	cout << "\t 1 - Autor. " << endl;
	cout << "\t 2 - Name book. " << endl;
	cout << "\t 3 - Genre. " << endl;
	cout << "\t 4 - reating. " << endl;
	cout << "\t 5 - Return to previous menu. " << endl;
	cout << "\t 6 - Return to main menu. " << endl;
	cout << "\t =========================" << endl;

	subitem = input("\t Enter subitem : ", 1, 6);

	subMenuSortHandler(subitem);
}

void subMenuSortHandler(int menuItem)
{
	if (menuItem == 5)
	{
		exitFromMenu();
	}
	else if (menuItem == 6)
	{
		prevMenu = &subMenu;
		exitFromMenu();
	}
	else
	{
		(*ActionSubSortAscendBooks[menuItem - 1])();
		delay();
	}
}

void subMenuSearchBook()
{
	prevMenu = &subMenu;
	currentMenu = &subMenuSearchBook;

	system("cls");
	cout << endl << "\t -------  Menu search book -------" << endl;

	cout << "\t =========================" << endl;
	cout << "\t 1 - Autor. " << endl;
	cout << "\t 2 - Name book. " << endl;
	cout << "\t 3 - Genre. " << endl;
	cout << "\t 4 - reating. " << endl;
	cout << "\t 5 - Return to previous menu. " << endl;
	cout << "\t 6 - Return to main menu. " << endl;
	cout << "\t =========================" << endl;

	int subitem = input("\t Enter subitem : ", 1, 6);

	subMenuSearchBooksHandler(subitem);
}

void subMenuSearchBooksHandler(int menuItem)
{
	if (menuItem == 5)
	{
		exitFromMenu();
	}
	else if (menuItem == 6)
	{
		prevMenu = &menu;
		exitFromMenu();
	}
	else
	{
		(*ActionSubSearchBooks[menuItem - 1])();

	}
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& READERS MENU &&&&&&&&&&&&&&&&

void menuReaders()
{
	prevMenu = &menu;
	currentMenu = &menuReaders;

	system("cls");
	cout << "\n------- Menu readers-------" << endl;

	cout << " =========================" << endl;
	cout << " 1 - Show all readers. " << endl;
	cout << " 2 - Adding reader. " << endl;
	cout << " 3 - Remove reader. " << endl;
	cout << " 4 - Editing. " << endl;
	cout << " 5 - Searching and Sorting: " << endl;

	cout << " 6 - Information about the most active readers. " << endl;
	cout << " 7 - Information about readers with overdue date book return. " << endl;
	cout << " 8 - Exit. " << endl;
	cout << " =========================" << endl;

	int item = input(" Selected action : ", 1, 8);

	menuReadHandler(item);
}

void menuReadHandler(int menuItem)
{
	(*ActionReaders[menuItem - 1])();
	delay();
}

void subEditingReadMenu()
{
	prevMenu = &menuReaders;
	currentMenu = &subEditingReadMenu;

	system("cls");
	cout << "\n-------  SubMenu readers Editing -------" << endl;

	cout << " =========================" << endl;
	cout << " 1 - Editing. " << endl;
	cout << " 2 - Exit to previous menu. " << endl;
	cout << " =========================" << endl;

	int item = input(" Selected action : ", 1, 2);

	subEditingReadMenuHandler(item);
}

void subEditingReadMenuHandler(int menuItem)
{

	if (menuItem == 1)
	{
		editingPartRearder();
	}
	else
	{
		exitFromMenu();
	}
}

void editingPartRearder()
{
	prevMenu = &menuReaders;
	subMenuSearchReaders();

	char bufferName[26];

	unsigned readIndex = input("\n\nSelect reader for editing", 1, searchResult->size);


	// ----------------------  Name -------------------------

	Reader &editingReader = libRead[searchResult->result[readIndex - 1]];

	cout << "\n ************** \n";
	cout << "Reader name is: " << editingReader.name << endl;
	input("Enter new name: ", bufferName, MAX_LEN_NAME);

	if (strlen(bufferName) != 0)
	{
		strcpy(editingReader.name, bufferName);
	}

	// ----------------------  SURNAME -------------------------
	char bufferSurName[26];

	cout << "\n ************** \n";
	cout << "Reader surname is: " << editingReader.surname << endl;

	input("Enter new surname: ", bufferSurName, MAX_LEN_NAME);

	if (strlen(bufferSurName) != 0)
	{
		strcpy(editingReader.surname, bufferSurName);
	}

	// ----------------------  PATRONIC -------------------------
	char bufferPatronic[26];

	cout << "\n ************** \n";
	cout << "Reader patronic is: " << editingReader.surname << endl;
	input("Enter new patronic: ", bufferPatronic, MAX_LEN_NAME);

	if (strlen(bufferPatronic) != 0)
	{
		strcpy(editingReader.patronic, bufferPatronic);
	}

	// ----------------------  DATA_BIRTH -------------------------

	char bufferDataBirth[26];

	cout << "\n ************** \n";
	cout << "Reader data birth is: " << editingReader.dataBirth << endl;
	input("Enter new data birth: ", bufferDataBirth, MAX_LEN_NAME);

	cout << endl;

	if (strlen(bufferDataBirth) != 0)
	{
		strcpy(editingReader.dataBirth, bufferDataBirth);
	}

	currentMenu = &menuReaders;
	delay();
}


void subMenuReaders()
{
	prevMenu = &menuReaders;
	currentMenu = &subMenuReaders;

	system("cls");

	cout << "\n ------- Sub menu readers -------" << endl << endl;

	cout << " =========================" << endl;
	cout << " 1 - Search readers. " << endl;
	cout << " 2 - Sort ascending readers. " << endl;
	cout << " 3 - Sort descending readers. " << endl;
	cout << " 4 - Exit to previous menu. " << endl;
	cout << " 5 - Exit to menu. " << endl;
	cout << " =========================" << endl;

	int item = input(" Select action : ", 1, 5);

	subMenuReadersHandler(item);

}

void subMenuReadersHandler(int menuItem)
{

	switch (menuItem)
	{
	case 1:
	{
		prevMenu = &subMenuReaders;
		subMenuSearchReaders();
		break;
	}
	case 2:
	{
		sortCondition = IS_LESS;//Ascenning
		subMenuSortReaders();
		break;
	}
	case 3:
	{
		sortCondition = IS_MORE;//Descenning
		subMenuSortReaders();
		break;
	}
	case 4:
	{
		exitFromMenu();
		break;
	}
	case 5:
	{
		prevMenu = &menu;
		exitFromMenu();
		break;
	}
	default:
		break;
	}
}

void subMenuSearchReaders()
{
	currentMenu = &subMenuSearchReaders;

	system("cls");
	cout << endl << "\t -------  Menu search readers -------" << endl;

	cout << "\t =========================" << endl;
	cout << "\t 1 - Surname, name, patronyc. " << endl;
	cout << "\t 2 - The number of books read. " << endl;
	cout << "\t 3 - Id Pasport. " << endl;
	cout << "\t 4 - Return to previous menu. " << endl;
	cout << "\t 5 - Exit menu. " << endl;
	cout << "\t =========================" << endl;


	int subitem = input("\t Enter subitem : ", 1, 5);

	subMenuSearchReadHandler(subitem);
}

void subMenuSearchReadHandler(int menuItem)
{
	if (menuItem == 4)
	{
		exitFromMenu();
	}
	else if (menuItem == 5)
	{
		prevMenu = &menu;
		exitFromMenu();
	}
	else
	{
		(*ActionSubSearcheReaders[menuItem - 1])();
	}
}

void subMenuSortReaders()
{
	prevMenu = &subMenuReaders;
	currentMenu = &subMenuSortReaders;

	system("cls");
	cout << endl << "\t -------  Menu sort readers -------" << endl;

	cout << "\t =========================" << endl;
	cout << "\t 1 - Surname, name, patronyc. " << endl;
	cout << "\t 2 - The number of books read. " << endl;
	cout << "\t 3 - Id Pasport. " << endl;
	cout << "\t 4 - Return to previous menu. " << endl;
	cout << "\t 5 - Exit menu. " << endl;
	cout << "\t =========================" << endl;

	int subitem = input("\t Enter subitem : ", 1, 5);

	subMenuSortReadHandler(subitem);
}

void subMenuSortReadHandler(int menuItem)
{
	if (menuItem == 4)
	{
		exitFromMenu();
	}
	else if (menuItem == 5)
	{
		prevMenu = &menu;
		exitFromMenu();
	}
	else
	{
		(*ActionSubSortAscendReaders[menuItem - 1])();
		delay();
	}
}


// ************************************ LIB_BOOK *********************************
void showLibBooks()
{
	cout << endl << " SHOW ALL libBooks BOOK : ";
	cout << "\n============================" << endl << endl;
	cout << "|-------------------------------------------------------------------------------|\n";
	cout << "| ID\t| Name \t\t| AutorName\t| Ganre \t| Date\t| Rate\t| Price\t|\n";

	cout << "|-------------------------------------------------------------------------------|\n" << endl;

	for (int i = 0; i < booksCount; i++)
	{
		cout << "| " << libBooks[i].id << " \t";
		cout << "| " << libBooks[i].name << "   \t";
		cout << "| " << getName(libBooks[i].autorId, autors, autorsCount) << "   \t";
		cout << "| " << getName(libBooks[i].genreId, genres, genresCount) << "   \t";
		cout << "| " << libBooks[i].dataEdit << " \t";
		cout << "| " << libBooks[i].rate << " \t";
		cout << "| " << libBooks[i].price << "\t|\n";

	}
	cout << endl;
}

void addBook()
{
	int countBook = input("\n Enter amount books : ");

	Book* tmp = new Book[booksCount + countBook];

	copyArray(libBooks, tmp, booksCount);

	for (int j = booksCount; j < booksCount + countBook; j++)
	{
		cout << endl << " ENTER DATE ABOUT BOOK : ";
		cout << "\n============================" << endl << endl;

		input(" Enter name book : ", tmp[j].name, MAX_LEN_NAME);
		cout << " Enter autor book : \n";
		showCatalog(autors, autorsCount);
		tmp[j].autorId = input(" Select ID autor : ");
		cout << " Enter ganre book : \n";
		showCatalog(genres, genresCount);
		tmp[j].genreId = input(" Select ID ganre : ");
		tmp[j].dataEdit = input(" Enter data edit book (1999) : ", 1800, 2017);
		tmp[j].price = input(" Enter price book : ", 10, 10000);
		tmp[j].rate = input(" Enter rating book :", 1, 100);

		tmp[j].id = j + 1;
		cout << endl;
	}
	booksCount += countBook;

	delete[] libBooks;
	libBooks = tmp;
}

void addBookLib()
{
	addBook();
}

void removeBook()
{
	bool isFound = false;
	char name[25];
	int index = -1;

	Book* tmp = new Book[booksCount - 1];

	input("\n Enter name book : ", name, MAX_LEN_NAME);

	for (int i = 0; i < booksCount; i++)
	{
		tmp[i] = libBooks[i];
		if (strcmp(libBooks[i].name, name) == 0)
		{
			index = i;
			isFound = true;
			break;
		}
	}

	if (isFound)
	{
		bool isOnHands = false;

		for (int i = 0; i < bookOnHandsCount; i++)
		{
			if (booksOnHands[i].idBook == libBooks[index].id && booksOnHands[i].dataReturnBook.day == 0)
			{
				isOnHands = true;
				break;
			}
		}

		if (!isOnHands)
		{
			for (int i = index; i < booksCount - 1; i++)
			{
				tmp[i] = libBooks[i + 1];
			}

			booksCount--;
			delete[] libBooks;
			libBooks = tmp;
		}
		else
		{
			cout << "The book " << name << " is issued reader!!!\n";
			delete[] tmp;
		}
	}
	else
	{
		cout << "The book " << name << " not found!!!\n";
		delete[] tmp;
	}

	delay();
}
//############################################################################################

void givBook()
{

	// ---------------------  Selecting Reader ----------------------
	prevMenu = &menuBooks;
	subMenuSearchReaders();

	BooksOnHands* tmp = new BooksOnHands[bookOnHandsCount + 1];
	copyArray(booksOnHands, tmp, bookOnHandsCount);

	unsigned selectedIndex = input("\nSelect reader : ", 1, searchResult->size);

	Reader& selectedReader = libRead[searchResult->result[selectedIndex - 1]];

	tmp[bookOnHandsCount].idReader = selectedReader.id;
	selectedReader.amountBook++;

	// ------------------------ Selecting BOOK from books on hands ----------------------

	subMenuSearchBook();

	selectedIndex = input("\n\nSelect book: ", 1, searchResult->size);

	Book& selectedBook = libBooks[searchResult->result[selectedIndex - 1]];

	tmp[bookOnHandsCount].idBook = selectedBook.id;

	// --------------------  Enter date ------------------------------
	char bufferData[26];
	cout << "\n ************** \n";
	input("Enter date of issue book reader : ", bufferData, MAX_LEN_NAME);

	if (strlen(bufferData) != 0)
	{
		parseDate(bufferData, tmp[bookOnHandsCount].dataIssueBook);
	}

	parseDate("0.0.0", tmp[bookOnHandsCount].dataReturnBook);


	//-----------------------
	delete[] booksOnHands;
	booksOnHands = tmp;

	bookOnHandsCount++;

	currentMenu = &menuBooks;
	delay();
}

// ****************************************************************************************************

void returnBook()
{
	// ---------------------  Selecting Reader ----------------------
	prevMenu = &menuBooks;
	subMenuSearchReaders();

	unsigned selectedIndex = 0;
	selectedIndex = input("\nSelect reader : ", 1, readsCount);

	Reader& selectedReader = libRead[searchResult->result[selectedIndex - 1]];

	// ------------------------ Selecting BOOK ----------------------

	currentMenu = &menuBooks;
	cout << " ------------------------ Book ------------------ ";
	searchBooksOnHands(selectedReader.id);

	selectedIndex = input("\n\nSelect book: ", 1, booksCount);

	BooksOnHands& selectedBook = booksOnHands[searchResult->result[selectedIndex - 1]];

	// --------------------  Enter returned date ------------------------------
	char bufferData[26];
	cout << "\n ************** \n";
	input("Enter date return book reader : ", bufferData, MAX_LEN_NAME);

	if (strlen(bufferData) != 0)
	{
		parseDate(bufferData, selectedBook.dataReturnBook);
	}

	delay();
}

void showPopGenr()
{
	int max = 0, maxNum = -1;
	int popGenreId;

	cout << endl << " --- The most popular book for genre --- " << endl << endl;
	cout << " Enter the genre of the book: ";

	showCatalog(genres, genresCount);

	popGenreId = input(" Select ID ganre : ");

	for (int i = 0; i < booksCount; i++)
	{
		if (popGenreId == libBooks[i].genreId)
		{
			if (libBooks[i].rate > max)
			{
				max = libBooks[i].rate;
				maxNum = i;
			}
		}
	}
	if (maxNum != -1)
	{

		cout << " THE  MOST  THE POPULAR BOOK IN THE GENRE: ";
		cout << "\n============================" << endl;
		cout << " Edit date         : " << libBooks[maxNum].dataEdit << endl;
		cout << " Name book         : " << libBooks[maxNum].name << endl;
		cout << " Autor's name      : " << getName(libBooks[maxNum].autorId, autors, autorsCount) << endl;
		cout << " Ganre of book     : " << getName(libBooks[maxNum].genreId, genres, genresCount) << endl;
		cout << " Price             : " << libBooks[maxNum].price << endl;
		cout << " Popular reting    : " << libBooks[maxNum].rate << endl;
		cout << " Id number of book : " << libBooks[maxNum].id << endl;
		cout << "\n============================" << endl;
	}
	else
	{
		cout << endl << " No book for this genres be found." << endl;
	}
	delay();
}

void bookHendRead()
{
	cout << "\n| ID Reader\t | ID Book\t | Data issue book |";
	cout << "\n|---------------------------------------------------------\n";
	for (int i = 0; i < bookOnHandsCount - 1; i++)
	{
		if (booksOnHands[i].dataReturnBook.day == 0)
		{
			cout << "| " << getName(booksOnHands[i].idReader, libRead, readsCount) << " \t | "
				<< getName(booksOnHands[i].idBook, libBooks, booksCount) << " \t | "
				<< booksOnHands[i].dataIssueBook.day << "." << booksOnHands[i].dataIssueBook.month << "."
				<< booksOnHands[i].dataIssueBook.year << "\n";
		}
	}
	cout << endl;
}

void penStitch()
{}

void addAutor()
{
	Autor* tmp = new Autor[autorsCount + 1];
	copyArray(autors, tmp, autorsCount);
	tmp[autorsCount].id = autorsCount + 1;

	input(" Enter Autor : ", tmp[autorsCount].name, autorsCount);

	autorsCount++;

	delete[] autors;
	autors = tmp;
}


// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// **********************************   ACTION BY READERS **********************

void showReaders()
{
	cout << endl << " SHOW ALL READERS : ";
	cout << "\n============================" << endl;
	cout << "|-------------------------------------------------------------------------------------------------------|\n";
	cout << "| ID\t| Name\t\t| Surname\t| Patronic\t| Data Birth\t| Id pasport\t| Readed books\t|\n";

	cout << "|-------------------------------------------------------------------------------------------------------|\n";

	for (int i = 0; i < readsCount; i++)
	{
		cout << "| " << libRead[i].id << " \t";
		cout << "| " << libRead[i].name << "   \t";
		cout << "| " << libRead[i].surname << "   \t";
		cout << "| " << libRead[i].patronic << "   \t";
		cout << "| " << libRead[i].dataBirth << "   \t";
		cout << "| " << libRead[i].idPasp << " \t";
		cout << "| " << libRead[i].numReadBook << "   \t\t|\n";

	}
	cout << endl;
}

void addRead()
{
	cout << "\n Enter amount readers : ";
	int countRead = input("\n Enter amount readers : ");

	Reader* tmp = new Reader[readsCount + countRead];
	copyArray(libRead, tmp, readsCount);

	for (int i = readsCount; i < readsCount + countRead; i++)
	{

		tmp[i].id = i + 1;
		input(" Enter name readers : ", tmp[i].name, MAX_LEN_NAME);
		input(" Enter surname readers : ", tmp[i].surname, MAX_LEN_NAME);
		input(" Enter patronic readers : ", tmp[i].patronic, MAX_LEN_NAME);
		input(" Enter data birth readers(01.01.1981) : ", tmp[i].dataBirth, DATE_STR_LEN);
		tmp[i].idPasp = input(" Enter ID pasport readers : ");

		tmp[i].numReadBook = 0;

		cout << endl;
	}
	readsCount += countRead;

	delete[] libRead;
	libRead = tmp;

}
void addReadsLib()
{
	addRead();
}

void removeRead()
{
	bool isFound = false;

	char surname[10];
	char name[10];
	char patronic[15];
	int index = -1;

	cout << " Enter name reader : ";
	input(" Enter name reader : ", name, MAX_LEN_NAME);
	input(" Enter surname reader : ", surname, MAX_LEN_NAME);
	input(" Enter patronic reader : ", patronic, MAX_LEN_NAME);

	Reader* tmp = new Reader[readsCount - 1];

	for (int i = 0; i < readsCount - 1; i++)
	{
		tmp[i] = libRead[i];
		if ((strcmp(libRead[i].surname, surname) == 0) && (strcmp(libRead[i].name, name) == 0) && (strcmp(libRead[i].patronic, patronic) == 0))
		{
			index = i;
			isFound = true;
			break;
		}
	}



	if (isFound)
	{
		for (int i = index; i < readsCount - 1; i++)
		{
			tmp[i] = libRead[i + 1];
		}
		readsCount--;
		delete[] libRead;
		libRead = tmp;

	}
	else
	{
		cout << "The reader " << surname << " not found!!!\n";
		delete[] tmp;
	}

	delay();

}

void activeRed()
{
	const int AMOUNT_READER = 5;

	sortCondition = IS_MORE;
	doSortRead(&readNumCondition, sortCondition);

	cout << "\n -------------- The most active readers ----------------";
	cout << "\n| Name\t\t| SurName\t| Patronic\t| Amount reds book\t|";
	cout << "\n---------------------------------------------------------\n";
	for (int i = 0; i < AMOUNT_READER; i++)
	{
		cout << "| " << libRead[i].name << " \t";
		cout << "| " << libRead[i].surname << "   \t";
		cout << "| " << libRead[i].patronic << "   \t";
		cout << "| " << libRead[i].numReadBook << "\t \n";
	}
	cout << endl;


}
void showReadersStitch()
{}


// *************** SEARCH BOOK ********************
void searchBookAutor()
{
	showCatalog(autors, autorsCount);

	int authorId;
	authorId = input("\n Enter ID - the name author book for search : ");

	bool isFound = false;
	cout << endl;

	searchResult = new RequestResult;

	unsigned buffer[1024];

	for (int i = 0; i < booksCount; i++)
	{
		if (libBooks[i].autorId == authorId)
		{
			buffer[searchResult->size] = i;
			searchResult->size++;
			isFound = true;
		}
	}

	searchResult->result = new unsigned[searchResult->size];
	copyArray(buffer, searchResult->result, searchResult->size);

	if (isFound)
	{
		showListSearchBook();
	}
	else
	{
		cout << "The book whith the produser -" << authorId << "- not  found!!!\n";
		delay();
	}

}

void searchBookName()
{
	char name[20];
	input("\n Enter the name book for search : ", name, MAX_LEN_NAME);
	bool isFound = false;

	searchResult = new RequestResult;

	unsigned buffer[1024];

	for (int i = 0; i < booksCount; i++)
	{
		if (strcmp(name, libBooks[i].name) == 0)
		{
			buffer[searchResult->size] = i;
			searchResult->size++;
			isFound = true;
		}
	}

	searchResult->result = new unsigned[searchResult->size];
	copyArray(buffer, searchResult->result, searchResult->size);

	if (isFound)
	{
		cout << " Search by name book: ";
		showListSearchBook();
	}
	else
	{
		cout << "The book -" << name << "- not found!!!\n";
		delay();
	}

}

void searchBookGenre()
{
	showCatalog(genres, genresCount);

	int genreId = input("\n Enter item -  the genre book for search : ", 1, genresCount);
	bool isFound = false;

	searchResult = new RequestResult;

	unsigned buffer[1024];

	for (int i = 0; i < booksCount; i++)
	{
		if (libBooks[i].genreId == genreId)
		{
			buffer[searchResult->size] = i;
			searchResult->size++;

			isFound = true;
		}
	}

	searchResult->result = new unsigned[searchResult->size];
	copyArray(buffer, searchResult->result, searchResult->size);

	if (isFound)
	{
		cout << " Search by ganre book: ";
		showListSearchBook();
	}
	else
	{
		cout << "The book in genre -" << genreId << "- not found!!!\n";
		delay();
	}
}

void searchRatingBook()
{
	int max = 0;
	bool isFound = false;

	searchResult = new RequestResult;

	unsigned buffer[1024];

	cout << endl << " --- The most popular book for genre --- " << endl << endl;
	showCatalog(genres, genresCount);

	int genrId = input(" Enter the genre of the film : ", 1, genresCount);

	for (int i = 0; i < booksCount; i++)
	{
		if (genrId == libBooks[i].genreId)
		{
			if (libBooks[i].rate > max)
			{
				isFound = true;
				buffer[searchResult->size] = i;
				searchResult->size++;
				max = libBooks[i].rate;
			}
		}
	}
	searchResult->result = new unsigned[searchResult->size];
	copyArray(buffer, searchResult->result, searchResult->size);

	if (isFound)
	{
		cout << "\n Search by Rating book : ";
		showListSearchBook();
		isFound = true;
	}
	else
	{
		cout << "The book in genre -" << genrId << "- not found!!!\n";
		delay();
	}
}


/* &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& SUB MENU BOOK &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
// *************** SORT Ad BOOK ********************
void sortBookAutor()
{
	doSortBook(&bookAutorCondition, sortCondition);
	showLibBooks();
}
void sortBookName()
{
	doSortBook(&bookNameCondition, sortCondition);
	showLibBooks();
}

void sortBookGenre()
{
	doSortBook(&bookGenreCondition, sortCondition);
	showLibBooks();
}

void sortRatingBook()
{
	doSortBook(&bookRatingCondition, sortCondition);
	showLibBooks();
}


/* &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&  Action by sub READER  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/


// ************************** Sub menu SEARCH READER **************************
void searchReaderSurNamePatr()
{
	char surname[25];
	char name[25];
	char patronic[25];

	searchResult = new RequestResult;

	unsigned buffer[1024];

	input(" Enter name reader : ", name, MAX_LEN_NAME);
	input(" Enter surname reader : ", surname, MAX_LEN_NAME);
	input(" Enter patronic reader : ", patronic, MAX_LEN_NAME);

	bool isFound = false;

	for (int i = 0; i < readsCount; i++)
	{
		if ((strcmp(libRead[i].surname, surname) == 0) && (strcmp(libRead[i].name, name) == 0) && (strcmp(libRead[i].patronic, patronic) == 0))
		{
			buffer[searchResult->size] = i;
			searchResult->size++;
			isFound = true;
		}
	}

	searchResult->result = new unsigned[searchResult->size];
	copyArray(buffer, searchResult->result, searchResult->size);

	if (isFound)
	{
		cout << " Search readers for surname, name, patronic : ";
		showListSearchRead();
	}
	else
	{
		cout << "The book -" << surname << "- not found!!!\n";
		delay();
	}
}

void searchNumRead()
{
	int numReadBook = input("Enter the number of books read : ");

	bool isFound = false;

	searchResult = new RequestResult;
	unsigned buffer[1024];

	for (int i = 0; i < readsCount; i++)
	{
		if (libRead[i].numReadBook == numReadBook)
		{

			buffer[searchResult->size] = i;
			searchResult->size++;
			isFound = true;
		}
	}
	searchResult->result = new unsigned[searchResult->size];
	copyArray(buffer, searchResult->result, searchResult->size);

	if (isFound)
	{
		cout << "\n Search by number of reads book : ";
		showListSearchRead();
	}
	else
	{
		cout << "The reader whith  -" << numReadBook << "- read books not found!!!\n";
		delay();
	}
}

void searchIdPasp()
{
	int IdPasp = input("Enter the ID pasport reader : ");

	bool isFound = false;

	searchResult = new RequestResult;

	unsigned buffer[1024];

	for (int i = 0; i < readsCount; i++)
	{
		if (libRead[i].idPasp == IdPasp)
		{

			buffer[searchResult->size] = i;
			searchResult->size++;
			isFound = true;
		}
	}

	searchResult->result = new unsigned[searchResult->size];
	copyArray(buffer, searchResult->result, searchResult->size);

	if (isFound)
	{
		cout << "\n Search by ID readers : ";
		showListSearchRead();
	}
	else
	{
		cout << "The reader whith  -" << IdPasp << "- ID pasport not found!!!\n";
		delay();
	}
}

// ******************** Search books on hand ***************************
void searchBooksOnHands(int readerId)
{
	bool isFound = false;

	searchResult = new RequestResult;

	unsigned buffer[1024];

	for (int i = 0; i < bookOnHandsCount; i++)
	{
		if (booksOnHands[i].idReader == readerId && booksOnHands[i].dataReturnBook.day == 0)
		{
			buffer[searchResult->size] = i;
			searchResult->size++;

			isFound = true;
		}
	}

	searchResult->result = new unsigned[searchResult->size];
	copyArray(buffer, searchResult->result, searchResult->size);

	if (isFound)
	{
		cout << "Found books: \n";
		showListBooksOnHand(readerId);
	}
	else
	{
		cout << "Books on hans not found!!!\n";
		delay();
	}
}

// ************************* SHOW **************************************

void showDateBookSearch(int i)
{
	cout << "\n============================" << endl;
	cout << " Edit date       : " << libBooks[i].dataEdit << endl;
	cout << " Name book       : " << libBooks[i].name << endl;
	cout << " Autor's name    : " << getName(libBooks[i].autorId, autors, autorsCount) << endl;
	cout << " Ganre of book   : " << getName(libBooks[i].genreId, genres, genresCount) << endl;
	cout << " Price           : " << libBooks[i].price << endl;
	cout << " Popular reting  : " << libBooks[i].rate << endl;
	cout << " Idnumber of book: " << libBooks[i].id << endl;
	cout << "\n============================" << endl << endl;
}

void showListSearchBook(int i)
{
	cout << "| " << libBooks[i].id << "\t";
	cout << "| " << libBooks[i].name << "\t\t";
	cout << "| " << getName(libBooks[i].autorId, autors, autorsCount) << "\t\t";
	cout << "| " << getName(libBooks[i].genreId, genres, genresCount) << "\t\t";
	cout << "| " << libBooks[i].dataEdit << "\t\t";
	cout << "| " << libBooks[i].rate << "\t";
	cout << "| " << libBooks[i].price << "\t\n";
}

void showDateBookSearch()
{
	for (unsigned j = 0; j < searchResult->size; j++)
	{
		unsigned i = searchResult->result[j];
		cout << "\n============================" << endl;
		cout << " Edit date       : " << libBooks[i].dataEdit << endl;
		cout << " Name book       : " << libBooks[i].name << endl;
		cout << " Autor's name    : " << getName(libBooks[i].autorId, autors, autorsCount) << endl;
		cout << " Ganre of book   : " << getName(libBooks[i].genreId, genres, genresCount) << endl;
		cout << " Price           : " << libBooks[i].price << endl;
		cout << " Popular reting  : " << libBooks[i].rate << endl;
		cout << " Idnumber of book: " << libBooks[i].id << endl;
		cout << "\n============================" << endl << endl;
	}

	delete[] searchResult->result;
	delete searchResult;

}

void showListSearchBook()
{

	cout << "\n =================================== LIST BOOK  =========================================" << endl;
	cout << "| #  | ID\t| Name \t\t| AutorName\t| Ganre \t| Date\t| Rate\t| Price\t|\n";

	cout << "\n ----------------------------------------------------------------------------------------|\n" << endl;

	for (unsigned j = 0; j < searchResult->size; j++)
	{
		unsigned i = searchResult->result[j];
		cout << "| " << j + 1 << "  | " << libBooks[i].id << " \t";
		cout << "| " << libBooks[i].name << "   \t";
		cout << "| " << getName(libBooks[i].autorId, autors, autorsCount) << "   \t";
		cout << "| " << getName(libBooks[i].genreId, genres, genresCount) << "   \t";
		cout << "| " << libBooks[i].dataEdit << " \t";
		cout << "| " << libBooks[i].rate << " \t";
		cout << "| " << libBooks[i].price << "\t|\n";
	}
}



void showListBooksOnHand(int readerId)
{
	cout << "\n ============== LIST BOOKS ON HAND FOR READER: " << getName(readerId, libRead, readsCount) << "==================" << endl;
	cout << "| #  | Book Name \t | Issue date \t | Overdued days \t| Penja ";
	cout << "\n|-----------------------------------------------------------------------------------\n" << endl;

	for (unsigned j = 0; j < searchResult->size; j++)
	{
		unsigned i = searchResult->result[j];
		cout << "| " << j + 1 << "  | " << getName(booksOnHands[i].idBook, libBooks, booksCount) << "   \t";
		cout << "| " << booksOnHands[i].dataIssueBook.day << "." << booksOnHands[i].dataIssueBook.month << "." << booksOnHands[i].dataIssueBook.year << "   \t";
		cout << "| " << 0 << " \t";
		cout << "| " << 0 << " \t\n";
	}
}
//*****************************************************************************

void showDateReaderSearch(int i)
{
	cout << "\n============================" << endl;
	cout << " ID reader                        : " << libRead[i].id << endl;
	cout << " Name reader                      : " << libRead[i].name << endl;
	cout << " Surname reader                   : " << libRead[i].surname << endl;
	cout << " Patronic reader                  : " << libRead[i].patronic << endl;
	cout << " Date birth reader                : " << libRead[i].dataBirth << endl;
	cout << " ID Pasport reader                : " << libRead[i].idPasp << endl;
	cout << " Num read books                   : " << libRead[i].numReadBook << endl;

	cout << "============================" << endl << endl;
}

void showListSearchRead(int i)
{
	cout << "| " << libRead[i].id << "\t";
	cout << "| " << libRead[i].name << "\t\t";
	cout << "| " << libRead[i].surname << "\t";
	cout << "| " << libRead[i].patronic << "\t";
	cout << "| " << libRead[i].dataBirth << "\t";
	cout << "| " << libRead[i].idPasp << "\t\t";
	cout << "| " << libRead[i].numReadBook << "\t\n";

}

void showDateReaderSearch()
{
	for (unsigned j = 0; j < searchResult->size; j++)
	{
		unsigned i = searchResult->result[j];
		cout << "\n============================" << endl;
		cout << " ID reader                        : " << libRead[i].id << endl;
		cout << " Name reader                      : " << libRead[i].name << endl;
		cout << " Surname reader                   : " << libRead[i].surname << endl;
		cout << " Patronic reader                  : " << libRead[i].patronic << endl;
		cout << " Date birth reader                : " << libRead[i].dataBirth << endl;
		cout << " ID Pasport reader                : " << libRead[i].idPasp << endl;
		cout << " Num read books                   : " << libRead[i].numReadBook << endl;

		cout << "============================" << endl << endl;
	}
}

void showListSearchRead()
{
	cout << "\n|=========================================== LIST Reader  ===============================\n";
	cout << "|-------------------------------------------------------------------------------------------------------|\n";
	cout << "| # | ID\t| Name\t\t| Surname\t| Patronic\t| Data Birth\t| Id pasport\t| Readed books\t|\n";

	cout << "|-------------------------------------------------------------------------------------------------------|\n";


	for (unsigned j = 0; j < searchResult->size; j++)
	{
		unsigned i = searchResult->result[j];
		cout << "| " << j + 1 << " | " << libRead[i].id << " \t";
		cout << "| " << libRead[i].name << "   \t";
		cout << "| " << libRead[i].surname << "   \t";
		cout << "| " << libRead[i].patronic << "   \t";
		cout << "| " << libRead[i].dataBirth << "   \t";
		cout << "| " << libRead[i].idPasp << " \t";
		cout << "| " << libRead[i].numReadBook << "   \t\t\n";


	}
	cout << endl;
}


// ************************** Sub menu SORT READER **************************

void sortReadSurNamePatr()
{
	doSortRead(&readSurNameCondition, sortCondition);
	showReaders();
}

void sortNumRead()
{
	doSortRead(&readNumCondition, sortCondition);
	showReaders();
}

void sortIdPasport()
{
	doSortRead(&readIdPaspCondition, sortCondition);
	showReaders();
}




// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

void delay()
{
	cout << "Press any key to continue...\n";
	_getch();
	currentMenu();
}

void exitFromMenu()
{
	prevMenu();
}

void doSortBook(CompareCondition(*conditionFunct)(int, int), CompareCondition condition)
{
	Book tmp;

	for (int i = 0; i < booksCount - 1; i++)
	{
		for (int j = i + 1; j < booksCount; j++)
		{
			if (conditionFunct(i, j) == condition)
			{
				tmp = libBooks[i];
				libBooks[i] = libBooks[j];
				libBooks[j] = tmp;
			}
		}
	}

	cout << endl << " Sorting finalized : " << endl;
}

void doSortRead(CompareCondition(*conditionFunct)(int, int), CompareCondition condition)
{
	Reader tmp;

	for (int i = 0; i < readsCount - 1; i++)
	{
		for (int j = i + 1; j < readsCount; j++)
		{
			if (conditionFunct(i, j) == condition)
			{
				tmp = libRead[i];
				libRead[i] = libRead[j];
				libRead[j] = tmp;
			}
		}
	}

	cout << endl << " Sorting finalized : " << endl;

}

// *******************************************  BOOK SORT  **********************************************

CompareCondition bookNameCondition(int i, int j)
{
	return compare(libBooks[j].name, libBooks[i].name);
}

CompareCondition bookAutorCondition(int i, int j)
{
	return compare(getName(libBooks[j].autorId, autors, autorsCount), getName(libBooks[i].autorId, autors, autorsCount));
}

CompareCondition bookGenreCondition(int i, int j)
{
	return compare(getName(libBooks[j].genreId, genres, genresCount), getName(libBooks[i].genreId, genres, genresCount));
}

CompareCondition bookRatingCondition(int i, int j)
{
	return compare(libBooks[j].rate, libBooks[i].rate);
}



// *******************************************  READER SORT  **********************************************

CompareCondition readSurNameCondition(int i, int j)
{
	unsigned str1Size = strlen(libRead[j].surname) + strlen(libRead[j].name) + strlen(libRead[j].patronic);
	unsigned str2Size = strlen(libRead[i].surname) + strlen(libRead[i].name) + strlen(libRead[i].patronic);
	char* str1 = new char[str1Size + 1];
	char* str2 = new char[str2Size + 1];

	strcat(str1, libRead[j].surname);
	strcat(str1, libRead[j].name);
	strcat(str1, libRead[j].patronic);

	strcat(str2, libRead[i].surname);
	strcat(str2, libRead[i].name);
	strcat(str2, libRead[i].patronic);

	CompareCondition result = compare(str1, str2);

	delete[] str1;
	delete[] str2;

	return result;
}

CompareCondition readNumCondition(int i, int j)
{
	return compare(libRead[j].numReadBook, libRead[i].numReadBook);
}

CompareCondition readIdPaspCondition(int i, int j)
{
	return compare(libRead[j].idPasp, libRead[i].idPasp);
}

// *******************************************   LOAD FILE   **************************************************

void loadData()
{
	loadAutors();
	loadGenres();
	loadBooks();
	loadReaders();

	loadBookOnHand();
}

void loadAutors()
{
	FILE* fileAutors = fopen("autors.txt", "r");

	if (fileAutors == nullptr)
	{
		cout << "Cannot open autors.txt!!! ";
		return;
	}

	char strBuff[256];
	Autor buffer[128];

	while (fgets(strBuff, 256, fileAutors))
	{
		if (strBuff[strlen(strBuff) - 1] == '\n')
		{
			strBuff[strlen(strBuff) - 1] = '\0';
		}

		parseIdName(buffer[autorsCount], strBuff);
		autorsCount++;
	}

	autors = new Autor[autorsCount];

	copyArray(buffer, autors, autorsCount);
	fclose(fileAutors);
}

void loadGenres()
{
	FILE* fileGenres = fopen("genres.txt", "r");

	char strBuff[256];
	Genre buffer[128];

	while (fgets(strBuff, 256, fileGenres))
	{
		if (strBuff[strlen(strBuff) - 1] == '\n')
		{
			strBuff[strlen(strBuff) - 1] = '\0';
		}

		parseIdName(buffer[genresCount], strBuff);
		genresCount++;
	}

	genres = new Genre[genresCount];

	copyArray(buffer, genres, genresCount);
	fclose(fileGenres);
}

void loadBooks()
{
	FILE* fileBooks = fopen("books.txt", "r");

	char strBuff[256];
	Book buffer[512];

	while (fgets(strBuff, 256, fileBooks))
	{
		if (strBuff[strlen(strBuff) - 1] == '\n')
		{
			strBuff[strlen(strBuff) - 1] = '\0';
		}

		parseIdName(buffer[booksCount], strBuff);
		char* strAutorId = strtok(nullptr, SEPARATOR);
		char* strGenreId = strtok(nullptr, SEPARATOR);
		char* strDataEdit = strtok(nullptr, SEPARATOR);
		char* strRate = strtok(nullptr, SEPARATOR);
		char* strPrice = strtok(nullptr, SEPARATOR);

		buffer[booksCount].autorId = atoi(strAutorId);
		buffer[booksCount].genreId = atoi(strGenreId);
		buffer[booksCount].dataEdit = atoi(strDataEdit);
		buffer[booksCount].rate = atoi(strRate);
		buffer[booksCount].price = atoi(strPrice);

		booksCount++;
	}

	libBooks = new Book[booksCount];

	copyArray(buffer, libBooks, booksCount);
	fclose(fileBooks);
}

void loadReaders()
{
	FILE* fileReaders = fopen("readers.txt", "r");

	char strBuff[256];
	Reader buffer[512];

	while (fgets(strBuff, 256, fileReaders))
	{
		if (strBuff[strlen(strBuff) - 1] == '\n')
		{
			strBuff[strlen(strBuff) - 1] = '\0';
		}

		parseIdName(buffer[readsCount], strBuff);

		char* strSurname = strtok(nullptr, SEPARATOR);
		char* strPatronic = strtok(nullptr, SEPARATOR);
		char* strDataBirth = strtok(nullptr, SEPARATOR);
		char* strIdPasport = strtok(nullptr, SEPARATOR);
		char* strNunReadBook = strtok(nullptr, SEPARATOR);

		buffer[readsCount].idPasp = atoi(strIdPasport);
		buffer[readsCount].numReadBook = atoi(strNunReadBook);

		strcpy(buffer[readsCount].surname, strSurname);
		strcpy(buffer[readsCount].patronic, strPatronic);
		strcpy(buffer[readsCount].dataBirth, strDataBirth);

		readsCount++;

	}

	libRead = new Reader[booksCount];
	copyArray(buffer, libRead, readsCount);
	fclose(fileReaders);
}

void loadBookOnHand()
{
	FILE* fileBookOnHeand = fopen("booksOnHands.txt", "r");
	char strBuff[255];

	BooksOnHands buffer[512];

	while (fgets(strBuff, 255, fileBookOnHeand))
	{
		if (strBuff[strlen(strBuff) - 1] == '\n')
		{
			strBuff[strlen(strBuff) - 1] = '\0';
		}

		char* strIdReader = strtok(strBuff, SEPARATOR);
		char* strIdBook = strtok(nullptr, SEPARATOR);
		char* strIssueBookDate = strtok(nullptr, SEPARATOR);
		char* strReturnBookDate = strtok(nullptr, SEPARATOR);

		buffer[bookOnHandsCount].idReader = atoi(strIdReader);
		buffer[bookOnHandsCount].idBook = atoi(strIdBook);

		//Parse dates
		parseDate(strIssueBookDate, buffer[bookOnHandsCount].dataIssueBook);
		parseDate(strReturnBookDate, buffer[bookOnHandsCount].dataReturnBook);

		bookOnHandsCount++;
	}

	booksOnHands = new BooksOnHands[bookOnHandsCount];
	copyArray(buffer, booksOnHands, bookOnHandsCount);
	fclose(fileBookOnHeand);
}

// *************************************** SAVE  **************************************

void saveData()
{
	saveAutors();
	saveGenres();
	saveBooks();
	saveReaders();
	saveBookOnHand();
}

void saveAutors()
{
	FILE* fileAutor = fopen("autors.txt", "w");

	if (fileAutor == nullptr)
	{
		cout << "Cannot open autors.txt!!! ";
		return;
	}


	for (int i = 0; i < autorsCount; i++)
	{
		char buffer[254] = { '\0' };

		_itoa((autors[i].id), buffer, 10);
		strcat(buffer, SEPARATOR);
		strcat(buffer, autors[i].name);

		fputs(buffer, fileAutor);
		putc('\n', fileAutor);
	}

	fclose(fileAutor);

}

void saveGenres()
{
	FILE* fileGanre = fopen("genres.txt", "w");

	if (fileGanre == nullptr)
	{
		cout << "Cannot open autors.txt!!! ";
		return;
	}


	for (int i = 0; i < genresCount; i++)
	{
		char buffer[254] = { '\0' };

		_itoa((genres[i].id), buffer, 10);
		strcat(buffer, SEPARATOR);
		strcat(buffer, genres[i].name);

		fputs(buffer, fileGanre);
		putc('\n', fileGanre);
	}

	fclose(fileGanre);
}

void saveBooks()
{
	FILE* fileBook = fopen("books.txt", "w");

	if (fileBook == nullptr)
	{
		cout << "Cannot open autors.txt!!! ";
		return;
	}


	for (int i = 0; i < booksCount; i++)
	{
		char buffer[254] = { '\0' };

		char bufItoa[25];
		_itoa((libBooks[i].id), bufItoa, 10);
		strcat(buffer, bufItoa);
		strcat(buffer, SEPARATOR);
		strcat(buffer, libBooks[i].name);
		strcat(buffer, SEPARATOR);
		_itoa((libBooks[i].autorId), bufItoa, 10);
		strcat(buffer, bufItoa);
		strcat(buffer, SEPARATOR);
		_itoa((libBooks[i].genreId), bufItoa, 10);
		strcat(buffer, bufItoa);
		strcat(buffer, SEPARATOR);
		_itoa((libBooks[i].dataEdit), bufItoa, 10);
		strcat(buffer, bufItoa);
		strcat(buffer, SEPARATOR);
		_itoa((libBooks[i].rate), bufItoa, 10);
		strcat(buffer, bufItoa);
		strcat(buffer, SEPARATOR);
		_itoa((libBooks[i].price), bufItoa, 10);
		strcat(buffer, bufItoa);

		fputs(buffer, fileBook);
		putc('\n', fileBook);
	}
	fclose(fileBook);
}

void saveReaders()
{
	FILE* fileReader = fopen("readers.txt", "w");

	if (fileReader == nullptr)
	{
		cout << "Cannot open autors.txt!!! ";
		return;
	}


	for (int i = 0; i < readsCount; i++)
	{
		char buffer[254] = { '\0' };

		char bufItoa[25];
		_itoa((libRead[i].id), bufItoa, 10);
		strcat(buffer, bufItoa);
		strcat(buffer, SEPARATOR);
		strcat(buffer, libRead[i].name);
		strcat(buffer, SEPARATOR);
		strcat(buffer, libRead[i].surname);
		strcat(buffer, SEPARATOR);
		strcat(buffer, libRead[i].patronic);
		strcat(buffer, SEPARATOR);
		strcat(buffer, libRead[i].dataBirth);
		strcat(buffer, SEPARATOR);
		_itoa((libRead[i].idPasp), bufItoa, 10);
		strcat(buffer, bufItoa);
		strcat(buffer, SEPARATOR);
		_itoa((libRead[i].numReadBook), bufItoa, 10);
		strcat(buffer, bufItoa);

		fputs(buffer, fileReader);
		putc('\n', fileReader);
	}
	fclose(fileReader);
}

void saveBookOnHand()
{
	FILE* fileBookOnHand = fopen("booksOnHands.txt", "w");

	if (fileBookOnHand == nullptr)
	{
		cout << "Cannot open autors.txt!!! ";
		return;
	}


	for (int i = 0; i < bookOnHandsCount; i++)
	{
		char buffer[254] = { '\0' };

		char bufItoa[25];
		_itoa((booksOnHands[i].idReader), bufItoa, 10);
		strcat(buffer, bufItoa);
		strcat(buffer, SEPARATOR);
		_itoa((booksOnHands[i].idBook), bufItoa, 10);
		strcat(buffer, bufItoa);
		strcat(buffer, SEPARATOR);
		_itoa((booksOnHands[i].dataIssueBook.day), bufItoa, 10);
		strcat(buffer, bufItoa);
		strcat(buffer, ".");
		_itoa((booksOnHands[i].dataIssueBook.month), bufItoa, 10);
		strcat(buffer, bufItoa);
		strcat(buffer, ".");
		_itoa((booksOnHands[i].dataIssueBook.year), bufItoa, 10);
		strcat(buffer, bufItoa);
		strcat(buffer, SEPARATOR);
		_itoa((booksOnHands[i].dataReturnBook.day), bufItoa, 10);
		strcat(buffer, bufItoa);
		strcat(buffer, ".");
		_itoa((booksOnHands[i].dataReturnBook.month), bufItoa, 10);
		strcat(buffer, bufItoa);
		strcat(buffer, ".");
		_itoa((booksOnHands[i].dataReturnBook.year), bufItoa, 10);
		strcat(buffer, bufItoa);

		fputs(buffer, fileBookOnHand);
		putc('\n', fileBookOnHand);
	}

	fclose(fileBookOnHand);
}

//*************************** TOOLS ************************************
template<typename T>
void copyArray(const T* src, T* dst, unsigned size)
{
	for (unsigned i = 0; i < size; i++)
	{
		dst[i] = src[i];
	}
}

template<typename T>
void parseIdName(T &dataStruct, char *str)
{
	char* strId = strtok(str, SEPARATOR);
	char* strName = strtok(nullptr, SEPARATOR);
	unsigned nameLen = strlen(strName);

	dataStruct.id = atoi(strId);

	strcpy(dataStruct.name, strName);
}

// *******************************  SHOW CATALOG - ID, NAME  ***********************
template<typename T>
void showCatalog(const T *catalog, int count)
{
	cout << "\n|========= TITLE ========|\n";
	cout << "| ID\t | Name\t\t |\n";
	cout << "|------------------------|\n";

	for (int i = 0; i < count; i++)
	{
		cout << "| " << catalog[i].id << "\t | " << catalog[i].name << "\t |\n";
	}
	cout << "|------------------------|\n";
}

CompareCondition compare(char const *str1, char const *str2)
{
	CompareCondition result = IS_LESS;
	int strcmpRes = strcmp(str1, str2);

	if (strcmpRes == 0)
	{
		result = IS_EQUAL;
	}
	else if (strcmpRes > 0)
	{
		result = IS_MORE;
	}
	return result;
}

CompareCondition compare(const int num1, const int num2)
{
	CompareCondition result = IS_LESS;

	if (num1 == num2)
	{
		result = IS_EQUAL;
	}
	else if (num1 > num2)
	{
		result = IS_MORE;
	}
	return result;
}

void parseDate(const char *str, Date& date)
{
	char* parseStr = new char[strlen(str) + 1];
	strcpy(parseStr, str);
	char* day = strtok(parseStr, ".");
	char* month = strtok(nullptr, ".");
	char* year = strtok(nullptr, ".");

	date.day = atoi(day);
	date.month = atoi(month);
	date.year = atoi(year);
}

int input(const char* title, int from, int to)
{
	int result = 0;
	char buffer[250];
	cout << title;
	if (from != 0 && from != to)
	{
		cout << "(" << from << " - " << to << "):";
	}

	//cin.get();

	while (true)
	{
		cin >> buffer;

		result = atoi(buffer);

		if (from != 0 && from != to && (result < from || result > to))
		{
			cout << "Incorect input! Please repeat...\n";
		}
		else
		{
			break;
		}
	}
	return result;
}

void input(const char* title, char* buffer, unsigned size)
{
	cout << title;
	cin.get();
	cin.getline(buffer, size);
}
