-Program:a5

-Programmer(s): Calvin Hoy -(No partner :( )
-Student #: 100954276
-Due Date: Dec 4, 2015, NOON
-Instructor: Christine Laurendeau

-Purpose: 
• implement programs with inter-process communications, work with signals and sockets

-List of files:
	-a5main.c
	-a5main.o
	-Makefile	
	-README.txt
	-a5 'executable file'

-To compile on BASH:
	1) >cd home/CalvinHoy_COMP2401A5

	2) >make


-To run on BASH:
	1) Open up a BASH terminal

	2)>cd home/CalvinHoy_COMP2401A5

	3)>./a5

	4) Open up a new and separate BASH terminal
		-NOTE: DO NOT CLOSE THE LAST ONE

	5) On the new one, run    >cd home/CalvinHoy_COMP2401A5

	6) then on the new one, run    >./a5 10.0.2.15

	-NOTE: IT IS IMPORTANT THAT THESE RUN IN THE RIGHT ORDER. IF NOT THEY WILL NOT CONNECT PROPERLY	
	-NOTE: IF YOU FAIL TO RERUN A SERVER, WAIT 1 MINUTE, THEN TRY RUNNING ">./a5" AGAIN.
		-ALSO NOTE: 


-Operation: Running the Game
1) First off, you need 2 command line windows to run the game.

2) Within the first, input >./a5 . This will act as the server.

3) Then in the second, input >./a5 10.0.2.15 . This will act as the client.

4) The client gets to choose a word first. Then he must wait for the server.

5) The server will now choose a word.

6) After they both have selected their words, the words will now be converted and shown
   to each other, ready to be thrown guesses at.

anddd.......sadly, that's about as far as i got. No guessing, no letter checking (It still compiles though, just doesnt do what i want it to). 
Although the code for everything else is still there for everything else, they kind of won't work without the letter guessing/checking.
