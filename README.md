# 🍻 Liar's Bar 🔫

Ești în vizită prin **Mama Rusia** și ți se face sete, așa că intri în primul bar pe care îl vezi, ca să tragi și tu la măsea ceva bun.
Te așezi frumos la masă și vezi cum vin trei rusnaci la tine. Ei te forțează să joci unul dintre jocurile lor, iar dacă refuzi să te joci, ești **cooked** 🔥.
Rușii par să fie drăguți cu tine, așa că te lasă să alegi jocul și cu câți dintre ei vrei să te joci. 😏


## ⚔️Instrucțiuni (**nimeni nu citește instrucțiuni, dar aici te joci cu viața ta...☠️**)
Alege unul din cele 2 jocuri, altfel nu te vad bine...⚰️:

1️⃣ **Liar's Deck** 🃏

În funcție de **masa aleasă random** de unul dintre ruși **la începutul fiecărei runde**, trebuie să minți cât de bine poți sau să încerci să ghicești dacă unul dintre ruși a mințit.


**Fiecare jucător are**:
- Cinci cărți din mulțimea **{Q, K, A, JOKER}**
- Un **revolver** cu un **glonț** din șase


2️⃣ **Liar's Dice** 🎲

Jocul se desfășoară în runde, în care jucătorii fac pariuri progresive despre câte zaruri de o anumită valoare cred că există în total pe masă.

**Fiecare jucător are**:
- Cinci zaruri acoperite de un paharar **[opac](#dicționar)** 🥤
- Două **shot-uri** de **Spirytus Rektyfikowany 🍷** o vodkă **[puternic dezvoltată](#dicționar)** 💪 care sperie chiar și rușii, având doar **96% ABV**



## 🎮 How to play:

### 🃏 Liar's deck 🃏
1️⃣ Jucătorii aleg 1-3 cărți din mână.

2️⃣ Dacă un jucător este prins mințind, el trebuie să-și tragă un glonț în cap folosind revolverul său (glonțul poate fi orb... sau adevărat).

3️⃣ Dacă jucătorul nu minte, adversarul, de dinainte, este obligat să tragă un glonț.

4️⃣ Dacă un jucător rămâne fără cărți, iar ultimele lui declarații au fost adevărate, adversarul precedent trebuie să se împuște.

### 🎲 Liar's dice 🎲
1️⃣ Primul jucător face o declarație.

2️⃣ Următorul jucător are trei opțiuni:
- creste pariul
- acuză jucător anterior: pe masă sunt mai puține zaruri de acea valoare
- anunță SPOT ON: declarația jucătorului anterior conține exact numărul de zaruri, de la masă, cu valoarea respectivă 

3️⃣ Dacă jucătorul anterior minte, el trebuie să bea un shot. În caz contrar, acuzatorul bea un shot 🥃

4️⃣ Dacă un jucător nimerește **SPOT ON-ul**, toată lumea de la masă bea un shot



**⚠️ Pe scurt: pierzi o rundă, ești cu un pas mai aproape de moarte! 💀**
🍀**Succes**!🍀


#### De implementat:
- ~~jocul continuă cand un player nu mai are cărți in mână~~
- ~~adăugare mod de joc~~
- rezolvare buguri

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



## Dicționar
- Opac = Prin care nu poate trece lumina, lipsit de transparență, nestrăveziu. ♦ Care nu permite trecerea unei radiații electromagnetice sau corpusculare. ♦ Lipsit de strălucire, întunecat.
- Puternic dezvoltat = Expresie folosită obsesiv de **Adelin Petrișor**, având sensul de șmecher. În acest context înseamnă letală 💀