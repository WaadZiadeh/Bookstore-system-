//

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

void displayMainMenu();
void addBook(int bins[], double prices[], int *size);
void removeBook(int bins[], double prices[], int *size);
void searchForBook(int bins[], double prices[], int size);
void uploadDataFile(int bins[], double prices[], int *size);
void updateDataFile(int bins[], double prices[], int size);
void printBooks(int bins[], double prices[], int size);

int main()
{
	printf("Welcome To My Book Store Management System: \n");
	int bins[MAXSIZE];
	double prices[MAXSIZE];
	int size = 0;
	uploadDataFile(bins, prices, &size);
	displayMainMenu();

	int ch;
	ch = 1;
	while (ch != 5)
	{
		scanf("%d", &ch);
		switch (ch)
		{
		case 1: addBook(bins, prices, &size); displayMainMenu();
			break;
		case 2: removeBook(bins, prices, &size); displayMainMenu();
			break;
		case 3: searchForBook(bins, prices, size); displayMainMenu();
			break;
		case 4: printBooks(bins, prices, size); displayMainMenu();
			break;
		case 5: updateDataFile(bins, prices, size); printf("\nThank you for using My Bookstore Managment System. GoodBye.\n");
			break;
		default:printf("No such operation! Please try again.\n"); displayMainMenu();
		}
	}

	return 0;
}

void displayMainMenu()
{
	printf("\nPlease Select an Operation <1-4>: \n1-Add a Book \n2-Remove a Book \n3-Search for a Book \n4-Print Book List \n5-Exit System\n\n");
}

void addBook(int bins[], double prices[], int *size)
{
	int size2 = *size;
	int book_bin = 0;
	double book_price = 0;

	printf("Enter bin number for book: \n");

	while (1)
	{
		if (scanf("%d", &book_bin) == 1) {
			break;
		}
	}

	printf("Enter price of book: \n");

	while (1) {
		if (scanf("%lf", &book_price) == 1) {
			break;
		}
	}

	int exist = 0;
	for (int i = 0; i < size2; i++) {
		if (bins[i] == book_bin) {
			exist = 1;
			break;
		}
	}

	if (exist == 1) {
		printf("\nBook with specified bin already exists, please try again\n");
	}
	else {
		if (size2 < MAXSIZE) {
			bins[size2] = book_bin;
			prices[size2] = book_price;
			size2++;
			*size = size2;
		}
		else {
			for (int i = size2 - 1; i > 0; i--) {
				bins[i] = bins[i - 1];
				prices[i] = prices[i - 1];
			}
			bins[0] = book_bin;
			prices[0] = book_price;
		}
		printf("\nBook with bin %d has beend added", book_bin);
	}
}

void removeBook(int bins[], double prices[], int *size)
{
	int size2 = *size;
	printf("Enter bin number for book: \n");
	int book_bin;
	scanf("%d", &book_bin);

	int exist = 0;
	if (size2 > 0) {
		for (int i = 0; i < size2; i++) {
			if (bins[i] == book_bin) {
				exist = 1;
				bins[i] = bins[i + 1];
				prices[i] = prices[i + 1];
				size2--;
				*size = size2;
				printf("\nBook with bin %d has beend removed", book_bin);
				break;
			}
		}
	}

	if (exist == 0) {
		printf("\nBook with specified bin does not exists, please try again\n");
	}
}

void searchForBook(int bins[], double prices[], int size)
{
	printf("Enter bin number for book to search for: \n");
	int book_bin;
	scanf("%d", &book_bin);

	int exist = 0;
	if (size > 0) {
		for (int i = 0; i < size; i++) {
			if (bins[i] == book_bin) {
				exist = 1;
				printf(" bin# = %d\tprice = %0.2f\n", bins[i], prices[i]);
				break;
			}
		}
	}

	if (exist == 0) {
		printf("\nBook with specified bin does not exists, please try again\n");
	}
}

void uploadDataFile(int bins[], double prices[], int *size)
{
	printf("\nUploading data file ...");
	FILE *books = fopen("books.txt", "r");
	if (books == NULL) {
		printf("\nError opening file\n");
	}
	else {
		int bin;
		double price;
		int c = 0;
		while (fscanf(books, "%d	%lf", &bin, &price) != EOF)
		{
			bins[c] = bin;
			prices[c] = price;
			c++;
		}
		*size = c;
		fclose(books);
		printf("\nData File uploaded\n");
	}
}

void updateDataFile(int bins[], double prices[], int size)
{
	printf("\nUpdating data file ...");
	FILE *books = fopen("books.txt", "w");
	if (books == NULL) {
		printf("\nError opening file\n");
	}
	else {
		for (int i = 0; i < size; i++) {
			fprintf(books, "%d\t%0.2f\n", bins[i], prices[i]);
		}
		fclose(books);
		printf("\nData File updated\n");
	}
}

void printBooks(int bins[], double prices[], int size)
{
	for (int i = 0; i < size; i++) {
		printf(" bin# = %d\tprice = %0.2f\n", bins[i], prices[i]);
	}
}


