make re 

# DEATH

./philo 1 200 100 100 3 

sleep 1
./philo 2 200 100 100 3 

sleep 1
./philo 5 200 100 100 3 

sleep 1
./philo 10 200 100 100 3 

sleep 1
./philo 199 200 100 100 3 

sleep 1
./philo 200 200 100 100 3 

# OK

sleep 1
./philo 1 200 50 50 3

sleep 1
./philo 2 200 50 50 3 

sleep 1
./philo 5 200 50 50 3 

sleep 1
./philo 10 200 50 50 3 

sleep 1
./philo 199 200 50 50 3 

sleep 1
./philo 200 200 50 50 3 

sleep 1

# Valgrind

valgrind ./philo 1 200 50 50 3
echo "\n\n\n\n\n"

sleep 1
valgrind ./philo 2 200 50 50 3 
echo "\n\n\n\n\n"

sleep 1
valgrind ./philo 5 200 50 50 3 
echo "\n\n\n\n\n"

sleep 1
valgrind ./philo 10 200 50 50 3 
echo "\n\n\n\n\n"

sleep 1
valgrind ./philo 199 200 50 50 3 
echo "\n\n\n\n\n"

sleep 1
valgrind ./philo 200 200 50 50 3 
echo "\n\n\n\n\n"

# HELGRIND


# echo "\n\nHELGRIND\n\n\n"
# sleep 3
# valgrind --tool=helgrind ./philo 1 200 50 50 3
# echo "\n\n\n\n\n"

# sleep 1
# valgrind --tool=helgrind ./philo 2 200 50 50 3 
# echo "\n\n\n\n\n"

# sleep 1
# valgrind --tool=helgrind ./philo 5 200 50 50 3 
# echo "\n\n\n\n\n"

# sleep 1
# valgrind --tool=helgrind ./philo 10 200 50 50 3 
# echo "\n\n\n\n\n"

# sleep 1
# valgrind --tool=helgrind ./philo 199 200 50 50 3 
# echo "\n\n\n\n\n"

# sleep 1
# valgrind --tool=helgrind ./philo 200 200 50 50 3 
# echo "\n\n\n\n\n"


./philo 1 200 800 100 3 

sleep 1
./philo 2 200 800 100 3 

sleep 1
./philo 5 200 800 100 3 

sleep 1
./philo 10 200 800 100 3 

sleep 1
./philo 199 200 800 100 3 

sleep 1
./philo 200 200 800 100 3 