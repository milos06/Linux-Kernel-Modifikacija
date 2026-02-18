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

## 4. Pravimo modul koji prima putanju fajla i ispisuje koji procesi koriste taj fajl
1. nano hello.c (menjamo kod)
2. make clean
3. make
4. touch /tmp/testfile.txt
5. sudo insmod hello.ko filepath=/tmp/testfile.txt
6. sudo dmesg | tail

	![image alt](https://github.com/milos06/Linux-Kernel-Modifikacija/blob/9f902b81f4e4212702953d85e0ee1adfc28ae57e/Slike/Slika3.png)

## 5. Inode
1. nano hello.c (izmene)
2. make clean
3. make
4. touch /tmp/testfile.txt
5. sudo insmod hello.ko filepath=/tmp/testfile.txt
6. sudo dmesg | tail

	![image alt](https://github.com/milos06/Linux-Kernel-Modifikacija/blob/46bd78a9af8621912f432f8dc289fc30914296ef/Slike/slika4.png)

## 6. Pronalazak inode i prolaz kroz sve procese
1. nano helo.c (izmena)
2. make clean
3. make
4. echo "test" > /tmp/testfile.txt
5. nano /tmp/testfile.txt (otvaramo fajl)
6. sudo insmod hello.ko filepath=/tmp/testfile.txt
7. sudo dmesg | tail -n 30

   ![image alt](https://github.com/milos06/Linux-Kernel-Modifikacija/blob/5e3a08192e5e36b39d22c72073bfda880ec5b7ea/Slike/Slika5.png)

## 7. Konacno resenje
1. nano hello.c (izmena koda)
2. make clean
3. make
4. sudo rmmod hello
5. sudo insmod hello.ko filepath=/tmp/testfile.txt
6. sudo dmesg | tail -n 40

 ![image alt](https://github.com/milos06/Linux-Kernel-Modifikacija/blob/3fa6d6579195bb3e41cbab1a01e53d20627ba6c4/Slike/slika6.png)

