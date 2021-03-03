# 42_philosophers
Who wants to live forever?

## Description
These are my solutions to the Dijkstra's famous dining philosophers problem ([Wiki](https://en.wikipedia.org/wiki/Dining_philosophers_problem)).

<img src="diner.jpg" width="400"/>

Common requirements:
- Some number of philosophers are sitting at the round table, doing three things - eating, sleeping, or thinking, one at a time.  
- There are some forks and spaghetti on the table, philosophers should use two forks to eat.  
- Philosophers do not talk to each other and do not know, what others are doing.  
- If a philosopher does not eat within specified time, he dies and the simulation stops.

The goal is to make philosophers live eternally, if the simulation parameters were correct of course. This could be achieved if no deadlocks occur.

The problem comes in three flavors:
1. Forks lie between philosophers (one to the left and one to the right). Philosophers should be represented by **threads** and forks by **mutexes**;
2. Forks lie in the center of the table. Philosophers should be represented by **threads** and forks by a **semaphore**;
3. Forks lie in the center of the table. Philosophers should be represented by **processes** and forks by a **semaphore**.

The solutions are implemented in three C programs - philo_one, philo_two and philo_three.

## Usage

### To install
```
git clone <repo> <dir>
cd <dir>/<program_name>
make
```

### To run simulation
```
./<program_name> <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [<number_of_times_each_philosopher_should_eat>]
```
For example:
```
./philo_one 4 410 200 200
```
The last parameter is optional. If it is set, then the simulation will stop when all philosophers eat the specified number of times (or if one of them dies).
