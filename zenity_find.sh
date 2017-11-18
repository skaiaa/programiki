#!/bin/bash
NAZWA="Find_it"
WYBOR="0"
ARGUMENT="0"
NAZWA_KATALOGU="."
ARG_CZAS_MOD1=""
ARG_CZAS_MOD2=""
TECZA=0

pokaz_wynik()
{
			if [ $TECZA -eq 1 ]; then
				echo "$1" | lolcat --force | ./ansi2html.sh --bg=dark> roboczy.html
				zenity --text-info --title "Zawartość" --height 300 --width 800 --filename="roboczy.html" --html
				rm roboczy.html
			else
				zenity --info --title "Zawartość" --text "$1"
			fi
}
while [[ ARGUMENT -ne 8 ]]; do
#zenity --info --title $NAZWA --text "Witam gorąco, oto mój skrypt wyszukujący"
MENU=("1. Nazwa pliku:"
	  "2. Katalog"
	  "3. Szukaj ostatnio modyfikowanych później x dni temu"
	  "4. Szukaj ostatnio modyfikowanych wcześniej niz x dni temu"
	  "5. Wyniki w tęczowych kolorach"
	  "6. Zawartość plików"
	  "7. Szukaj"
	  "8. Koniec")
WYBOR=`zenity --list --column=MENU "${MENU[@]}" --height 300 --width 400`
	case  "$WYBOR"  in
		"1. Nazwa pliku:")
			NAZWA_PLIKU=`zenity --entry --title "Nazwa pliku" --text "Podaj nazwę pliku"`;;

		"2. Katalog")
		NAZWA_KATALOGU=`zenity --entry --title "Nazwa katalogu" --text "Podaj nazwę katalogu"`;;

		"3. Szukaj ostatnio modyfikowanych później x dni temu")
			CZAS_MODYFIKACJI=`zenity --entry --title "Liczba dni" --text "Podaj liczbę dni"`
			ARG_CZAS_MOD1="-mtime +$CZAS_MODYFIKACJI";;

		"4. Szukaj ostatnio modyfikowanych wcześniej niz x dni temu")
			CZAS_MODYFIKACJI=`zenity --entry --title "Liczba dni" --text "Podaj liczbę dni"`
			ARG_CZAS_MOD2="-mtime -$CZAS_MODYFIKACJI";;

		"5. Wyniki w tęczowych kolorach")
			if [ $TECZA -eq 0 ]; then
				TECZA=1
				zenity --info --title "Tęcza" --text "AKTYWACJA TĘCZY"
			else
				TECZA=0
				zenity --info --title "Tęcza" --text "DEZAKTYWACJA TĘCZY"
			fi;;

		"6. Zawartość plików")
			WYNIK=`find $NAZWA_KATALOGU -name "$NAZWA_PLIKU" $ARG_CZAS_MOD1 $ARG_CZAS_MOD2 -exec cat '{}' \;`
			pokaz_wynik "$WYNIK";;

		"7. Szukaj")
			WYNIK=`find $NAZWA_KATALOGU -name "$NAZWA_PLIKU" $ARG_CZAS_MOD1 $ARG_CZAS_MOD2`
			pokaz_wynik "$WYNIK";;

		"8. Koniec")ARGUMENT=8;;

		*)echo "Nic nie wybrano"
	esac

done