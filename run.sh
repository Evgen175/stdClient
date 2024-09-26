for i in $(seq 1 5000); do
echo "i : $(( $i / 10 ))"
./stdClient $i 3030 $(( $RANDOM % 31 )) &
done
