# projekt_cpp_Bolanowski_Szul
Projekt zaliczeniowy napisany w C++

--------

Gra typu "rougelike" w połączeniu z elementami RPG, oparta o grafikę dwuwymiarową z kamerą top-down. Gracz pokonując kolejne fale przeciwników będzie miał możliwość rozwoju swojej postaci oraz dokonywania wymian w sklepie. Wraz z kolejnymi falami przeciwników wzrastać będzie również poziom trudności.
Naszymi inspiracjami są gry The Binding of Issac oraz Enter the Gungeon

Podział pracy:

-Michał: tekstury i animacja / gracz / sklep /

-Karol: menu / przeciwnicy /

--------

Do zrobienia:
- mapa z losowo generowanymi poziomami
- system rozwoju postaci
- system zakupywania przedmiotów za zdobyte punkty
- przeciwnicy i ich zachowanie
- ...

Użyte technologie:
Naszym założeniem jest oparcie projektu w głównej mierze o bibliotekę SFML, lecz w trakcie tworzenia projektu możliwe, że użyjemy bibliotek opartych lub współpracujących z SFML'em w celu spójniejszego działania aplikacji oraz uproszczenia kodu.
2020/12/01 - rozszerzenie projektu o bibliotekę Thor, opartą o SFML i poszerzającą jego możliwości.

--------



RAPORT I - 2020/11/03

branch Szul_movement:
- basic player movement
- tekstura postaci

branch Bolanowski:
- proste menu



RAPORT II - 2020/11/17

branch main:
- duże ulepszenia graficzne menu
- dodanie opcji w menu
- podstawowe mechaniki



RAPORT III - 2020/12/01 (955 linijek kodu)

- scalenie menu z grą
- przycisk PLAY przenosi do rozgrywki
- BACKSPACE pauzuje grę ( Q - powrót do menu / R - wznowienie gry )
- poprawione poruszanie się (będzie zmienione w przyszłości)
- dalsze rozkminianie animacji (będzie poprawione w przyszłości)
- kolizje z obiektami na mapie ("ściana" wokół mapy)
- zrobienie i dodanie ostatecznych tekstur ścian i podłogi
- zalążek GUI

zdjęcia z obecnego stanu gry: https://imgur.com/a/uWUoXpO



RAPORT IV - 2020/12/15

- wprowadzenie planszy, będącej sklepem
- wprowadzenie prostych przeciwników, którzy podążają za graczem
- nowe tekstury
- usprawnienie kodu
- poprawa kilku drobnych błędów w gameplayu
- animacja postaci i obiektów
- robienie screenshotów



(PROTOTYP - 2021/01/12) / do zrobienia

- usprawnienie przeciwników (loot z przeciwników)
- podstawowy system walki
- sklep (system wymiany przedmiotów i inne mechaniki)
- system levelovania postaci
- usprawnienie stanów gry
- usprawienie GUI (X)
- usprawnienie menu (X)

--------
- 12.01.2021 - prototyp
- 02.02.2021 - deadline
--------
