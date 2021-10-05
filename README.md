# philosophers
In computer science, the dining philosophers problem is an example problem often used in concurrent algorithm design to illustrate synchronization issues and techniques for resolving them.

It was originally formulated in 1965 by <a href='https://en.wikipedia.org/wiki/Edsger_W._Dijkstra'>Edsger Dijkstra</a> as a student exam exercise, presented in terms of computers competing for access to tape drive peripherals. Soon after, <a href='https://en.wikipedia.org/wiki/Tony_Hoare'>Tony Hoare</a> gave the problem its present formulation:

Five silent philosophers sit at a round table with bowls of spaghetti. Forks are placed between each pair of adjacent philosophers.

Each philosopher must alternately think and eat. However, a philosopher can only eat spaghetti when they have both left and right forks. Each fork can be held by only one philosopher at a time and so a philosopher can use the fork only if it is not being used by another philosopher. After an individual philosopher finishes eating, they need to put down both forks so that the forks become available to others. A philosopher can only take the fork on their right or the one on their left as they become available and they cannot start eating before getting both forks.

Eating is not limited by the remaining amounts of spaghetti or stomach space; an infinite supply and an infinite demand are assumed.

The problem is how to design a discipline of behavior (a concurrent algorithm) such that no philosopher will starve; i.e., each can forever continue to alternate between eating and thinking, assuming that no philosopher can know when others may want to eat or think.

This exercise is part of the basic curriculum at <a href='https://www.42sp.org.br/'>42 São Paulo</a>.

## work_history

<details>
  <summary>Click to expand </summary>


  **September 11th 2021** - I set up the project structure and Makefile, as well as some standard input error handling. I still have to figure out exactly how I'm going to approach this.

  **September 22th 2021** - Still structuring the project and started playing with threads. Don't really know how I'm gonna do this yet.

  **September 22th 2021** - Philosophers are now threads and they "take turns" thinking. Tomorrow I will try to implement their actual eating/sleeping/thinking routine. Maybe organize my files a little bit.

  **September 27th 2021** - Now the philosophers eat/think/sleep, but the files are still a mess. I'm gonna fix it later. Gotta figure out mutexes now.

  **September 29th 2021** - Mutexes/forks implemented, and we're starting to count time. REALLY need to refactor to clean up. Having occasional deadlocks that need to be addressed.

  **October 54th 2021** - Philosophers now starve to death as they should. Code still looks like a messy heap of garbage. Allocated everything on the stack because I don't wanna deal with mallocs.

  </details>
