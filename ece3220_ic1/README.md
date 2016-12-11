# day1

## About

Assignment from the first day of class.   

Asks the user for a number n, (1 < n <= 10), and a parameter: 'm' or 'p'.   
Prints either the first ten multiples of n or the first 6 integer powers of n.   
Malformed input is given one retry attempt. If the second attempt fails, the program exits.

## Considerations / Issues / Limitations
 
 - Doesn't handle input buffer overflow (segfaults) 
 - Doesn't check for uppercase character parameters (or convert input) 
 - Buffer array is global 
 - Error codes in parameter-getting functions are ambiguous
     - i.e. return -1 for two different failure mechanisms
 - Number of retry attempts is not configurable 
 - Accepts no command line arguments or switches 

## Tools used 

 - Vim
 - Git 
 - Make 
 - * nix development environment


## Author 

- Zachary Rump 
