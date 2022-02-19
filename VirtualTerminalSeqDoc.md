<style>table.t tr,table.t th{border: 1px solid black;padding: 10px 20px 10px 10px;}.t{border: 2px solid black;}.idk{color:#ff0000;}.todo{color:#22aaaa;}.maybe{color:#0000ff;}.tocheck{color:#aadd00;}.ok{color:#00ff00;}</style>

ANSI Virtual Terminal Sequences
===============================

Web sites with infos
--------------------

* wikipedia:
    * [ANSI escape code](https://en.wikipedia.org/wiki/ANSI_escape_code)
    * [control codes](https://en.wikipedia.org/wiki/C0_and_C1_control_codes)
    * [ISO/IEC 2022 standard](https://en.wikipedia.org/wiki/ISO/IEC_2022) (can't consult standart -> not free)
* github:
    * [fnky's page](https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797)
* [ASCII table](http://ascii-table.com/documents/vt100/chapter3.php#S3.3.3)
* [GNU manual](https://www.gnu.org/software/screen/manual/html_node/Control-Sequences.html)
* [Microsoft's doc](https://docs.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences)

[XTerm doc](https://invisible-island.net/xterm/ctlseqs/ctlseqs.html)


[Ecma standard](https://www.ecma-international.org/wp-content/uploads/ECMA-48_5th_edition_june_1991.pdf)


Basic escape sequences
----------------------

* Type Fe (C1 set element)
    > most useful ones

    * ESC: <code>\x1b</code>

        start of an escape sequence


    * CSI: <code>ESC [</code>

        Control Sequence Introducer


    * OSC: <code>ESC ]</code>

        Operating System Command


    * ST: <code>ESC \ </code>

        String Terminator (used to end strings in other sequences such as in OSC)


* Type Fs (independant functions)
    > reserch a bit

* ~~Type 0Ft (announcement)~~

* ~~nF or nFp (private)~~
    > mostly used for ANSI/ISO code-switching mechanisms


Control Sequence Introducer (ESC [)
-----------------------------------
---

* <h3>Cursor control</h3>

    <table class = "t">
        <tr>
            <th style = "padding-right: 60px;">Sequence</th>
            <th>Effect</th>
        </tr>
        <tr class = "tocheck">
            <th><code>CSI [n]A</code></th>
            <th>moves the cursor n lines up</th>
        </tr>
        <tr class = "tocheck">
            <th><code>CSI [n]B</code></th>
            <th>-> n lines down</th>
        </tr>
        <tr class = "tocheck">
            <th><code>CSI [n]C</code></th>
            <th>-> n lines right</th>
        </tr>
        <tr class = "tocheck">
            <th><code>CSI [n]D</code></th>
            <th>-> n lines left</th>
        </tr>
        <tr class = "tocheck">
            <th><code>CSI [n]E</code></th>
            <th>moves the cursor to the begining of the n<sup>th</sup> line in the viewport (top to bottom)</th>
        </tr>
        <tr class = "tocheck">
            <th><code>CSI [n]F</code></th>
            <th>same but from bottom to top</th>
        </tr>
        <tr class = "tocheck">
            <th><code>CSI [n]G</code></th>
            <th>moves the cursor to column n</th>
        </tr>
        <tr class = "tocheck">
            <th><code>CSI [n];[m]H</code></th>
            <th>moves the cursor to (n; m). n and m start from 1</th>
        </tr>
        <tr class = "maybe">
            <th><code>CSI [n];[m]f</code></th>
            <th>same as previous but is a format effector function</th>
        </tr>
        <tr class = "tocheck">
            <th><code>CSI s</code></th>
            <th>saves the current cursor position</th>
        </tr>
        <tr class = "tocheck">
            <th><code>CSI u</code></th>
            <th>restores the cursor to last saved position</th>
        </tr>
        <tr class = "tocheck">
            <th><code>CSI ?12h</code></th>
            <th>enables cursor blinking</th>
        </tr>
        <tr class = "tocheck">
            <th><code>CSI ?12l</code></th>
            <th>disables cursor blinking</th>
        </tr>
        <tr class = "tocheck">
            <th><code>CSI ?25h</code></th>
            <th>show cusror</th>
        </tr>
        <tr class = "tocheck">
            <th><code>CSI ?25l</code></th>
            <th>hides cursor</th>
        </tr>
    </table>

---

* <h3>Screen controls</h3>

    <table class = "t">
        <tr>
            <th style = "padding-right: 60px;">Sequence</th>
            <th>Effect</th>
        </tr>
        <tr class = "todo">
            <th><code>CSI [n]S</code></th>
            <th>scrolls up n lines</th>
        </tr>
        <tr class = "todo">
            <th><code>CSI [n]T</code></th>
            <th>scrolls down n lines</th>
        </tr>
    </table>

    * screen modes (CSI = n h)

        <table class = "t">
            <tr>
                <th style = "padding-right: 60px;">Sequence</th>
                <th>Effect</th>
            </tr>
            <tr class = "todo">
                <th><code>CSI =0h</code></th>
                <th>40 x 25 monochrome (text)</th>
            </tr>
            <tr class = "todo">
                <th><code>CSI=1h</code></th>
            <th>40 x 25 color (text)</th>
            </tr>
            <tr class = "todo">
                <th><code>CSI=2h</code></th>
                <th>80 x 25 monochrome (text)</th>
            </tr>
            <tr class = "todo">
                <th><code>CSI=3h</code></th>
                <th>80 x 25 color (text)</th>
            </tr>
            <tr class = "todo">
                <th><code>CSI=4h</code></th>
                <th>320 x 200 4-color (graphics)</th>
            </tr>
            <tr class = "todo">
                <th><code>CSI=5h</code></th>
                <th>320 x 200 monochrome (graphics)</th>
            </tr>
            <tr class = "todo">
                <th><code>CSI=6h</code></th>
                <th>640 x 200 monochrome (graphics)</th>
            </tr>
            <tr class = "todo">
                <th><code>CSI=7h</code></th>
                <th>Enables line wrapping</th>
            </tr>
            <tr class = "todo">
                <th><code>CSI=13h</code></th>
                <th>320 x 200 color (graphics)</th>
            </tr>
            <tr class = "todo">
                <th><code>CSI=14h</code></th>
                <th>640 x 200 color (16-color graphics)</           td>
            </tr>
            <tr class = "todo">
                <th><code>CSI=15h</code></th>
                <th>640 x 350 monochrome (2-color graphics)         </th>
            </tr>
            <tr class = "todo">
                <th><code>CSI=16h</code></th>
                <th>640 x 350 color (16-color graphics)</           td>
            </tr>
            <tr class = "todo">
                <th><code>CSI=17h</code></th>
                <th>640 x 480 monochrome (2-color graphics)         </th>
            </tr>
            <tr class = "todo">
                <th><code>CSI=18h</code></th>
                <th>640 x 480 color (16-color graphics)</           td>
            </tr>
            <tr class = "todo">
                <th><code>CSI=19h</code></th>
                <th>320 x 200 color (256-color graphics)</          td>
            </tr>
            <tr class = "maybe">
                <th><code>CSI={value}l</code></th>
                <th>Resets the mode by using the same           values that Set Mode uses, except for 7,        which disables line wrapping. The last      character in this escape sequence is a        lowercase L.</th>
            </tr>
            </tbody>
        </table>

---

* <h3>Text formatting</h3>
    <code>CSI [command...]m</code> 
    
    where the commands are separated with semicolons.
    A command is a number folowed by zero ore more semicolon separated parameters (numbers).
    Commands are executed in order.
    The following commands exist:

    <table class = "t">
        <tr>
            <th style = "padding-right: 60px ">Commands</th>
            <th>Effect</th>
        </tr>
        <tr class = "todo">
            <th><code>0</code></th>
            <th>reset formatting to default</th>
        </tr>
        <tr class = "todo">
            <th><code>1</code></th>
            <th>turn on high intencity (bold)</th>
        </tr>
        <tr class = "todo">
            <th><code>2</code></th>
            <th>turn on low intensity (faint)</th>
        </tr>
        <tr class = "todo">
            <th><code>22</code></th>
            <th>turn off low and high intensity</th>
        </tr>
        <tr class = "todo">
            <th><code>3</code></th>
            <th>turn on italics</th>
        </tr>
        <tr class = "todo">
            <th><code>23</code></th>
            <th>turn off italics</th>
        </tr>
        <tr class = "todo">
            <th><code>4</code></th>
            <th>turn on underline</th>
        </tr>
        <tr class = "todo">
            <th><code>21</code></th>
            <th>turn on double underline</th>
        </tr>
        <tr class = "todo">
            <th><code>24</code></th>
            <th>turn off all underline</th>
        </tr>
        <tr class = "todo">
            <th><code>58;2;[r];[g];[b]</code></th>
            <th>set underline color to (r; g; b)</th>
        </tr>
        <tr class = "todo">
            <th><code>58;5;[c]</code></th>
            <th>
                set underline color to c, the color c is set by the OS (can be changed with an OSC)
            </th>
        </tr>
        <tr class = "todo">
            <th><code>59</code></th>
            <th>set underline color to default</th>
        </tr>
        <tr class = "todo">
            <th><code>5</code></th>
            <th>turn on slow blink</th>
        </tr>
        <tr class = "todo">
            <th><code>5</code></th>
            <th>turn on fast blink (not always supported)</th>
        </tr>
        <tr class = "todo">
            <th><code>25</code></th>
            <th>turn off blink</th>
        </tr>
        <tr class = "todo">
            <th><code>7</code></th>
            <th>reverse background and foreground colors (negative)</th>
        </tr>
        <tr class = "todo">
            <th><code>27</code></th>
            <th>re-reverse background and foreground colors (positive)</th>
        </tr>
        <tr class = "todo">
            <th><code>8</code></th>
            <th>hide text (-> passwords)</th>
        </tr>
        <tr class = "todo">
            <th><code>28</code></th>
            <th>show text (-> normal)</th>
        </tr>
        <tr class = "todo">
            <th><code>9</code></th>
            <th>turn on strikethrough</th>
        </tr>
        <tr class = "todo">
            <th><code>29</code></th>
            <th>turn off strikethrough</th>
        </tr>
        <tr class = "todo">
            <th><code>38;2;[r];[g];[b]</code></th>
            <th>
                set foreground color to (r; g; b)
            </th>
        </tr>
        <tr class = "todo">
            <th><code>38;5;[c]</code></th>
            <th>
                set foreground color to c, the color c is set by the OS (can be changed with an OSC)
            </th>
        </tr>
        <tr class = "todo">
            <th><code>39</code></th>
            <th>
                set foreground color to default
            </th>
        </tr>
        <tr class = "todo">
            <th><code>48;2;[r];[g];[b]</code></th>
            <th>
                set background color to (r; g; b)
            </th>
        </tr>
        <tr class = "todo">
            <th><code>48;5;[c]</code></th>
            <th>
                set background color to c, the color c is set by the OS (can be changed with an OSC)
            </th>
        </tr>
        <tr class = "todo">
            <th><code>49</code></th>
            <th>
                set background color to default
            </th>
        </tr>
        <tr class = "todo">
            <th><code>53</code></th>
            <th>turn on overline</th>
        </tr>
        <tr class = "todo">
            <th><code>55</code></th>
            <th>turn off overline</th>
        </tr>
    </table>

---

* <h3>Text editing</h3>

    <table class = "t">
        <tr>
            <th style = "padding-right: 60px;">Sequence</th>
            <th>Effect</th>
        </tr>
        <tr class = "todo">
            <th><code>CSI [n]@</code></th>
            <th>insert n spaces at the current cursor position, shifting all text to the right (text exiting the screen is removed)</th>
        </tr>
        <tr class = "todo">
            <th><code>CSI [n]P</code></th>
            <th>deletes n characters after the cursor position</th>
        </tr>
        <tr class = "todo">
            <th><code>CSI [n]X</code></th>
            <th>replaces n characters after the cursor position with spaces</th>
        </tr>
        <tr class = "todo">
            <th><code>CSI [n]L</code></th>
            <th>inserts n lines after the cursor position (all lines below and including the line where the cursor is will be shifted downwards)</th>
        </tr>
        <tr class = "todo">
            <th><code>CSI [n]M</code></th>
            <th>deletes n lines after the cursor position (including the line the cursor is on)</th>
        </tr>
    </table>

---

* <h3>Query state</h3>
    the queries will send their output in the standard input stream  (or console input stream)
    (by default)

    <table class = "t">
        <tr>
            <th style = "padding-right: 60px;">Sequence</th>
            <th>Effect</th>
        </tr>
        <tr class = "todo">
            <th><code>CSI 6n</code></th>
            <th>emites the cursor position with the as: <code>CSI [n];[m]R</code></th>
        </tr>
        <tr class = "todo">
            <th></th>
            <th>Search others</th>
        </tr>
    </table>

Operating System Commands
-------------------------
<br/>
here [str] stands for a string parameter terminated by ST.
[color] is a [str] that is either the name of the color (ei. "red") or a hex color ("#nnnnnn")
<table class = "t">
    <tr>
        <th style = "padding-right: 60px;">Sequence</th>
        <th>Effect</th>
    </tr>
    <tr class = "idk">
        <th><code>OSC 0;[str]</code></th>
        <th>changes the icon name and window title to [str]</th>
    </tr>
    <tr class = "idk">
        <th><code>OSC 0;[str]</code></th>
        <th>changes the icon name to [str]</th>
    </tr>
    <tr class = "todo">
        <th><code>OSC 0;[str]</code></th>
        <th>changes the window title to [str]</th>
    </tr>
    <tr class = "maybe">
        <th><code>OSC 3;[str]</code></th>
        <th>[str] has the form "[property]=[value]" to change a [property] or "[property]" to remove one</th>
    </tr>
    <tr class = "todo">
        <th><code>OSC 4;c;[color]</code></th>
        <th>changes the color c to [color] (c can be used in CSIs), you can have many c;[color] pairs</th>
    </tr>
    <tr class = "todo">
        <th><code>OSC 104;c</code></th>
        <th>reset color c to default</th>
    </tr>
    <tr class = "idk">
        <th><code>OSC 5;c;[color]</code></th>
        <th>changes the special color c to [color] (c can be used in CSIs), you can have many c;[color] pairs</th>
    </tr>
    <tr class = "idk">
        <th><code>OSC 105;c</code></th>
        <th>reset special color c to default</th>
    </tr>
    <tr class = "todo">
        <th><code>OSC 10;[color]</code></th>
        <th>sets the (default) foreground color</th>
    </tr>
    <tr class = "todo">
        <th><code>OSC 11;[color]</code></th>
        <th>sets the (default) background color</th>
    </tr>
    <tr class = "todo">
        <th><code>OSC 12;[color]</code></th>
        <th>sets the cursor's color</th>
    </tr>
    <tr class = "idk">
        <th><code>OSC 13-19;[color]</code></th>
        <th>???</th>
    </tr>
    <tr class = "todo">
        <th><code>OSC 110-119;[color]</code></th>
        <th>reset the colors set with OSC 10-19</th>
    </tr>
    <tr class = "idk">
        <th><code>OSC 50;[str]</code></th>
        <th>changes the font</th>
    </tr>
    <tr class = "idk">
        <th><code>OSC 52;[str]</code></th>
        <th>not yet supported by GNOME's terminal<br/>manipulates selection data</th>
    </tr>
</table>
