Run CSP script:

1. Install CSP/eybuild, see INSTALL

2. copy all .csp to cgi-bin of your webserver:
   cp *.csp /var/www/cgi-bin/

3. make script executable(default, need not):
   chmod a+rx /var/www/cgi-bin/*.csp

4. try from shell:
   /var/www/cgi-bin/svg.csp
   /var/www/cgi-bin/loop.csp
   ...

5. open browser and try following address:
   http://127.0.0.1/cgi-bin/svg.csp
   http://127.0.0.1/cgi-bin/loop.csp
   http://127.0.0.1/cgi-bin/input.csp
   http://127.0.0.1/cgi-bin/game.csp

