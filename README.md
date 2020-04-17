# ED2 (EDSCREEN) Screen Editor: v2.01
March 29, 2020


ED2 (EDSCREEN) is a lightweight, screen-oriented, plain-text file editor, suitable for creating and maintaining small documents that can fit into CP/M available memory.

ED2 (EDSCREEN) for CP/M is updated from the original Edward K. Ream program first published in Dr. Dobbs Journal #63, January 1982. and made available through the Simtel and Walnut Creek CP/M repositories.  The editor maintains its C/80 (Software Toolworks) compiler compatibility.

Excerpts from the original Dr. Dobbs Journal Volume 7 articles are in this repository.  The main compilation can be found here:
https://archive.org/details/dr_dobbs_journal_vol_07_201803/mode/2up

For retro-computing enthusiasts, updates in this version include a visible command mode prompt, WordStar style cursor navigation, and to use backspace and arrow keys prominent on IBM Model-M derived layout (e.g. PC) keyboards.  The default terminal is the (Kaypro) ADM-3A.

## Mode Switching ##

There are three modes to the editor: 

- Command
- Edit
- Insert.

Initially the editor is in Command mode.  The current mode is shown on the top line of the editor along with the cursor's current line and column, and filename.

----------

**Command mode key:** (ESC)

- Enters command mode. [See Command Mode commands.](#command-mode)  
- Command mode prompt is shown as a colon **':'** on the last line of the screen 

**Edit mode key:** (CTRL-E or UP key)

- Enter edit mode.  [See Edit Mode commands.](#edit-mode)



**Insert Mode key:** (CTRL-N)

- Enter insert mode. [See Insert Mode commands.](#insert-mode)


## Special Characters ##

   All special characters may be used in edit and insert
modes, but only the command, edit, insert, undo and delete character keys may be used in command mode.

The function of each special character is given below:

## Cursor Movement: WordStar Style ##

**UP key:** (CTRL-E, or UP arrow key)

Move the cursor up one line unless the
cursor is already at the top line of the file.
Enter edit mode.

**DOWN key:** (CTRL-X, or DOWN arrow key)

Move the cursor down one line unless the
cursor is already at the bottom line of the file.
Enter edit mode.

**LEFT key:** (CTRL-S or LEFT arrow key)

Move the cursor left one character.

**RIGHT key:** (CTRL-D or RIGHT arrow key)

Move the cursor right one character.

## Line Insertion & Deletion, Splitting & Joining ##
**Insert up key:** (CTRL-U)

Insert a new line above the current line and enter
insert mode.

**Insert down key:** (Enter)

Insert a new line below the current line and enter
insert mode.

**Delete line key:** (CTRL-Y)

Delete the line on which the cursor rests.

**Split line key:**  (CTRL-L)

Split the current line into two lines.

**Join lines key:**  (CTRL-O)

Append the current line to the line above it.
Then delete the lower line.



## Character insertion & deletion and undo ##

While in insert mode, type character keys to insert text at the cursor
 
**Delete character key:** (Backspace)

Delete the character to the left of the cursor.


**Undo (abandon edits) key:** (CTRL-A)

Undo any editing done since the cursor last came to 
the current line.


## Edit Mode ##

   The following are the edit mode commands:

**'c' or ESC  (command):** Enter command mode.

**'i'  (insert):** Enter insert mode.

**'space':** Move the cursor right one character.

**'u'  (scroll page up):** Scroll the cursor up rapidly.  Hit any key to stop.

**'d'  (scroll page down):** Scroll the cursor down one page at a time.

**'b' (beginning):** Move the cursor to the beginning of the current line.

**'e'  (end):** Move the cursor to the end of the current line.

**'g' [line #]  (go to line):** Move the cursor to the start of the indicated line.

**'k' [char]  (kill up to [char]):** Delete from the cursor up to, but not including <char>. Delete to the end of the line if <char> does not appear to the right of the cursor. Do not delete anything if <char> is a special character.

**s [char]  (search for [char]):** Move cursor to the next occurrence of <char> to the right of the cursor. Move cursor to the end of the current line if <char> does not appear to the right of the cursor.

**x [char]  (eXchange one character):** If <char> is not a special character then <char> replaces the character under the cursor.

**any other characters are (ignored):** If <char> is neither a special character nor an edit mode mode command it is completely ignored.



## Insert Mode ##

Use insert mode to enter multiple lines of text into the buffer. All characters which are not special characters are simply inserted into the buffer.

## Command Mode ##

Use command mode to load or save files and do operations
that effect the edit buffer.


**g [n] (go):** Enter edit mode and set the cursor on line **[n]**.  If **[n]** is not entered, the current line is used for **[n]**.


**search [line range]:** Print all lines on the display which contain an instance of **[search mask]**.

- Question marks match any character in **[search mask]**.
- A leading up arrow (^) anchors the search mask to the start of the line.
- The '?' and '^' characters are treated just as in the change command.
- [line range] ** is a formatted as....**

**find:** Search for the next occurrence of **[search mask]**.

- Enter edit mode if **[search mask]** is found. Otherwise, stay in command mode.
- The '?' and '^' characters are treated just as in the change command.
 
**change [line range]:**
Change the first instance of **[search mask]** on each line in the line range to **[change mask]**.

- Question marks in **[change mask]** match the character that the corresponding question mark matched in **[search mask]**.

**delete [line range]:** Delete all lines with numbers in [line range].

----------

**clear:** Erase the entire buffer.

**load [filename]:** Erase the buffer, then load it with the file named by [filename].

- [filename] becomes the current file name which is used by the save and resave commands.

**name [filename]:** Make [filename] the current file name for use by the save and resave commands.

**append [filename]:** Append the file <filename> to  the main buffer at the current cursor position.

**save:** Save the buffer in the file named in the load or name commands. **The file must not
already exist.**

**resave:**Save the buffer in the file named in the load or name commands. **The file must already exist.**

**dos:** Return to the operating system (exit from the editor).

- User is prompted whether to discard edits. 

----------

**tabs [number]:** Cause tabs to be printed as [number] blanks on the screen and on the list device.

**list [line range]:** List all lines with numbers in <line range> on the list device (printer).
