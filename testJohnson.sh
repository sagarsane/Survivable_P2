#!/bin/bash

#N = 10 d = 0.10,0.15,0.20,0.25
echo "N = 10, d = 0.10" > outputs/testJohnson.txt
for (( j = 1 ; j <= 10 ; j++  ))
do
	./johnson extra/extraN10D010_$j.txt 1 10 >> outputs/testJohnson.txt
done

echo "N = 10, d = 0.15" >> outputs/testJohnson.txt
for (( j = 1 ; j <= 10 ; j++  ))
do
       ./johnson extra/extraN10D015_$j.txt 1 10 >> outputs/testJohnson.txt
done

echo "N = 10, d = 0.20" >> outputs/testJohnson.txt
for (( j = 1 ; j <= 10 ; j++  ))
do
       ./johnson extra/extraN10D020_$j.txt 1 10 >> outputs/testJohnson.txt
done

echo "N = 10, d = 0.25" >> outputs/testJohnson.txt
for (( j = 1 ; j <= 10 ; j++  ))
do
       ./johnson extra/extraN10D025_$j.txt 1 10 >> outputs/testJohnson.txt
done

#N = 15 d = 0.10,0.15,0.20,0.25
echo "N = 15, d = 0.10" >> outputs/testJohnson.txt
for (( j = 1 ; j <= 10 ; j++  ))
do
        ./johnson extra/extraN15D010_$j.txt 1 15 >> outputs/testJohnson.txt
done

echo "N = 15, d = 0.15" >> outputs/testJohnson.txt
for (( j = 1 ; j <= 10 ; j++  ))
do
       ./johnson extra/extraN15D015_$j.txt 1 15 >> outputs/testJohnson.txt
done

echo "N = 15, d = 0.20" >> outputs/testJohnson.txt
for (( j = 1 ; j <= 10 ; j++  ))
do
       ./johnson extra/extraN15D020_$j.txt 1 15 >> outputs/testJohnson.txt
done

echo "N = 15, d = 0.25" >> outputs/testJohnson.txt
for (( j = 1 ; j <= 10 ; j++  ))
do
       ./johnson extra/extraN15D025_$j.txt 1 15 >> outputs/testJohnson.txt
done

#N = 20 d = 0.10,0.15,0.20,0.25
echo "N = 20, d = 0.10" >> outputs/testJohnson.txt
for (( j = 1 ; j <= 10 ; j++  ))
do
        ./johnson extra/extraN20D010_$j.txt 1 20 >> outputs/testJohnson.txt
done

echo "N = 20, d = 0.15" >> outputs/testJohnson.txt
for (( j = 1 ; j <= 10 ; j++  ))
do
       ./johnson extra/extraN20D015_$j.txt 1 20 >> outputs/testJohnson.txt
done

echo "N = 20, d = 0.20" >> outputs/testJohnson.txt
for (( j = 1 ; j <= 10 ; j++  ))
do
       ./johnson extra/extraN20D020_$j.txt 1 20 >> outputs/testJohnson.txt
done

echo "N = 20, d = 0.25" >> outputs/testJohnson.txt
for (( j = 1 ; j <= 10 ; j++  ))
do
       ./johnson extra/extraN20D025_$j.txt 1 20 >> outputs/testJohnson.txt
done

#N = 25 d = 0.10,0.15,0.20,0.25
echo "N = 25, d = 0.10" >> outputs/testJohnson.txt
for (( j = 1 ; j <= 10 ; j++  ))
do
        ./johnson extra/extraN25D010_$j.txt 1 25 >> outputs/testJohnson.txt
done

echo "N = 25, d = 0.15" >> outputs/testJohnson.txt
for (( j = 1 ; j <= 10 ; j++  ))
do
       ./johnson extra/extraN25D015_$j.txt 1 25 >> outputs/testJohnson.txt
done

echo "N = 25, d = 0.20" >> outputs/testJohnson.txt
for (( j = 1 ; j <= 10 ; j++  ))
do
       ./johnson extra/extraN25D020_$j.txt 1 25 >> outputs/testJohnson.txt
done

echo "N = 25, d = 0.25" >> outputs/testJohnson.txt
for (( j = 1 ; j <= 10 ; j++  ))
do
       ./johnson extra/extraN25D025_$j.txt 1 25 >> outputs/testJohnson.txt
done

#N = 30 d = 0.10,0.15,0.20,0.25
echo "N = 30, d = 0.10" >> outputs/testJohnson.txt
for (( j = 1 ; j <= 10 ; j++  ))
do
        ./johnson extra/extraN30D010_$j.txt 1 30 >> outputs/testJohnson.txt
done

echo "N = 30, d = 0.15" >> outputs/testJohnson.txt
for (( j = 1 ; j <= 10 ; j++  ))
do
       ./johnson extra/extraN30D015_$j.txt 1 30 >> outputs/testJohnson.txt
done

echo "N = 30, d = 0.20" >> outputs/testJohnson.txt
for (( j = 1 ; j <= 10 ; j++  ))
do
       ./johnson extra/extraN30D020_$j.txt 1 30 >> outputs/testJohnson.txt
done

echo "N = 30, d = 0.25" >> outputs/testJohnson.txt
for (( j = 1 ; j <= 10 ; j++  ))
do
       ./johnson extra/extraN30D025_$j.txt 1 30 >> outputs/testJohnson.txt
done
