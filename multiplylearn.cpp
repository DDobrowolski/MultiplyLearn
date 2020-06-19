/*
 * =====================================================================================
 *
 *       Filename:  multiplylearn.cpp
 *
 *    Description:  App to learn multiplication table
 *
 *        Version:  1.9
 *        Created:  05-06.2020
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Michal Czarnecki, Damian Dobrowolski, Adam Balcerzak
 *   Organization:  AHE Lodz
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <fstream>
#include <vector>

class Tester
{
    // Pyta o nick usera
    std::string askUsername()
    {
        std::string username;
        std::cout << "Podaj swoj nick\n";
        std::cin >> username;
        return username;
    }
    /*  
        Parsuje tekst wejsciowy (&txt) do wektora
        dzielac po danym znaku (ch)
        janek 10
        ["janek", "10"]
    */
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
    /* 
        Przyjmuje linie z pliku (lines) oraz dopisuje do nich
        nowy wynik (currentScore) danego usera (name), jesli jest lepszy niz pierwsze
        10 pozycji i sortuje po wyniku.
    */
    std::vector<std::string> sortNewUserScore(std::vector<std::string> lines, int currentScore, std::string name)
    {
        int i = 0; // wyjsciowy indeks nowego wyniku
        std::vector<std::string> allLines = lines; // linie wyjsciowe
        for(auto l: lines)
        {
            // podzial linii na wektor [nazwa, punkty]
            std::vector<std::string> splitted = split(l, ' ');
            if(i < 10)
            {
                std::string newLine = name + " " + std::to_string(currentScore);
                if(std::stoi(splitted.at(1).c_str()) < currentScore)
                {
                    // dodaj nowy wynik na pozycje i
                    allLines.insert(allLines.begin()+i, newLine);
                    /* jesli po dodaniu ilosc linii wyjsciowych 
                        jest > 10 to usun ostatni element */
                    if(allLines.size() > 10)
                        allLines.pop_back();
                    break;
                }
                /* Edge case, jesli nie znajdzie gorszego wyniku 
                   to push na sam koniec 
                */
                else if(i+1 == allLines.size()){
                    allLines.push_back(newLine);
                    break;
                }
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
                    newFile << l << "\n";
                }
            }
            // Edge case, jesli linie sa puste to dodaj nowy (pierwszy) wynik
            else
            {
                newFile << username << " " << std::to_string(score) << "\n";
            }
        }
        newFile.close();
    }

/* 
    Tylko metoda test jest publiczna, reszta jest uzywana tylko
    przez klase Tester, przez co sa private.
*/
public:
    Tester(){}
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
            if(!std::cin.good())
            {
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
                std::cout <<"\nZle!\n";
                continue;
            }
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

    std::cout << "1. Sprawdzanie umiejetnosci mnozenia\n2. Wyswietlanie calej tabliczki\n3. Mnozenie przez dana liczbe\n4. Jak sie uczyc?\n5. Koniec\n";
}

