#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include <conio.h>
#include <fstream>
#include <vector>


class Tester
{
    int points;

    std::string askUsername()
    {
        std::string username;
        std::cout << "Podaj swoj nick\n";
        std::cin >> username;
        return username;
    }

    std::vector<std::string> split(const std::string &txt, char ch)
    {
        size_t pos = txt.find( ch );
        size_t initialPos = 0;
        std::vector<std::string> strs;

        // Decompose statement
        while( pos != std::string::npos )
        {
            strs.push_back( txt.substr( initialPos, pos - initialPos ) );
            initialPos = pos + 1;

            pos = txt.find( ch, initialPos );
        }

        // Add the last one
        strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );

        return strs;
    }
    //name score
    std::vector<std::string> sortNewUserScore(std::vector<std::string> lines, int currentScore, std::string name)
    {
        int i = 0;
        std::vector<std::string> allLines = lines;
        for(auto l: lines)
        {
            std::vector<std::string> splitted = split(l, ' ');
            // TODO
            if(i < 10 && std::stoi(splitted.at(1).c_str()) < currentScore)
            {
                allLines.insert(allLines.begin()+i, name + " " + std::to_string(currentScore) + "\n");
                if(allLines.size() > 10)
                    allLines.pop_back();
                break;
            }
            else if(allLines.size() < 10)
            {
                allLines.push_back(name + " " + std::to_string(currentScore) + "\n");
            }
            i++;
        }
        return allLines;
    }

    void saveUserScore(std::string username, int score)
    {
        std::vector<std::string> lines;
        std::ifstream f( "score.txt" );
        for( std::string line; getline( f, line ); )
        {
            lines.push_back(line);
        }
        lines = sortNewUserScore(lines, score, username);
        std::ofstream newFile("score.txt");
        if(newFile.is_open())
        {
            if(!lines.empty())
            {
                for(auto const& l: lines)
                {
                    newFile << l;
                }
            }
            else
            {
                newFile << username << " " << std::to_string(score) << "\n";
            }
        }
        newFile.close();
    }


public:
    Tester()
    {
        points = 0;
    }
    void test()
    {
        int valid = 0;
        for(int i = 0; i<10; i++)
        {
            int a = rand() % 10 + 1;
            int b = rand() % 10 + 1;
            int result;
            printf("%d * %d = ", a, b);
            std::cin >> result;
            if(result == a*b)
            {
                std::cout << "\nDobrze!\n";
                valid++;
            }
            else
            {
                std::cout << "\nZle!\n";
            }
        }
        std::cout << "Wynik: " << valid << "/10\n";
        std::string username = askUsername();
        saveUserScore(username, valid);
    }
};

void showTable()
{
    std::cout << "Tabliczka mnozenia:" << std::endl
              << "  1\t2\t3\t4\t5\t6\t7\t8\t9" << std::endl
              << "" << std::endl;
    for(int c = 1; c < 10; c++)
    {
        std::cout << c << "| ";
        for(int i = 1; i < 10; i++)
        {
            std::cout << i * c << '\t';
        }
        std::cout << std::endl;
    }
}

void multiplyByNumber()
{
    int n, range;

    std::cout << "Podaj liczbe: ";
    std::cin >> n;

    std::cout << "Podaj zakres: ";
    std::cin >> range;

    for (int i = 1; i <= range; ++i)
    {
        std::cout << n << " * " << i << " = " << n * i << std::endl;
    }
}
void showMenu()
{

    std::cout << "1. Sprawdzanie umiejetnosci mnozenia\n2. Wyswietlanie calej tabliczki\n3. Mnozenie przez dana liczbe\n4. Koniec\n";
}


int main()
{
    int choice = 0;
    Tester * t = new Tester();
    while(choice!=4)
    {
        showMenu();
        std::cin >> choice;
        switch(choice)
        {
        case 1:
            t->test();
            continue;
        case 2:
            showTable();
            continue;
        case 3:
            multiplyByNumber();
            continue;
        case 4:
            break;
        }
    }
    return 0;
}
