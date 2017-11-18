#!/bin/bash
WYBOR="0"
NAZWA_KATALOGU="."
ARG_CZAS_MOD1=""
ARG_CZAS_MOD2=""
TECZA=0
while [[ WYBOR -ne 8 ]]; do

	echo "1. Nazwa pliku: $NAZWA_PLIKU"
	echo "2. Katalog: $NAZWA_KATALOGU"
	echo "3. Szukaj ostatnio modyfikowanych później $ARG_CZAS_MOD1 dni temu"
	echo "4. Szukaj ostatnio modyfikowanych wcześniej niz $ARG_CZAS_MOD2 dni temu"
	echo "5. Wyniki w tęczowych kolorach"
	echo "6. Zawartość plików"
	echo "7. Szukaj"
	echo "8. Koniec"
	read WYBOR
	case  "$WYBOR"  in
		"1")read NAZWA_PLIKU;;
		"2")read NAZWA_KATALOGU;;
		"3")echo "Podaj liczbę dni"
			read CZAS_MODYFIKACJI
			ARG_CZAS_MOD1="-mtime +$CZAS_MODYFIKACJI";;
		"4")echo "Podaj liczbę dni"
			read CZAS_MODYFIKACJI
			ARG_CZAS_MOD2="-mtime -$CZAS_MODYFIKACJI";;
		"5")if [ $TECZA -eq 0 ]; then
				TECZA=1
				echo "Aktywacja tęczy"
			else
				TECZA=0
				echo "Dezaktywacja teczy"
			fi;;
		"6")WYNIK=`find $NAZWA_KATALOGU -name "$NAZWA_PLIKU" $ARG_CZAS_MOD1 $ARG_CZAS_MOD2 -exec cat '{}' \;
		echo`
		if [ $TECZA -eq 1 ]; then
				echo "$WYNIK" | lolcat;
			else
				echo "$WYNIK"
		fi;;
		"7")WYNIK=`find $NAZWA_KATALOGU -name "$NAZWA_PLIKU" $ARG_CZAS_MOD1 $ARG_CZAS_MOD2`
			if [ $TECZA -eq 1 ]; then
				echo "$WYNIK" | lolcat;
			else
				echo "$WYNIK"
			fi
		;;
		"8");;
		*)echo "Nic nie wybrano"
	esac


done