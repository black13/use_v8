1. 	This example uses version 3.26 of the V8 engine, the reasons for using and older version
	is for compatibility with vs 2010. Later versions of V8 use vs 2013 and will soon use 
	those features.
2.  Requirements vs 2010 sp1 and a subversion client.
3.	The build of this is going to use 32bit versions and should be done from the vs 2010 command shell
	for the 32bit. I would help to have the subversion command line client on the path.
4. 	Obtain V8 3.26 from the branch by:
	svn checkout http://v8.googlecode.com/svn/branches/3.26/ v8
5. 	Change directory into the  v8 direct from the step above. Then run the following:
	svn co http://gyp.googlecode.com/svn/trunk build/gyp
6. 	Pull python tools and third party binaries as well by doing:
	> svn co http://src.chromium.org/svn/trunk/tools/third_party/python_26@89111 third_party/python_26
	> svn co http://src.chromium.org/svn/trunk/deps/third_party/cygwin@231940 third_party/cygwin
	> svn co https://src.chromium.org/chrome/trunk/deps/third_party/icu46 third_party/icu
	
7. 	Build the shared libraries. 
	python build\gyp_v8 -Dtarget_arch=ia32 -Dcomponent=shared_library
	cd to build and run:
	msbuild /p:Configuration=Release /p:Platform=Win32 all.sln	
	
	
*.	Examples
	http://v8.googlecode.com/svn/trunk/test/cctest/test-func-name-inference.cc