void learn()
{

    std::cout << "Oto 6 przydatnych wskazowek dotyczacych nauki tabliczki mnozenia \n\n";

    std::cout << "1. Bardzo szybka technika nauki tabliczki mnozenia na palcach. \n";
    std::cout << "Kazda z dloni ma 5 palcow. Jesli chcemy pomnozyc np. 7 x 7, musimy zgiac po dwa palce u obu rak, \n";
    std::cout << "by odliczyc do 7. W ten sposob zgiete palce tworza dziesiatki - jest ich w sumie 4 \n";
    std::cout << "(4 zgiete palce, daje 40). Pozostale (3 u jednej i 3 u drugiej reki) mnozymy przez siebie. \n";
    std::cout << "To daje wynik rowny 9. 40 i 9 daje 49. To wynik tego rownania (7 x 7 = 49). \n\n";

    std::cout << "2. Kazda liczba mnozona przez 1 daje ta liczbe \n\n";

    std::cout << "3. Liczba mnozona przez 0 daje zawsze 0 \n";
    std::cout << "(Dla kazdego, jak marzenie jest przez zero liczb mnozenie! Zawsze wynik masz gotowy: zero - no i klopot z glowy!) \n\n";

    std::cout << "4. Sa iloczyny okragle nr 4x4, 5x5, 6x6 i te warto po prostu zapamietac \n\n";

    std::cout << "5. Latwa do zapamietania istnieje takze zasada przy mnozeniu przez 9, suma cyfr daje 9 np. 9*8=72; 7+2=9, 9*4=36; 3+6=9 \n\n";

    std::cout << "6. Aby pomnozyc przez 10, wystarczy do liczby dodac 0. \n\n";

    std::cout << "--------------------------- \n";

    std::cout << "Dodatkowe sposoby na nauke tabliczki mnozenia (metody mniej konwencjonalne): \n\n";

    std::cout << "1. Gry edukacyjne o tabliczce mnozenia \n";

    std::cout << "Razem z dzieckiem przygotujcie sobie kartoniki, na ktorych napisz z jednej strony dzialanie mnozenia, \n";
    std::cout << "a na drugiej stronie wynik. Zacznij od najprostszy dzialan mnozenia, aby dziecko zachecic do odkrywania swiata matematyki. \n";
    std::cout << "Stopniowo wprowadzaj trudniejsze przyklady. \n\n";

    std::cout << "2. Kolorowanki z tabliczka mnozenia \n";

    std::cout << "Dostepne sa matematyczne kolorowanki dla dzieci, ktore pobudza kreatywnosc \n";
    std::cout << "twojego dziecka i pozwola wzrokowo zapamietac dzialanie matematyczne. \n\n";

    std::cout << "3. Nauka tabliczki mnozenia - zabawa w pary \n";
    std::cout << "Ta metoda polega na przygotowaniu powiedzmy 20 kartonikow. Niech polowa z nich bedzie zapelniona dzialaniami, \n";
    std::cout << "zas pozostala czesc wynikami. Zabawa polega na rozlozeniu tych kartonikow zapisana strona do dolu: \n";
    std::cout << "oddzielnie wyniki i dzialania. Podczas zabawy z dzieckiem kazda osoba w swojej kolejce odslania \n";
    std::cout << "po jednej karcie z dzialaniem i wynikiem oraz odpowiada czy rezultat jest prawidlowy. \n";
    std::cout << "Jesli wynik i dzialanie pasuja ze soba to odkladacie je na bok. \n\n";

    std::cout << "4. Nauki tabliczki mnozenia - technika mnemoniczna \n";
    std::cout << "Ten rodzaj nauki tabliczki mnozenia polega na nadawaniu poszczegolnym cyfrom konkretnych ksztaltow, wygladu. \n";
    std::cout << "Na przyklad pies bedzie cyfra 4, a ptak cyfra 9. Dzieki temu dziecko bedzie latwiej bedzie moglo sobie pewne rzeczy wyobrazic. \n";
    std::cout << "Chodzi o to, aby dzialanie zaprezentowac w formie opowiadania. Tylko i wylacznie od was zalezy jaki charakter beda miec poszczegolne cyfry. \n";
    std::cout << "Na zasadzie tego typu skojarzen rowniez latwo mozna przyswoic tabliczke mnozenia. \n\n";

    std::cout << "5. Nauka tabliczki mnozenia za pomoca kostki do gry \n";
    std::cout << "W tej zabawie potrzebne beda co najmniej dwie osoby. Kazdy z uczestnikow na kartce od gory do dolu zapisuje 10 cyfr. \n";
    std::cout << "Nastepnie gracze rzucaja kostka. Wyniki rzutu kostka zapisywane sa w formie mnozenie przez te cyfre. \n";
    std::cout << "Jesli na samej gorze mamy zapisana cyfre 1 i wypadnie nam 6, to zapisujemy dzialanie 1 x 6 przy okazji rozwiazujac je. \n";
    std::cout << "Kolejek jest tyle, ile zapisanych cyfr. Wygrywa osoba, ktora zdobyla najwieksza sume wynikajaca z dzialan. \n";

}


int main()
{
    int choice = 0;
    Tester * t = new Tester();
    while(choice!=5)
    {
        showMenu();
        std::cin >> choice;
        if(!std::cin.good())
            {
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
                std::cout <<"\nProsze podac poprawna opcje!\n";
                continue;
            }
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
