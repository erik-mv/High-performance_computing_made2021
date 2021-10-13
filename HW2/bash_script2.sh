my_array=( 1 3 2 4 10 3 54 43 234 12 -32 -1 0 2)

for i in `seq 0 $((${#my_array[@]}-1))`
    do
        echo ${my_array[i]}
done
