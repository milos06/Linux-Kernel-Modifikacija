# Modifikacija i Rebuild Linux Kernela (Projekat 1 - 2025/26)
## 1. Uvod i Cilj Projekta
Cilj projekta je ---------------------------------.

## 2. Priprema Okruženja
1. uname -r 
2. sudo apt update 
3. sudo apt install build-essential
4. sudo apt install linux-headers-$(uname -r)
5. gcc --version

## 3. Priprema prvog modula
1. mkdir ~/kernel_proj
2. cd ~/kernel_proj
3. nano hello.c (pocetni)
4. nano Makefile
5. make
6. sudo insmod hello.ko
7. sudo dmesg | tail
   
  	![image alt](https://github.com/milos06/Linux-Kernel-Modifikacija/blob/b3e0b0c0b5d5edd6e084c574a1ac797594981773/Slike/Slika2.png)

