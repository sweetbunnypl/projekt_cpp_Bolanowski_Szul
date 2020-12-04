# projekt_cpp_Bolanowski_Szul
Projekt zaliczeniowy napisany w C++

--------

Gra typu "rougelike" w połączeniu z elementami strzelanki, oparta o grafikę dwuwymiarową z kamerą top-down. Gracz przechodząc kolejne poziomy planszy będzie miał możliwość rozwoju swojej postaci. Wraz z poziomami wzrastać będzie również poziom trudności. W grze będzie występował system zbierania punktów i wymieniania ich w sklepie. Gracz będzie także stawać przed różnymi wyzwaniami typu zagadki logiczne.
Naszymi inspiracjami są gry The Binding of Issac oraz Enter the Gungeon

Podział pracy:
Nasza praca oparta będzie o system "branchów" githuba dlatego elementy projektu typu szkielet gry oraz podstawowe mechaniki będziemy wykonywać razem, natomiast poszczególnie będziemy robić:
- Karol Bolanowski - główne menu gry, śledzenie kamery, grafika, ...
- Michał Szul - system tworzenia poziomów, AI przeciwników, grafika, ...

--------

Do zrobienia:
- mapa z losowo generowanymi poziomami
- system rozwoju postaci
- system zakupywania przedmiotów za zdobyte punkty
- przeciwnicy i ich zachowanie
- ...

Użyte technologie:
Naszym założeniem jest oparcie projektu w głównej mierze o bibliotekę SFML, lecz w trakcie tworzenia projektu możliwe, że użyjemy bibliotek opartych lub współpracujących z SFML'em w celu spójniejszego działania aplikacji oraz uproszczenia kodu.

--------

RAPORTY:


RAPORT I - 03.11.2020

branch Szul_movement:
- basic player movement
- tekstura postaci

branch Bolanowski:
- proste menu


RAPORT II - 17.11.2020

branch main:
- duże ulepszenia graficzne menu
- dodanie opcji w menu
- podstawowe mechaniki

RAPORT III - 01.12.2020

- scalenie menu z grą
- przycisk PLAY przenosi do rozgrywki
- BACKSPACE pauzuje grę ( Q - powrót do menu / R - wznowienie gry )
- poprawione poruszanie się (będzie zmienione w przyszłości)
- dalsze rozkminianie animacji (będzie poprawione w przyszłości)
- kolizje z obiektami na mapie ("ściana" wokół mapy)
- zrobienie i dodanie ostatecznych tekstur ścian i podłogi
- zalążek GUI

zdjęcia z obecnego stanu gry: https://imgur.com/a/uWUoXpO

(RAPORT IV - 15.12.2020) / do zrobienia

- przeciwnicy (loot z przeciwników)
- podstawowy system walki
- sklep (system wymiany przedmiotów i inne mechaniki)
- system levelovania postaci
- usprawnienie stanów gry
- usprawienie GUI

--------
- 12.01.2021 - prototyp
- 02.02.2021 - deadline
--------
