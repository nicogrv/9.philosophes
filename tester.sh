make re 

# DEATH

./philo 1 200 100 100 3 
echo "\nIF DIE = OK\n"

sleep 1
./philo 2 200 100 100 3 
echo "\nIF DIE = OK\n"


sleep 1
./philo 5 200 100 100 3 
echo "\nIF DIE = OK\n"

sleep 1
./philo 10 200 100 100 3 
echo "\nIF DIE = OK\n"

sleep 1
./philo 199 200 100 100 3 
echo "\nIF DIE = OK\n"

sleep 1
./philo 200 200 100 100 3 
echo "\nIF DIE = OK\n"

# OK

echo "\nCHECK OK\n"


sleep 3
./philo 1 200 50 50 10
echo "\nIF DIE = KO\n"

sleep 1
./philo 2 200 50 50 10 
echo "\nIF DIE = KO\n"

sleep 1
./philo 5 200 50 50 10 
echo "\nIF DIE = KO\n"

sleep 1
./philo 10 200 50 50 10 
echo "\nIF DIE = KO\n"

sleep 1
./philo 199 200 50 50 10 
echo "\nIF DIE = KO\n"

sleep 1
./philo 200 200 50 50 10 
echo "\nIF DIE = KO\n"

sleep 2

# Valgrind

valgrind ./philo 1 200 50 50 10
echo "\n\n\n\n\n"

sleep 1
valgrind ./philo 2 200 50 50 10 
echo "\n\n\n\n\n"

sleep 1
valgrind ./philo 5 200 50 50 10 
echo "\n\n\n\n\n"

sleep 1
valgrind ./philo 10 200 50 50 10 
echo "\n\n\n\n\n"

sleep 1
valgrind ./philo 199 200 50 50 10 
echo "\n\n\n\n\n"

sleep 1
valgrind ./philo 200 200 50 50 10 
echo "\n\n\n\n\n"

# HELGRIND


echo "\n\nHELGRIND\n\n\n"
sleep 3
valgrind --tool=helgrind ./philo 1 200 50 50 10
echo "\n\n\n\n\n"

sleep 1
valgrind --tool=helgrind ./philo 2 200 50 50 10 
echo "\n\n\n\n\n"

sleep 1
valgrind --tool=helgrind ./philo 5 200 50 50 10 
echo "\n\n\n\n\n"

sleep 1
valgrind --tool=helgrind ./philo 10 200 50 50 10 
echo "\n\n\n\n\n"

sleep 1
valgrind --tool=helgrind ./philo 199 200 50 50 10 
echo "\n\n\n\n\n"

sleep 1
valgrind --tool=helgrind ./philo 200 200 50 50 10 
echo "\n\n\n\n\n"

# Valgrind

echo "\n\n\nDOIT MOURIR AVANT 210\n\n"
sleep 3

./philo 1 200 800 100 10 

sleep 1
./philo 2 200 800 100 10 

sleep 1
./philo 5 200 800 100 10 

sleep 1
./philo 10 200 800 100 10 

sleep 1
./philo 199 200 800 100 10 

sleep 1
./philo 200 200 800 100 10 

echo "\n\n\ntricky test\n\n"

echo "X 20 9 9 10\n"

./philo 2 20 9 9 10
sleep 1

./philo 10 20 9 9 10
sleep 1

./philo 100 20 9 9 10
sleep 1

./philo 200 20 9 9 10
echo "\n\nX 410 200 200\n"

sleep 3

./philo 2 410 200 200 10
sleep 1

./philo 10 410 200 200 10
sleep 1

./philo 100 410 200 200 10
sleep 1

./philo 200 410 200 200 10
sleep 1

