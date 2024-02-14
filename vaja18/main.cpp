#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

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

class Person
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

void menu()
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
}

int main()
{
  std::vector<Book> books = createBookList(readLinesFromFile("books.txt"));
  menu();
}
