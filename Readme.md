# Triangles visible area calculator

## Introduction

🇬🇧 This projects aim is to calculate visible area of triangles being given the triangle verticies stored in a text file, observation point and looking directory in an infinite 3d space.

🇵🇱 Celem tego projektu jest obliczanie widocznej powierzchni trójkątów mając podaną listę trójkątów w pliku tekstowym, punkt obserwacyjny oraz kierunek patrzenia w nieskończonej trójwymiarowej przestrzeni.

## Technologies

- C++
- Visual Studio Code

## Launch

### Mac and Linux

🇬🇧 Simply double click "main" file.

🇵🇱 Po prostu kliknij dwa razy na plik "main"

### Windows

🇬🇧 You will need to install MinGW compilator to compile the source code to .exe file. Once installed, you should run this command in your terminal opened in the projects directory:

🇵🇱 Będziesz musiał zainstalować kompilator MinGW aby skompilować kod źródłowy do pliku .exe. Kiedy zainstalujesz kompilator, uruchom tę komendę w terminalu otwartym w katalogu z projektem:

```
g++ -std=c++14 *.cpp -o main
```

## Project structure

### main.cpp

🇬🇧 This file contains main algorithm of the program. It is also responsible for reading triangles from file.

🇵🇱 Ten plik zawiera główny algorytm programu. Jest również odpowiedzialny za wczytywanie trójkątów z pliku.

### triangle.h/cpp

🇬🇧 These files contain Triangle class made for storing data about tiangles read from the file. They also contain enum that deifnes possible looking directions.

🇵🇱 Te pliki zawierają klasę Triangle stworzoną do przechowywania danych o trójkątach wczytanych z pliku. Zawierają też typ enumeryczny definiujący możliwe kierunki patrzenia.

### point.h/cpp

🇬🇧 These files contain Point structure made for storing information about a particular point. It can hold triangles verticies but also observation point and 3d coordinates in general.

🇵🇱 Te pliki zawierają strukturę Point stworzoną do przechowywania informacji o konkretnym punkcie. Może ona przechowywać wierzchołki trójkąta, ale również punkt obserwacyjny jak i ogólne współrzędne 3d czegokolwiek.

### myExtentions.h

🇬🇧 This file contains my custom defined exceptions.

🇵🇱 Ten plik zawiera moje własne rodzaje wyjątków.

### Other files

🇬🇧 Other files are neccesary for Visual Studio Code to run this project correctly.

🇵🇱 Inne pliki są używane przez Visual Studio Code do poprawnego uruchamiania tego projektu.
