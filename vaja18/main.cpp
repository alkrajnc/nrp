#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <bits/stdc++.h>

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

struct Book
{
  std::string title;
  std::string author;
  std::string ISBN;
  bool isAvailable;
};

struct PersonT
{
  std::string name;
  int ID;
  std::vector<std::string> borrowedBooks;
};

std::vector<std::string> split(const std::string &str, char delimiter)
{
  std::vector<std::string> parts;
  for (int i = 0; i < int(str.size()); i++)
  {
    std::string part;
    while (str[i] != delimiter && i < int(str.size()))
    {
      part += str[i];
      i++;
    }
    parts.push_back(part);
  }
  return parts;
}

std::vector<std::string> readLinesFromFile(std::string filename)
{
  std::ifstream file(filename);
  std::vector<std::string> lines;
  if (file.is_open())
  {
    while (!file.eof())
    {
      std::string line;
      std::getline(file, line);
      lines.push_back(line);
    }
  }
  return lines;
}

std::vector<Book> createBookList(std::vector<std::string> lines)
{
  std::vector<Book> books;
  std::vector<std::string> bookData;

  for (const auto &line : lines)
  {
    Book book;
    std::vector<std::string> data = split(line, ',');
    book.ISBN = data[0];
    book.title = data[1];
    book.author = data[2];
    book.isAvailable = data[3] == "1" ? true : false;
    books.push_back(book);
  }
  return books;
}

void saveBookToFile(Book book, std::string filename)
{
  std::ofstream file(filename, std::ios::app);
  file << book.ISBN << "," << book.title << "," << book.author << "," << book.isAvailable;
}

void saveUserToFile(PersonT person, std::string filename)
{
  std::ofstream file(filename, std::ios::app);
  std::string borrowedBooks;
  for (const auto &book : person.borrowedBooks)
  {
    borrowedBooks += book + "|";
  }
  file << person.name << "," << person.ID << "," << borrowedBooks;
}

void createNewUser()
{
  PersonT person;
  std::cout << "Enter your name: ";
  std::cin >> person.name;
  std::cout << "Enter your ID: ";
  std::cin >> person.ID;
  // totdo auto increment id
  saveUserToFile(person, "users.txt");
}

void addNewBook()
{
  Book book;
  std::cout << "Enter book title: ";
  std::cin >> book.title;
  std::cout << "Enter book author: ";
  std::cin >> book.author;
  std::cout << "Enter book ISBN: ";
  std::cin >> book.ISBN;
  book.isAvailable = true;
  saveBookToFile(book, "books.txt");
}

void sortBooks(std::vector<Book> &books)
{
  int i, j, min_idx;
  for (i = 0; i < books.size(); i++)
  {
    min_idx = i;
    for (j = i + 1; j < books.size(); j++)
    {
      if (books[j].title < books[min_idx].title)
        min_idx = j;
    }
    if (min_idx != i)
      std::swap(books[min_idx], books[i]);
  }
}

void printBooks(std::vector<Book> &books)
{
  sortBooks(books);
  for (const auto &book : books)
  {
    std::cout << book.title << " by " << book.author << " ISBN: " << book.ISBN << " " << (book.isAvailable ? "Available" : "Not available") << std::endl;
  }
}

std::vector<PersonT> getSavedUsers()
{
  std::vector<std::string> lines = readLinesFromFile("users.txt");
  // printf("lines: %d\n", lines.size());
  std::vector<PersonT> users;
  for (const auto &line : lines)
  {
    PersonT person;
    std::vector<std::string> data = split(line, ',');
    // std::cout << "\n\nName: " << data[0] << " ID: " << data[1] << " Borrowed books: " << data[2] << std::endl;
    person.name = data[0];
    person.ID = std::stoi(data[1]);
    person.borrowedBooks = split(data[2], '|');
    users.push_back(person);
  }
  return users;
}

class Person
{
  std::string name;
  int ID;
  std::vector<std::string> borrowedBooks;

public:
  Person(std::string name, int ID, std ::vector<std::string> borrowBook)
  {
    this->name = name;
    this->ID = ID;
    this->borrowedBooks = borrowBook;
  }

  std ::
      string
      getName()
  {
    return this->name;
  }

  void borrowBook(std::vector<Book> &books)
  {
    std::string ISBN;
    std::cout << "Enter book ISBN: ";
    std::cin >> ISBN;
    for (auto &book : books)
    {
      if (book.ISBN == ISBN)
      {
        if (book.isAvailable)
        {
          book.isAvailable = false;
          saveBookToFile(book, "books.txt");
          std::cout << "Book borrowed" << std::endl;
          borrowedBooks.push_back(book.ISBN);
        }
        else
        {
          std::cout << "Book not available" << std::endl;
        }
      }
    }
  }

  void returnBook(std::vector<Book> &books)
  {
    std::string ISBN;
    std::cout << "Enter book ISBN: ";
    std::cin >> ISBN;
    for (auto &book : books)
    {
      if (book.ISBN == ISBN)
      {
        if (!book.isAvailable)
        {
          book.isAvailable = true;
          saveBookToFile(book, "books.txt");
          std::cout << "Book returned" << std::endl;
          borrowedBooks.erase(std::remove(borrowedBooks.begin(), borrowedBooks.end(), book.ISBN), borrowedBooks.end());
        }
        else
        {
          std::cout << "Error: nekaj" << std::endl;
        }
      }
    }
  }
};

void menu(std::string currentUser)
{

  system(CLEAR);
  printf("Library\n\n");
  printf("1. Add book\n");
  printf("2. Borrow book\n");
  printf("3. Return book\n");
  printf("4. List books\n");
  printf("5. Search books\n");
  printf("6. New user\n");
  printf("7. Exit\n");
  printf("\nSelect an option: ");
  printf("Signed in as %s\n", currentUser);
}

int main()
{
  int userID;
  std::cout << "Login (enter user ID): ";
  std::vector<PersonT> users = getSavedUsers();
  std::cin >> userID;

  printf("users: %d\n", users.size());

  if (userID >= 0 && userID < users.size())
  {

    // Rest of the code
  }
  else
  {
    std::cout << "Invalid user ID" << std::endl;
  }
  Person currentUser(users[userID].name, users[userID].ID, users[userID].borrowedBooks);

  int selection;
  std::vector<Book> books = createBookList(readLinesFromFile("books.txt"));
  menu(currentUser.getName());

  std::cin >> selection;

  switch (selection)
  {
  case 1:
    addNewBook();
    break;
  case 2:
    currentUser.borrowBook(books);
    break;
  case 3:
    currentUser.returnBook(books);
    break;
  case 4:
    printBooks(books);
    break;
  case 5:
    break;
  case 6:
    createNewUser();
    break;
  case 7:
    exit(0);
    break;
  default:
    break;
  }
}
