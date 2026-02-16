##Background
I haven't dealt with C++ since about 2017 or so, and I'm totally new to Cmake, Catch2, vcpkg, and some other new-to-me approaches (loops for example). Because of this, I spent more time with infrastructure than with actual coding.
At the moment I'm still stuck with linking Catch2 to the project, so there is some commented code regarding that. #include's just couldn't find the hpp files. I was trying various approaches, through vcpkg, or this way: https://about.gitlab.com/blog/develop-c-unit-testing-with-catch2-junit-and-gitlab-ci/
There are traces of this in the code.

##How to run
Clone the repo and open the filder in Visual Studio. If launching with Visual Studio, you can either
	- define command line parameters in launch.vs.json (right-click on CMakeLists.txt, "Add Debug Cnfiguration" or "Open Launch And Debug Settings"), by adding to the configuration list let's say
	      "args": [
			"../../../data/sample_02.ifc",
			"../../../data/sample_02_formattted.ifc"
		]
	- or locate the executable and run it from command line: "ifc_fmt infile outfile", where infile should be an existing file, and outfile should not be the same as infile.

##How the parser works:
It is trying to build a rather simple ifc model looking for DATA; blocks in a file, using ENDSEC; tags. Once DATA; blocks are collected, they are organized and formatted by the requirement, while non-DATA blocks are preserved as they were. Unfortunately parenthese and syntax check is only performed once DATA statements are in a line. There were some doubts in me, because some syntax incorrectness in a preserved block could affect the correctness of a processed block, so I decided no to do multiline syntax checks at this point.
For identification of DATA; block lines I use the assmuption that they start like "# number = NAME".
If erros were found, no output file is generated.
I did use some code I found online, namely the algorithm with stacks for parenthese correctness check.

##Other limitations I'm aware of:
- blocks are identified only if DATA; and ENDSEC; tags are separate lines themselves.


##Todo's within the scope:
- get Catch2 working and write tests
- more professional error handling
- more optimal way of handling files, checking if output file already exists
- get into syntax error position (I didn't dig into that this time, because what I could report at this stage easily is according to the formatted output)
- searching a more optimal way of handling collections, instead of using std::vector everywhere

##Todo's outside the scope:
- build a proper ifc model, not limited to DATA; sections
- quote/parenthese check all through the file
