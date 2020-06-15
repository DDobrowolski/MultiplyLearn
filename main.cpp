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

        while( pos != std::string::npos )
        {
            strs.push_back( txt.substr( initialPos, pos - initialPos ) );
            initialPos = pos + 1;

            pos = txt.find( ch, initialPos );
        }

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

    std::cout << "1. Sprawdzanie umiejetnosci mnozenia\n2. Wyswietlanie calej tabliczki\n3. Mnozenie przez dana liczbe\n4. Nauka\n5. Koniec\n";
}

void learn(){

std::cout << "Oto 6 przydatnych wskazówek dotyczących nauki tabliczki mnożenia \n\n";

std::cout << "1. Bardzo szybka technika nauki tabliczki mnożenia na palcach. \n";
std::cout << "Każda z dłoni ma 5 palców. Jeśli chcemy pomnożyć np. 7 x 7, musimy zgiąć po dwa palce u obu rąk, \n";
std::cout << "by odliczyć do 7. W ten sposób zgięte palce tworzą dziesiątki – jest ich w sumie 4 \n";
std::cout << "(4 zgięte palce, daje 40). Pozostałe (3 u jednej i 3 u drugiej ręki) mnożymy przez siebie. \n";
std::cout << "To daje wynik równy 9. 40 i 9 daje 49. To wynik tego równania (7 x 7 = 49). \n\n";

std::cout << "2. Każda liczba mnożona przez 1 daję tą liczbę \n\n";

std::cout << "3. Liczba mnożona przez 0 daje zawsze 0 \n";
std::cout << "(Dla każdego, jak marzenie jest przez zero liczb mnożenie! Zawsze wynik masz gotowy: zero – no i kłopot z głowy!) \n\n";

std::cout << "4. Są iloczyny okrągłe nr 4x4, 5x5, 6x6 i te warto po prostu zapamiętać \n\n";

std::cout << "5. Łatwa do zapamiętania istnieje także zasada przy mnożeniu przez 9, suma cyfr daje 9 np. 9*8=72; 7+2=9, 9*4=36; 3+6=9 \n\n";

std::cout << "6. Aby pomnożyć przez 10, wystarczy do liczby dodać 0. \n\n";

std::cout << "--------------------------- \n";

std::cout << "Dodatkowe sposoby na naukę tabliczki mnożenia (metody mniej konwencjonalne): \n\n";

std::cout << "1. Gry edukacyjne o tabliczce mnożenia \n";

std::cout << "Razem z dzieckiem przygotujcie sobie kartoniki, na których napisz z jednej strony działanie mnożenia, \n";
std::cout << "a na drugiej stronie wynik. Zacznij od najprostszy działań mnożenia, aby dziecko zachęcić do odkrywania świata matematyki. \n";
std::cout << "Stopniowo wprowadzaj trudniejsze przykłady. \n\n";

std::cout << "2. Kolorowanki z tabliczką mnożenia \n";

std::cout << "Dostępne są matematyczne kolorowanki dla dzieci, które pobudzą kreatywność \n";
std::cout << "twojego dziecka i pozwolą wzrokowo zapamiętać działanie matematyczne. \n\n";

std::cout << "3. Nauka tabliczki mnożenia - zabawa w pary \n";
std::cout << "Ta metoda polega na przygotowaniu powiedzmy 20 kartoników. Niech połowa z nich będzie zapełniona działaniami, \n";
std::cout << "zaś pozostała część wynikami. Zabawa polega na rozłożeniu tych kartoników zapisaną stroną do dołu: \n";
std::cout << "oddzielnie wyniki i działania. Podczas zabawy z dzieckiem każda osoba w swojej kolejce odsłania \n";
std::cout << "po jednej karcie z działaniem i wynikiem oraz odpowiada czy rezultat jest prawidłowy. \n";
std::cout << "Jeśli wynik i działanie pasują ze sobą to odkładacie je na bok. \n\n";

std::cout << "4. Nauki tabliczki mnożenia - technika mnemoniczna \n";
std::cout << "Ten rodzaj nauki tabliczki mnożenia polega na nadawaniu poszczególnym cyfrom konkretnych kształtów, wyglądu. \n";
std::cout << "Na przykład pies będzie cyfrą 4, a ptak cyfrą 9. Dzięki temu dziecko będzie łatwiej będzie mogło sobie pewne rzeczy wyobrazić. \n";
std::cout << "Chodzi o to, aby działanie zaprezentować w formie opowiadania. Tylko i wyłącznie od was zależy jaki charakter będą mieć poszczególne cyfry. \n";
std::cout << "Na zasadzie tego typu skojarzeń również łatwo można przyswoić tabliczkę mnożenia. \n\n";

std::cout << "5. Nauka tabliczki mnożenia za pomocą kostki do gry \n";
std::cout << "W tej zabawie potrzebne będą co najmniej dwie osoby. Każdy z uczestników na kartce od góry do dołu zapisuje 10 cyfr. \n";
std::cout << "Następnie gracze rzucają kostką. Wyniki rzutu kostką zapisywane są w formie mnożenie przez tę cyfrę. \n";
std::cout << "Jeśli na samej górze mamy zapisaną cyfrę 1 i wypadnie nam 6, to zapisujemy działanie 1 x 6 przy okazji rozwiązując je. \n";
std::cout << "Kolejek jest tyle, ile zapisanych cyfr. Wygrywa osoba, która zdobyła największą sumę wynikającą z działań. \n";

}


int main()
{
    int choice = 0;
    Tester * t = new Tester();
    while(choice!=5)
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
            learn();
            continue;
        case 5:
            break;
        }
    }
    return 0;
}
