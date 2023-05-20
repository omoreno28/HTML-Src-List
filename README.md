# HTML-Src-List
Written in C. The general idea of this program is to use various commands to analyze the content of HTML files.  
All of the commands are related to HTML tags that have a src attribute.

Outline of Functionality:
  1. Prints "URL:\n" to the standard output.
  2. Gets the url of the HTML document to analyze from the standard input.
  3. Reads the HTML document into a string in memory.
  4. While the quit command has not been received:
    - Prints "Ready\n" to the stdout.
    - Gets a command to execute from the standard input. The command will be one of the following (followed by a '\n'):
      * c = count. Prints the number of valid src attributes found in the HTML document to the standard output.
      * t = tags. Each time a valid src attribute is found, print the associated tag name plus a "\n" to the standard output.
      * u = urls. Each time a valid src attribute is found, print the associated URL plus a "\n" to the standard output.
      * f = frequencies. Writes a list of tag names and tag counts (as with other commands, only includes tags with valid src                           attributes) to the standard output.  Names and counts are seperated by a \t; one tag+count combo per line.  The order of the tag names           follow the same order in which tags are first encountered in the HTML source file (top to bottom).
      * q = quit.   
    - Perform the requested command.
  6. Prints "Complete\n" to stdout.

Assumptions:
  1. Valid xhtml.
  2. All src urls have double-quotes around them.
  3. Tags and attributes are lower case.
  4. There aren't any nasty CDATA sections in the HTML file.

Additional Information:
  1. Valid src attributes 
    - Searches for src=\". Only counts src attributes that have at least one white space character before the s of src.
      NOTE: This exlcludes .src=\"
