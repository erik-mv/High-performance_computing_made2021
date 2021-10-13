X=100
Y=.5

Z=$(bc<<<"scale=1;$X+$Y")
echo "100 + 0.5 = " $Z
