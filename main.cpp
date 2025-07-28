#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Book
{
public:
    int id;
    string title, author;
    bool isIssued;

public:
    Book()
    {
    }

    Book(int id, string title, string author)
    {
        this->id = id;
        this->title = title;
        this->author = author;
        this->isIssued = false;
    }

    void display() const
    {
        cout << "Id : " << id << " | Title : " << title << " | Author : " << author;
        cout << " | Isissue : " << (isIssued ? "Yes" : "No") << endl;
    }

    string tofileformat() const
    {
        return to_string(id) + "|" + title + "|" + author + "|" + (isIssued ? "1" : "0") + "\n";
    }

    static Book fromfileformat(const string &line)
    {
        Book b;
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        size_t pos3 = line.find('|', pos2 + 1);

        b.id = stoi(line.substr(0, pos1));
        b.title = line.substr(pos1 + 1, pos2 - pos1 - 1);
        b.author = line.substr(pos2 + 1, pos3 - pos2 - 1);
        b.isIssued = line[pos3 + 1] == '1';

        return b;
    }
};

class library
{
    vector<Book> books;
    static int totalbook;

    void loadfile()
    {
        ifstream out("Book_Records.txt");
        string line;
        while (getline(out, line))
        {
            Book b = Book::fromfileformat(line);
            books.push_back(b);
            totalbook++;
        }

        out.close();
    }

    void tosavefile()
    {

        ofstream out("Book_Records.txt");
        for (auto const &b : books)
        {
            out << b.tofileformat();
        }

        out.close();
    }

public:
    library()
    {
        loadfile();
    }
    ~library()
    {
        tosavefile();
    }

    void Addbook()
    {
        int id;
        string title, author;
        cout << "Enter the id of the book : ";
        cin >> id;
        cin.ignore();
        cout << "Enter the Title of the book : ";
        getline(cin, title);
        cout << "Enter the Author of the book : ";
        getline(cin, author);
        books.push_back(Book(id, title, author));
        totalbook++;
        tosavefile();
        cout << "Book Added Successfully !\n" << endl;
    }

    void ShowAllbooks() const
    {

        if (books.empty())
        {
            cout << "No books Avilable !" << endl;
            return;
        }

        for (const auto &b : books)
        {
            b.display();
        }
    }

    void SearchBook()
    {
        int id;
        cout << "Enter your book id to search : ";
        cin >> id;
        cin.ignore();

        bool found;
        for (const auto &b : books)
        {
            if (b.id == id)
            {
                b.display();
                found = true;
                break;
            }

            if (!found)
            {
                cout << "Not found!" << endl;
            }
        }
    }

    static void totalbookshow()
    {
        cout << "Total books is " << totalbook << endl;
    }

    void DeleteBook()
    {
        int id;
        cout << "Enter your book id to delete : ";
        cin >> id;
        cin.ignore();
        bool found;
        for (auto it = books.begin(); it != books.end();)
        {
            if (it->id == id)
            {
                books.erase(it);
                totalbook--;
                cout << "Book deleted Successful !" << endl;
                found = true;
                return;
            }
            if (!found)
            {
                cout << "Id is no match !" << endl;
            }
        }
    }

    void UpdateBook()
    {
        int getid;
        string gettitle,getauthor;
        cout << "Enter your id to update : ";
        cin >> getid;
        cin.ignore();
        bool found;
        for(auto it = books.begin(); it !=books.end(); )
        {
            if(it->id == getid)
            {
                cout << "Enter your new book id : ";
                cin >>getid;
                cin.ignore();
                cout << "Enter your new book title : ";
                getline(cin,gettitle);
                cout << "Enter your new book Author : ";
                getline(cin,getauthor);

                it->id= getid;
                it->title = gettitle;
                it->author = getauthor;
                found = true;
                cout << "Book details updated successfl !" <<endl;
                return;
            }

            if(!found)
            {
                cout << "Id is not matched !" <<endl;
            }
        }
    }
};

int library::totalbook = 0;

int main()
{
    library lib;
    int choice;
    do
    {
        cout << "----------------------------" << endl;
        cout << "Library Managment System" << endl;
        cout << "----------------------------" << endl;
        cout << endl;
        cout << "----Menu----" << endl;
        cout << "1.Add Book" << endl;
        cout << "2.Show All Books" << endl;
        cout << "3.Search Books" << endl;
        cout << "4.Total Books" << endl;
        cout << "5.Delete Book" << endl;
        cout << "6.Update Book" << endl;
        cout << "7.Exit\n"
             << endl;

        cout << "Enter your choice : ";
        cin >> choice;
        cin.ignore();
        cout << endl;
        switch (choice)
        {
        case 1:
            lib.Addbook();
            break;
        case 2:
            lib.ShowAllbooks();
            break;
        case 3:
            lib.SearchBook();
            break;
        case 4:
            library::totalbookshow();
            break;

        case 5:
            lib.DeleteBook();
            break;
        case 6:
            lib.UpdateBook();
            break;
        case 7:
            cout << "Exiting... Saving data.\n";
            break;
        default:
            cout << "Enter the correct choice !" << endl;
            break;
        }

    } while (choice != 7);

    return 0;
}