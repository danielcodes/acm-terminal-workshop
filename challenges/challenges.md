# Terminal Talk - Challenges

### ACM Club - Oct 22, 2015

### Instructions
When attempting these challenges, it's assumed that you've cloned this repo and pointed your terminal to the challenges directory. Each challenge section has a subdirectory for itself, and in those subdirectories is where you should do your work.

## Section-1 - Coding workflow - Part 1
1. **Navigate to aLongfile.cpp file**
1. **Print contents of aLongFile.cpp file to terminal**

    *Hint:* `cat` and `less` are helpful here, but which one should you use? Both do text reading. Try to think about how they get the job done differently.
1. **View paginated contents of aLongFile.cpp**

    *Hint:* See above hint
1. **Open aLongFile.cpp file in GUI editor**
1. **Compile and execute a helloWorld.cpp program**

    *Hint-1:* The syntax for executing an executable, is ` ./<nameOfExecutable> `

    *Hint-2:* If you’re on Git Bash for Windows, you probably don’t have g++ available. In that case, then use your usual C++ IDE to compile the cpp file. Afterwards, go back to your terminal, `cd` to the executable that your IDE produced, and then execute it.
1. **Use terminal history to execute the program from the previous challenge a second time**
1. **Clean up the output from the previous two challenges**

## Section-2 - File copying and renaming
1. **Create a copy of folder-a called folder-b**

    *Hint:* Remember how we said that ` -r ` is sometimes necessary.
1. **Within folder-b, renames files M, N, O to X, Y, Z**

    *Hint:* Remember that renaming is lumped into the move command
1. **Copy files X, Y, Z to folder A with only one use of the cp command**

    *Hint:* `cp` is a smart little command. You’ve already seen it handle two arguments, but watch what it can do with more than two arguments. Oh boy.

## Section-3 - Coding workflow - Part 2
1. **Identify the included library or header files within simulationWidget.cpp file**

    *Hint:* Try to remember how the presenters were able to track down all those for loops in a given cpp file
1. **Count total lines in simulationWidget.cpp**

    *Hint:* The `wc` command is pretty nifty. It short for word count but it also spits out other stats like line count and byte count, but who wants that stuff? If only we knew a way to find out what types of arguments `wc` accepts so that we could skip out on those ugly other stats. Oh right, there’s documentation built into the command.
1. **Identify all included library or header files for the whole project**

    *Hint:* You’ve already seen that `grep` can handle one filename as an argument, but why stop there. Give it more filenames. Or better yet, how did the presenters reference all filenames of a particular extension?
1. **Count total number of included library or header files for the whole project**

    *Hint-1:* Something seems fishy...this challenge sounds awfully similar to the previous two challenges. `wc` count lines, right? But do those lines have to be from a file? Hmm.

    *Hint-2:* `grep` and `wc` are great, but if only there was a way to get them to work together as team. It’s like we need some kind of connector between the two of them. Something like how indoor plumbing gets water from the water company to come out of our kitchen sink faucet. Brilliant! Indoor plumbing for Unix terminal programs!
1. **Count total lines across all cpp files in whole project**

    *Hint:* Remember how `cp` and `grep` could take multiple arguments? Well, so can `wc`.
1. **Within simulationWidget.cpp, rename the cpp variable `opacity` to `transparency` and update all occurrences that variable**

    *Hint:* Meet the `sed` command. She’s kind of a multitalented gal, but her most famous ability is string substitution. Give her an input file, a pattern, and a replacement string, and lickity split, she’ll give you an output file with all the substitutions you could have ever hoped for.

    Here’s an example of her in action: `sed ‘s/aPattern/yourReplacementString/g’ anInputfile > yourOutputFile`

## Section-4 - File cleanup
1. **Delete all files with a java extension**

    *Hint:* Give your cheatsheet a quick glance. You might find the syntax you in need in the “File Matching” section.
1. **Delete the ciao cpp files numbered 1 through 15**

    *Hint:* See above hint
1. **Delete the ciao cpp files numbered 17, 19, and 25**

    *Hint:* See above hint
1. **Delete all files in a directory**

    *Hint:* We’ve seen wildcard work its magic with file extensions, but what happens when we let wildcard run carefree and, well, wild. No burdensome file extensions for this here wildcard.
