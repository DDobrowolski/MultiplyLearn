#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include <conio.h>

class Tester{
  int points;

public:
  Tester(){
    points = 0;
  }
 void test(){
   int valid = 0;
  for(int i = 0; i<10; i++){
    int a = rand() % 10 + 1;
    int b = rand() % 10 + 1;
    int result;
    printf("%d * %d = ", a, b);
    std::cin >> result;
    if(result == a*b)
    {
      std::cout << "\nDobrze!\n";
      valid++;
    }else{
      std::cout << "\nZle!\n";
    }
  }
  std::cout << "Wynik: " << valid << "/10\n";
}
};

int main(){
  Tester * t = new Tester();
  t->test();
  getch();
}