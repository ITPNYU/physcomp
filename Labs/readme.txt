How to make new lab illustrations

You'll need:
*Fritzing 0.8.0
*Illustrator CS6
*a text editor
*WordPres
*a little patience

1. Make a new folder for the lab in the labs2014 folder if it doesn't exist already.

2. From the lab templates folder, open LabTemplate.fzz in Fritzing.

3. Save As Lab(lab name) in your lab's folder

4. Make the final state of the circuit in Fritzing from this file. Get the breadboard and the schematic views neat and tidy. For schematics, use the ground symbol where needed to make things readable.

5. Export the breadboard and schematic views as .svg files. Use the default names, Lab(lab name)_bb and Lab(lab name)_schem respectively.  Your life will be easier if you have only these two .svgs for each complete circuit. You'll do all the step-by-step edits in Illustrator.

6. Because of a bug in Illustrator CS6, you have to edit the text of the .svg files in a text editor before Illustrator can open them. Remove any reference to "font-family". it helps to have a text editor that can handle regular expressions, like Coda, TextMate, Sublime, or any command line editor. A global search and replace for these terms should do the job:
font-family="*"
style="font-family:*"
Save the .svg files when you're done removing these terms.

7. Open the svg files in illustrator. 

8. Because of a bug in the Fritzing Arduino Uno part, the Uno will look wrong in your_bb file. Delete it, leaving the rest of the image intact.

9. From the lab templates folder, open Arduino_bb.svg. This is a cleaned-up export of the Arduino part. Select all and paste into your _bb file. The new Arduino should be perfectly sized to drop in place of the messed up Uno. Select the Arduino, Arrange -> Send To Back, then move the Arduino into place to line up with your wires.

10. Select All and transform the image, expanding the long edge to 8 inches. Adjust the drawing size to fit the drawing. Command-0 to center it all, and Save. this is your reference .svg for the breadboard view.

11. In the schematics svg, Select All and transform the image, expanding the long edge to 8 inches. Adjust the drawing size to fit the drawing. Select All again and change all the line widths to 2 points. Command-0 to center it all, and save. This is your reference svg for the schematic.

12. Check both .svgs for idiosyncrasies of Fritzing, like parts not lined up with the holes of the breadboard, etc.

13. In both .svgs, remove the parts needed to show each step, and Save As with the name of the step. then Export as a .PNG with the name of the step. Repeat for each step.

14. Import all the PNG files to WordPress and drop them into your lab. 