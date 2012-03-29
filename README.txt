Install:

Download the module's dependencies - jquery_update and libraries module.

Download the noty library from github and place it in the libraries directory.

The path to noty.js should be sites/all/libraries/noty/js/jquery.noty.js

Download the module and untar into your site's modules directory.

Go to admin/modules/list and enable the module.

Go to admin/config/user-interface/noty-messages and enable the message types you would like to be
taken over by noty.
------------------------------------------------------
Usage:

Once you have enabled the message types, they will be taken over by noty rendering.

You can decided to disable the display of noty style messages on admin pages.
------------------------------------------------------
Customization:

There are several built in themes inside the noty library.  You can use those or you can override them
by putting files with the same names into your theme/notycss/ directory.

If you choose custom, you have to make a file in that directory called noty_theme_custom.css and copy
one of the original theme files over and work on it.

In admin, all themes are getting loaded for preview.

------------------------------------------------------
Known issues:
No Dynamic theme loading / discovery

------------------------------------------------------

This module was written by MrMaksimize. It uses code from https://github.com/needim/noty
