Remote Spark
============

A Remote Starter example that's a customize-able simple Spark Core web app controller with feedback through Variables.

###Run The Example First!###

1. Edit the index.html file and enter your ``coreID`` and ``accessToken`` in the user editable data area.

2. Create a new app on https://www.spark.io/build and call it "RemoteSpark".  Copy/Paste the contents of the RemoteSpark.cpp file over your new app.  Save it and Flash it to your Core.

3. Open the index.html in your browser or upload all files to your website at a secret URL and start controlling your Spark Core!

NOTES: When you press Start Engine, notice the onboard blue LED tied to output D7 flashes twice when starting, and once when stopping.  Read more on the operation below.


###Customize it!###

1. Enter a ``funcKey``, ``args`` (if desired) and button ``label`` for each function you want to control. [Learn about how Functions work here.](http://docs.spark.io/#/firmware/cloud-spark-function)

2. Any button label that is defined such as ``label4 = "";``, will automatically hide that button.

3. Enter a ``varKey``, and ``refresh`` (rate in milliseconds) for each variable you want to access.  A refrsh rate of ``5000``(5 seconds) or greater is recommended.  NOTE: Leave the ``refresh = 0;`` to disable and hide that variable field. [Learn about how Variables work here.](http://docs.spark.io/#/firmware/cloud-spark-variable)

4. If you wish to show custom text based on the variable value, enter the ``varonState`` and corresponding ``varOnLabel`` and enter the ``varoffState`` and corresponding ``varOffLabel``.  Try to keep these short if you are using the app on a smartphone, so that the text doesn't get clipped.  If you want to just see the actual variable value, set the ``varonState = null;`` and ``varOffState = null;``

5. Name your app with the ``appHeading`` variable.

6. Edit your sketch with corresponding ``funcKeys`` and ``varKeys`` and whatever control and logic you can dream up for your project.

NOTES: You will see the "SUCCESS!" message pop up every time you press a button or your variables update.  It will say success on button presses only if it actually gets a return value of 200 from your function.  It will say success on variable updates if your coreID matches the one you enter in the webpage (currently variables don't return anything but their own value).  If you Core goes offline and you press a button, you'll see an ERROR! Timed Out message.  This success/error message popup could easily change to something else in the future.  Study the working example before you start editing it to your liking!"

NOTES ON REMOTESPARK.INO: This example was specifically designed for a buddy of mine who has a four button remote starter keyfob hooked up to his Spark Core.  The four digital outputs control four tiny reed relays that are wired up to the four buttons of a doner keyfob.  The Start Engine button requires two presses to start the engine, and one press thereafter to stop it.  If started, the car will run for 15 minutes and then turn off to conserve gas.  The example program will update the startState variable based on these conditions.  If the trunk is remotely popped, the trunkState variable helps to alert the user that the trunk is open which will need to be manually closed. To reset the trunkState back to off, just press the trunkPop button again.  The code is smart enough to track the trunkState and not open the trunk again when you are resetting the state.  Lock and Unlock are separate buttons, but there is just one state to keep track of.  In the future, the concept of time will be added by polling an NTP server or using the internal Real Time Clock to automatically start the engine at a certain time every morning.

For two other trimmed down versions without variables, check these out:
https://github.com/technobly/Simple-Spark-Core-Controller
https://github.com/technobly/Remote-RTTTL

![iPhone5s](http://i.imgur.com/9AAP4Mx.png)

Credits: This code is a hacked up version of code from http://www.github.com/jflasher/spark-helper thanks!
