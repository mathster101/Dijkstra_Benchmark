#include "../includes/dijkstra.h"
#include<iostream>
#include<cstdlib>
#include<ctime>

void Clear()
{
    //'borrowed' from https://stackoverflow.com/a/52895729
#if defined _WIN32
    system("cls");
    //clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
    //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
#elif defined (__APPLE__)
    system("clear");
#endif
}


void dbg1()
{
    Clear();   
    int perfCountercopy = wrapper();
    Clear();
    cout<<"MULTICORE SCORE : "<<perfCountercopy;
    getchar();
}


int main(){
    srand(time(NULL));

    dbg1();
    return 0;
}