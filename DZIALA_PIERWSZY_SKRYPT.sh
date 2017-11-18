#!/bin/bash
grep "OK DOWNLOAD" cdlinux.ftp.log | cut -d '"' -f 2,4 | sed "s#\"# #">roboczy.txt

grep "200 " cdlinux.www.log | cut -d '"' -f 1,2 | cut -d ':' -f 2,5 |
cut -d " " -f 1,7>>roboczy.txt

sort -u roboczy.txt | sed "s#.*/##" | grep -e "\\.iso" -e "\\.tgz" | sort | uniq -c>liczba_sciagniec_linuxa.txt 

rm roboczy.txt
