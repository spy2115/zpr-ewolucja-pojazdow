# ZPR_Ewolucja_pojazdow
Oprogramowanie przeprowadzające ewolucję sztucznych pojazdów w 2D.


## Wymagane pakiety:
### Dla Ubuntu 22.04 LTS:
<code>libsfml-dev, libboost-test-dev, libbox2d-dev rapidjson-dev</code>
### Instalacja:
```
sudo apt-get install libsfml-dev
sudo apt-get install libboost-test-dev
sudo apt-get install libbox2d-dev
sudo apt install rapidjson-dev
```

## Kompilowanie:
W katalogu <code>zpr_ewolucja_pojazdow</code>:
```
cmake .
make
```

## Uruchomienie:
### Aplikacja:
```
./bin/GeneticCars
```
### Testy:
```
./bin/tests -l all
```

