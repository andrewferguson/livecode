# Spinner Widget
The spinner widget can be used as an activity indicator, showing users 
that your app is busy performing a task that will take some time to 
complete.

When the spinner widget is visible, it spins around.  You can use the 
visible property of the widget to control when it’s displayed to the 
user.  Normally, it would make sense to display it in front of other 
content displayed on the screen.

![A group of spinners](images/spinner.gif)

## Creating a Spinner
A spinner widget can be created by dragging it out from the Tools
Palette, where it appears with the following icon:

<svg viewBox="0 0 1800 1800" style="display:block;margin:auto" width="auto" height="50">
  <path d="M496 1408Q496 1468 453.5 1510 411 1552 352 1552 292 1552 250 1510 208 1468 208 1408 208 1348 250 1306 292 1264 352 1264 411 1264 453.5 1306 496 1348 496 1408ZM928 1600Q928 1653 890.5 1690.5 853 1728 800 1728 747 1728 709.5 1690.5 672 1653 672 1600 672 1547 709.5 1509.5 747 1472 800 1472 853 1472 890.5 1509.5 928 1547 928 1600ZM320 960Q320 1026 273 1073 226 1120 160 1120 94 1120 47 1073 0 1026 0 960 0 894 47 847 94 800 160 800 226 800 273 847 320 894 320 960ZM1360 1408Q1360 1454 1327 1487 1294 1520 1248 1520 1202 1520 1169 1487 1136 1454 1136 1408 1136 1362 1169 1329 1202 1296 1248 1296 1294 1296 1327 1329 1360 1362 1360 1408ZM528 512Q528 585 476.5 636.5 425 688 352 688 279 688 227.5 636.5 176 585 176 512 176 439 227.5 387.5 279 336 352 336 425 336 476.5 387.5 528 439 528 512ZM992 320Q992 400 936 456 880 512 800 512 720 512 664 456 608 400 608 320 608 240 664 184 720 128 800 128 880 128 936 184 992 240 992 320ZM1536 960Q1536 1000 1508 1028 1480 1056 1440 1056 1400 1056 1372 1028 1344 1000 1344 960 1344 920 1372 892 1400 864 1440 864 1480 864 1508 892 1536 920 1536 960ZM1328 512Q1328 545 1304.5 568.5 1281 592 1248 592 1215 592 1191.5 568.5 1168 545 1168 512 1168 479 1191.5 455.5 1215 432 1248 432 1281 432 1304.5 455.5 1328 479 1328 512Z" />
</svg>


Alternatively it can be created in script using:

	create widget as "com.livecode.widget.spinner"

## Using the Spinner
Here are some tips that may help you use the spinner effectively.

### Ensuring the Spinner Actually Spins
The spinner widget will only update (rotate to its next notch) when the 
engine gets to do event processing, such as during a wait with messages 
statement.  There are several commands and functions which implicitly 
wait with messages internally, such as the url chunk.

However, if you are doing a slow computation, such as parsing a text 
file or loading data from a database, you may wish to add `wait 0 with 
messages` statement each time you make progress, so that the spinner 
continues to spin, and your users don’t think your app has frozen.

### Making it Clear that the App is “Busy”
You may wish to hide or “dim” your app’s user interface while the app is 
busy.  For example, your app could use a “splash screen” card that 
displays a logo and a spinner widget while loading its resources and 
preparing to run.  This helps by providing additional visual cues to the 
user that the app’s user interface is not ready to respond yet.

### Cancelling a Long-Running Activity
Sometimes, you may have a very slow process that you can safely abandon. 
It can be useful to provide a “Cancel” button. Suppose you have a stack 
with a cancelButton and a spinnerWidget.  You can create a cancellable 
process using a script-local variable to store whether the process 
should continue:

	-- In the script of the cancelButton
	on mouseUp
	   send "cancelOperation"
	end mouseUp

	-- In the stack script
	local sCancelled

	command doOperation
	   set the visible of control "spinnerWidget" to true
	   set the visible of control "cancelButton" to true
	   put false into sCancelled

	   repeat for each item to process
		  -- (do something with the item)

		  -- allow the spinner widget to spin, and
		  -- for cancel button clicks to be handled
		  wait 0 with messages
		  if sCancelled then
			 exit repeat
		  end if
	   end repeat

	   if not sCancelled then
		  -- (update the UI to reflect the results)
	   end if
	   set the visible of control "spinnerWidget" to false
	   set the visible of control "cancelButton" to false
	end doOperation
	
### Indicating Background Processing
Sometimes your app may need to do some background processing, such as 
synchronising its state with a server, without needing to block the user 
interface.  You may wish to use a spinner widget in a peripheral part of 
the user interface, such as a status bar, to provide an unobtrusive 
indication that this is going on.

For example, an e-mail app might regularly check for new messages, but 
that shouldn’t necessarily block the user from carrying on reading or 
writing e-mails.