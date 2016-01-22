This two files are copyed from fcgi-2.4.0. for WIN32
http://www.fastcgi.com

===============================
HOW TO USE FastCGI WITH EYBUILD
===============================

=========
FOR UNIX
=========
1. Download "fcgi.2.4.0.tar.gz" and "mod_fastcgi-2.4.2.tar.gz" from 
   website http://www.fastcgi.com/dist

2. Install FastCGI toolkits:
   tar -xzf fcgi.2.4.0.tar.gz
   cd fcgi.2.4.0
   ./configure
   make install

3. Install mod_fastcgi to Apache2:
   tar -xzf mod_fastcgi-2.4.2.tar.gz
   cd mod_fastcgi-2.4.2
   cp Makefile.AP2 Makefile 
   make 
   make install

   NOTE: 
   if your Apahe2 not installed in /usr/local/apache2, you need to set
   the variable "top_dir", see INSTALL.AP2
 
 4. Goto your project target directory, e.g.:
 	cd $EYBUILD_BASE/project/demo/unix

 5. Open the Makefile and remove the "#" before the line:
    # HAVE_FASTCGI = TRUE

 6. Rebuild project:
    make all

----------------------
newzy update
2006-4-25


=========
FOR WIN32
=========
1. Set environment "FASTCGI_BASE" as like "EYBUILD_BASE"
2. Copy "libfcgi.dll" to Windows system directory, e.g: system32
3. Copy "mod_fastcgi-2.4.2-AP20.dll" to Apache2/module diretory.
4. Add following into the file Apache2/conf/http.conf:
   LoadModule fastcgi_module modules/mod_fastcgi-2.4.2-AP20.dll
   AddHandler fastcgi-script .fcgi

   # must modify following path as you want to
   ScriptAlias /fcgi-bin/ "F:/website/fcgi-bin/"
   <Directory "F:/website/fcgi-bin">
       AllowOverride None   
       Options None
       Order allow,deny
       Allow from all
   </Directory>

5. Open projects with VC++ 6.0, right click in the toolbar, 
   select "build" from the popup menu.

6. Select the active project and active configration from this tool bar, 
   one of following:
   Win32 Release
   Win32 Debug
   Win32 ReleaseFastCGI
   Win32 DebugFastCGI

   Of course, you also can add new configration from menu:
   "Build" -> "Configurations..."

7. Rebuild project.

----------------------
http://www.eybuild.com
newzy@eybuild.com
2006-4-12

