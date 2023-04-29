# TreeQuiz

This program helps you to create quizes using Binary TreeQuiz

## Logic

When the quiz starts, you are at the top (or root) of the tree that contains all the questions. If you answer correctly, you go to the right node, or left otherwise, and the quiz continues. Thus it is possible to make questions harder as more correct answers are received

## Usage

Create a file containing all the questions in the following format:

```
Question 1 | Answer to question 1
Question 2, if got correct answer | Answer 2
Question 3, if got correct answer | Answer 3
...
Question 3, if got incorrect answer | Answer 3
Question 2, if got incorrect answer | Answer 2
Question 3, if got correct answer | Answer 3
...
Question 3, if got incorrect answer | Answer 3
```

When done, run `make` followed by `./main <filename>` to compile and run the program
