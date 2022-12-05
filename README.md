# DFA Minimizer
> This program is compatible with C++11.

This program takes: 
> State are represented by unsigned integers in this program and it can't be changed. Starting state is `0`.

1. Number of states in the DFA -`unsigned integer`.
2. Alphabets - `string`.  
Alphabet seperated by commas `,`.
Example: `a,b`

3. Accepting state - `unsigned integer`.
> DFA by definition may have multiple accepting state. Support for same will be included later.

4. Transition - `unsigned integer`.

Input delta(state, alphabet) as asked in console.

**Sample inputs:**
> Examples are from [this webpage.](https://www.gatevidyalay.com/minimization-of-dfa-minimize-dfa-example/#:~:text=PRACTICE%20PROBLEMS%20BASED%20ON%20MINIMIZATION%20OF%20DFA%2D)

1. [Run on an online IDE](https://bit.ly/3p4tDCD)
> ![DFA-Example-1](https://www.gatevidyalay.com/wp-content/uploads/2018/08/DFA-Minimization-Problem-01.png)  
_Source: https://www.gatevidyalay.com/minimization-of-dfa-minimize-dfa-example/_
```
5
a,b
1
4
1
2
1
3
1
2
1
4
1
2
```

2. [Run on an online IDE](https://bit.ly/3p1RLWK)
> ![DFA-Example-2](https://www.gatevidyalay.com/wp-content/uploads/2018/08/DFA-Minimization-Problem-03.png)  
_Source: https://www.gatevidyalay.com/minimization-of-dfa-minimize-dfa-example/_
```
5
a,b
4
1
3
2
4
1
4
2
4
4
4
```
