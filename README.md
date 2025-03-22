# 🍻 Liar's Bar 🔫

Ești în vizită prin Mama Rusia și ți se face sete, așa că intri în primul bar pe care îl vezi, ca să tragi și tu la măsea ceva bun.
Te așezi frumos la masă și vezi cum vin trei rusnaci la tine. Ei te forțează să joci jocul lor, care este o combinație dintre Trombon și Ruleta rusească, iar dacă refuzi să te joci ești **cooked** 🔥.
Rușii par să fie drăguți cu tine, așa că te lasă să alegi cu câți dintre ei vrei să te joci. 😏


## ⚔️ Instrucțiuni (**nimeni nu citește instrucțiuni, dar aici te joci cu viața ta... ☠️**)
În funcție de **masa aleasă random** 🎲 de unul dintre ruși la începutul fiecărei runde, trebuie să minți cât de bine poți sau să încerci să ghicești dacă unul dintre ruși a mințit.
**Fiecare jucător are**:
- Cinci cărți din mulțimea {Q, K, A, JOKER}
- Un **revolver** cu un **glonț** din șase:



## 🎮 How to play:
1️⃣ Jucătorii aleg 1-3 cărți din mână.

2️⃣ Dacă un jucător este prins mințind, el trebuie să-și tragă un glonț în cap folosind revolverul său (glonțul poate fi orb... sau adevărat).

3️⃣ Dacă jucătorul nu minte, adversarul, de dinainte, este obligat să tragă un glonț.

4️⃣ Dacă un jucător rămâne fără cărți, iar ultimele lui declarații au fost adevărate, adversarul precedent trebuie să se împuște.

**⚠️ Pe scurt: pierzi o rundă, ești cu un pas mai aproape de moarte! 💀**
🍀**Succes**!🍀




## Instrucțiuni de compilare

Proiectul este configurat cu CMake.

Instrucțiuni pentru terminal:

0. Biblioteci necesare pe Linux (presupunem sistem de operare bazat pe Debian)
```sh
sudo apt-get update && \
  sudo apt-get install libxrandr-dev \
    libxcursor-dev \
    libudev-dev \
    libopenal-dev \
    libflac-dev \
    libvorbis-dev \
    libgl1-mesa-dev \
    libegl1-mesa-dev \
    libdrm-dev \
    libgbm-dev \
    libfreetype6-dev
```

Dacă lipsesc și alte biblioteci, ștergeți folder-ul de build de la pasul 1 și reconfigurați proiectul după ce ați instalat ce lipsea.

1. Pasul de configurare
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
# sau ./scripts/cmake.sh configure
```

Sau pe Windows cu GCC:
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -G Ninja
# sau ./scripts/cmake.sh configure -g Ninja
```

La acest pas putem cere să generăm fișiere de proiect pentru diverse medii de lucru.


2. Pasul de compilare
```sh
cmake --build build --config Debug --parallel 6
# sau ./scripts/cmake.sh build
```

Cu opțiunea `parallel` specificăm numărul de fișiere compilate în paralel.


3. Pasul de instalare (opțional)
```sh
cmake --install build --config Debug --prefix install_dir
# sau ./scripts/cmake.sh install
```

Vezi și [`scripts/cmake.sh`](scripts/cmake.sh).

Observație: folderele `build/` și `install_dir/` sunt adăugate în fișierul `.gitignore` deoarece
conțin fișiere generate și nu ne ajută să le versionăm.


## Resurse

- [SFML](https://github.com/SFML/SFML/tree/2.6.1) (Zlib)
  - [OpenAL](https://openal-soft.org/) (LGPL): din cauza licenței, trebuie distribuită ca shared library
- adăugați trimiteri către resursele externe care v-au ajutat sau pe care le-ați folosit
