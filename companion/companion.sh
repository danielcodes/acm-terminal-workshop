#####################
## 01 - navigation ##
#####################
pwd
ls
ls . # note: list current dir
ls ~ # note: list profile dir
ls .. # note: list parent dir
cd .. # note: change to parent dir
ls
cd / # note: change to root dir 
ls
cd

############################
## 02 - file manipulation ##
############################
cd ~/terminal_talk_f15/companion/section-02-manip
ls # note: already contains one file
mkdir aFolder
ls
cp aFile aFile1
ls
cp aFolder aFolder2 # note: this produces an error
ls
cp -r aFolder aFolder2
ls
mv aFile1 aFile99
ls
mv aFolder2 aFolder100 # note: no `-r` is needed
ls
rm aFile
ls
rm aFolder2 # note: this produces an error
rm -r aFolder2
ls

########################
## 03 - file matching ##
########################
cd ~/terminal_talk_f15/companion/section-03-file_match
ls
ls *.png
ls *.txt
rm pic-?.png # note: deletes pic 1-9 and a-z, but not >9 or aa
ls *.png
rm text-{16,19,20}.txt # deletes only text 16, 19, 20
rm text-{00..15}.txt # note: deletes text 1-15. leading zero is important!
ls *.txt

#######################
## 04 - text reading ##
#######################
cd ~/terminal_talk_f15/companion/section-04-read
ls
cat aShortFile
cat aLongFile # note: isn't helpful here
less aLongFile # note: less helpful because it allows paging
# note: press q to exit less

#####################
## 05 - timesavers ##
#####################
cat --h # note: explanation of command usage
cat ~/terminal_talk_f15/companion/section-04/aShortFile # note: use tab to complete path
fakeCommand -o with -j allKinds -k ofComplicated -f arguments # note: run command once, then arrow up
yes =] # note: press control-c to interrupt and close program
clear # note: cleans up command output

###########################
## 06 - pattern matching ##
###########################
cd ~/terminal_talk_f15/companion/section-06-pattern_match
ls # note: one file present
grep for aLongFile # note: find all for loops
grep int aLongFile # note: find all integer variables

#######################
## 07 - input/output ##
#######################
# no commands necessary

###############
## 08 - pipe ##
###############
cd ~/terminal_talk_f15/companion/section-08-pipe
cat --h | less
ls # note: one file present
cat aLongFile | grep -C3 void # note: too much output
cat aLongFile | grep -C3 void | less # note: paginated

######################
## 09 - redirection ##
######################
cd ~/terminal_talk_f15/companion/section-09-redirect
echo "Hello"
echo -e "hello\nhola" # note: `-e` evaluate special characters like new line
ls # note: should folder empty
echo -e "hello\nhola" > greetings # note: writes output as file
ls
cat greetings # note: contents came from echo
grep ol < greetings # note: reads file as input
echo "bonjour" > greetings
cat greetings # note: contents have overwritten
echo -e "hello\nhola" > greetings
cat greetings # note: back to original contents
echo "bonjour" >> greetings
cat greetings # note: new line has been appended to original contents
grep j < greetings > newFile # note: combo in/out
cat newFile # note: contains bonjour