1. **Delete a whole directory**

    *Hint:* Remember how we said that ` -r ` is sometimes necessary.

## Section-5 - Recreate cleaned up files
1. **Create one empty file named bonjour-00.java**

    *Hint:* `touch` has a way with a little things, like making empty files. No can compare to him. He just makes it look so easy. See for you yourself: run `touch myNewFile`, and ta-da! you’ve got a new file. He’s just that good!
1. **Create 4 more numbered bonjour java files and 15 ciao cpp files that are numbered in order**

    *Hint-1:* `touch` can handle multiple arguments just like the rest of those high class commands you’ve already met. I’m talking about `cp`, `grep`, `wc`, you name it. Well, `touch` is right up there with those greats!

    *Hint-2:* Give your cheatsheet a quick glance. You might find the syntax you in need in the “File Matching” section.
1. **Create 26 hola js files that are labeled a through z**

    *Hint:* see hints from the previous two challenges
1. **Delete the new files from the previous three challenges, and try to recreate them with only one use of the touch command**

    *Hint:* This isn’t a trick question. Given his multi-argument abilities, `touch` can do it!

## Section-6 - Misc
1. **Count number of files/directories within this section's directory**

    *Hint:* Remember `wc` counts lines, but no one said that they have to be lines of a file.
1. **Store “Hello world” in a new file**

    *Hint:* `echo` might be pretty unoriginal, but she’s pretty true to her purpose, which is just repeating what others tell her to say. Yes, she’s an overgrown parrot, but it works for her, somehow. Just listen to her, you’ll know what I mean: run `echo "I am bigger than my problems"`
1. **Append “Goodbye world” to the file from the previous challenge**

    *Hint:* Give your cheatsheet a quick glance. You’ll find what you’re looking for in the “Pipe/Redirection” section.
1. **Delete the file from the previous challenge and recreate it with only one use of the echo command**

    *Hint:* Over the years, we’ve manage to teach some tricks to `echo`. Or a trick. It wasn’t easy, but now she can repeat multiline messages. I know, I know, it’s not much. Actually, it’s almost nothing. It’s just so hard to be patient when teaching such blithering idiot. 

    Hopefully, you can find a use for this multiline message crap, because I’ve had enough of it. run: `echo -e “line-1\nline-2”`

## Section-7 - Beginnings and ends of files
1. **Identify first two lines of aLongFile.cpp**

    *Hint:* `head` and `tail` are a very myoptic couple. You give them a file, and they only see what’s directly in front of them, and they’re oblivious to everything else. For `head` it is the first couple of lines of a file, and for `tail` it is the last couple of lines. By default, each command zeroes in on a total of ten lines, but that might be configurable. Check the docs on that.
1. **Identify the last three lines of aLongFile.cpp**

    *Hint:* see above hint
1. **Store first two lines of a long file into a new file**

    *Hint:* see above hint
1. **Make a file that contains all of contents of fileA.txt and fileB.txt**

    *Hint:* You probably could have guessed it, but `cat` is short is concatenation. So, naturally, when you give it two arguments, it combines them in order and print them to the terminal.
1. **Identify the first two lines of fileA.txt and the last three lines of fileB.txt with one command**

    *Hint:* Our definition of single command is a very loose interpretation. Examples of some “single” commands include: `echo Hi; echo Bye` and `ls && ls ..`. As seen in these two examples, you can perform multiple commands, one after the other, all “in one shot.” 

1. **Make a file that contains the first two lines of fileA.txt and the last three lines of fileB.txt with one command**

    *Hint:* This challenge is purposely saved for last because it’s pretty much impossible to figure out from the information provided in this workshop. So, ha! We win! But to be honest the solution, is so simple that’s it’s kind of dull. What’s more interesting is that the command/technique you’d expect to work, fails completely. The take-home message is that with all its simplicity and resourcefulness, Unix still has some ugliness that gets in the way of solving what you’d expect to be easy problems.

    Now that we’re done explaining the moral of this challenge, you might be wondering what is that dratted solution. Our hint to you, is to look up the concept of a subshell. With the help of [this stackoverflow answer](http://stackoverflow.com/questions/8624669/unix-head-and-tail-of-file/8624829#8624829), you should be able to piece together the solution to this challenge.
