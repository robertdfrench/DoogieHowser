DoogieHowser
============

An MD package that's too big for its shorts

### Installing

Installing DoogieHowser follows the normal conventions for GNU-style packages:

* `./configure`
* `make install`

The `configure` script takes the usual options, such as `--prefix` for installing to non-standard locations. This is recommended if, for example, installing on a system where you do not have sudo access (likely the case for users of most HPC systems). If you are installing on an unsupported system (currently, anything other than old versions of Mac OS X), you are advised also to run `make check`. 

### Developers

Setting up the DoogieHowser development environment on Mac OS X can be done easily via (Homebrew)[http://brew.sh/]:

* `brew install check`
* `brew install pkg-config`
* `echo "/usr/local/share/aclocal" | sudo tee -a /usr/share/aclocal/dirlist`

The unit tests are written using a framework called (Check)[http://check.sourceforge.net/], which makes use of the GNU Autoconf tools. Unfortunately, the OS X developer tools do not include Pkg-Config by defualt, so they must be installed as well. Also, when installing Check, Homebrew does not automatically alter the system `aclocal` path. Thus the HomeBrew created `/usr/local/share/aclocal` directory must be appended the system `/usr/share/aclocal/dirlist` file so that Autoconf can find the Check and Pkg-Config macros. See (Issue #4)[https://github.com/robertdfrench/DoogieHowser/issues/4] for more discussion on this.

Once the environment has been set up correctly, the build configuration can be updated by running `autoconf --install`. At this point, you can configure the build by running `./configure` and then run the tests with a good old fashioned `make; make check`.
