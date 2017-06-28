all:Test.exe

Test.exe:main.obj
	link /out:$@ $^
	
main.obj:main.cxx
	cl /c $<
clean :
	-del main.obj Test.exe